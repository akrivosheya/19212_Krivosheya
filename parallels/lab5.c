#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "mpi.h"
#include <unistd.h>

#define TASKS 10
#define TRUE 1
#define FALSE 0
#define REQUIRE_TAG 1
#define SHARE_TAG 2
#define MAX_ITER 5
#define VALUE 10

#define SIZE 16

typedef struct Task_t{
    int isUntouched;
    int sleepNum;
} Task;

typedef struct Arguments_t{
    pthread_mutex_t* mutex;
    pthread_cond_t* cond;
    int rank;
    int size;
    int execIndx;
    int shareIndx;
    int badNum;
    Task taskList[TASKS];
} Arguments;

void* execTasks(void* me);
void* shareTask(void* me);
int getTask(Task* taskList, int* execIndx, int* sleepNum);
void start(int sleepNum);
int stealTask(int rank, int size, int* stoleFrom, int* sleepNum);
void createTasks(Task* taskList, Arguments* args,  int length, int size, int rank, int iter);

int main(int argc, char** argv){
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    pthread_attr_t attrs;
    if(pthread_attr_init(&attrs)){
        perror("Can't initialize attributes");
        return 0;
    }
    if(pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE))
    {
        perror("Error in setting attributes");
        return 0;
    }
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[2];
    Arguments args;
    args.mutex = &mutex;
    args.rank = rank;
    args.size = size;
    args.execIndx = 0;
    args.shareIndx = TASKS - 1;
    args.badNum = -1;
    if(pthread_create(&threads[0], &attrs, execTasks, &args))
    {
        perror("Cannot create a thread");
        return 0;
    }
    if(pthread_create(&threads[1], &attrs, shareTask, &args))
    {
        perror("Cannot create a thread");
        return 0;
    }
    pthread_attr_destroy(&attrs);
    for(int i = 0; i < 2; ++i){
        if(pthread_join(threads[i], NULL)){
            perror("Cannot join a thread");
            return 0;
        }
    }
    pthread_mutex_destroy(&mutex);


    MPI_Finalize();
    exit(0);
}

int getTask(Task* taskList, int* execIndx, int* sleepNum){
        if(taskList[*execIndx].isUntouched){
            taskList[*execIndx].isUntouched = FALSE;
            *sleepNum = taskList[*execIndx].sleepNum;
            *execIndx = (*execIndx + 1) % TASKS;
            return TRUE;
        }
        else{
            return FALSE;
        }
}

void start(int sleepNum){
    sleep(sleepNum);
}

int stealTask(int rank, int size, int* stoleFrom, int* sleepNum){
    int message;
    int isTask = FALSE;
    int value;
    for(int i = 0; i < size; ++i){
        if(i == rank){
            continue;
        }
        MPI_Send(&message, 1, MPI_INT, i, REQUIRE_TAG, MPI_COMM_WORLD);
        MPI_Recv(&value, 1, MPI_INT, i, SHARE_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(value >= 0){
            *sleepNum = value;
            ++stoleFrom[i];
            isTask = TRUE;
            break;
        }
    }
    return isTask;
}

void createTasks(Task* taskList, Arguments* args,  int length, int size, int rank, int iter){
    for(int i = 0; i < length; ++i){
        taskList[i].sleepNum = abs(rank-(iter  % size));
        taskList[i].isUntouched = TRUE;
    }
    args->execIndx = 0;
    args->shareIndx = TASKS - 1;
}

void* shareTask(void* me){
    MPI_Status status;
    int message;
    int badNum = -1;
    int isTasks = TRUE;
    int shareTo[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    while(isTasks){
        MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, REQUIRE_TAG, MPI_COMM_WORLD, &status);
        if(status.MPI_SOURCE == ((Arguments*)me)->rank){
                isTasks = FALSE;
        }
        else{
            pthread_mutex_lock(((Arguments*)me)->mutex);
                if((((Arguments*)me)->taskList)[((Arguments*)me)->shareIndx].isUntouched){
                    MPI_Send(&((((Arguments*)me)->taskList)[((Arguments*)me)->shareIndx].sleepNum), 1, MPI_INT,
                        status.MPI_SOURCE, SHARE_TAG, MPI_COMM_WORLD);
                    (((Arguments*)me)->taskList)[((Arguments*)me)->shareIndx].isUntouched = FALSE;
                    ((Arguments*)me)->shareIndx = ((((Arguments*)me)->shareIndx) - 1 + TASKS) % TASKS;
                    ++shareTo[status.MPI_SOURCE];
                }
                else{
                    MPI_Send(&(((Arguments*)me)->badNum), 1, MPI_INT, status.MPI_SOURCE, SHARE_TAG, MPI_COMM_WORLD);
                }
            pthread_mutex_unlock(((Arguments*)me)->mutex);
        }
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    for(int i = 0; i < ((Arguments*)me)->size; ++i){
        MPI_Barrier(MPI_COMM_WORLD);
        if(((Arguments*)me)->rank == i){
            printf("Process %d has shared:\n", ((Arguments*)me)->rank);
            for(int j = 0; j < ((Arguments*)me)->size; ++j){
                printf("   %d to %d\n", shareTo[j], j);
            }
        }
    }
}

void* execTasks(void* me){
    int iterCounter = 0;
    pthread_mutex_lock(((Arguments*)me)->mutex);
        createTasks(((Arguments*)me)->taskList, (Arguments*)me, TASKS, ((Arguments*)me)->size, ((Arguments*)me)->rank, iterCounter);
    pthread_mutex_unlock(((Arguments*)me)->mutex);
    int isTask = TRUE;
    int stoleFrom[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int done = 0;
    int sleepNum;
    int message;
    while(TRUE){
        ++iterCounter; 
        while(TRUE){
            if(!isTask){
                if(!stealTask(((Arguments*)me)->rank, ((Arguments*)me)->size, stoleFrom, &sleepNum)){
                    break;
                }
            }
            else{
                pthread_mutex_lock(((Arguments*)me)->mutex);
                    isTask = getTask(((Arguments*)me)->taskList, &(((Arguments*)me)->execIndx), &sleepNum);
                pthread_mutex_unlock(((Arguments*)me)->mutex);
                if(!isTask){
                    continue;
                }
            }
            start(sleepNum);
            ++done;
        }
        MPI_Barrier(MPI_COMM_WORLD);
        if(iterCounter >= MAX_ITER){
                for(int i = 0; i < ((Arguments*)me)->size; ++i){
                    MPI_Barrier(MPI_COMM_WORLD);
                    if(((Arguments*)me)->rank == i){
                        printf("Process %d has done %d and stolen:\n", ((Arguments*)me)->rank, done);
                        for(int j = 0; j < ((Arguments*)me)->size; ++j){
                            printf("   %d from %d\n", stoleFrom[j], j);
                        }
                    }
                }
                MPI_Send(&message, 1, MPI_INT, ((Arguments*)me)->rank, REQUIRE_TAG, MPI_COMM_WORLD);
            break;
        }
        pthread_mutex_lock(((Arguments*)me)->mutex);
            createTasks(((Arguments*)me)->taskList, (Arguments*)me, TASKS, ((Arguments*)me)->size, ((Arguments*)me)->rank, iterCounter);
            isTask = TRUE;
        pthread_mutex_unlock(((Arguments*)me)->mutex);
    }
}