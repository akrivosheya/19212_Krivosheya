#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define A 100000
#define E 0.00000001
#define DEFAULT 0
#define X0 -1
#define Y0 -1
#define Z0 -1
#define XNX 1
#define YNY 1
#define ZNZ 1
#define NX 10
#define NY 10
#define NZ_FOR_EACH 5
#define FIRST_PROC 0
#define FIRST_PLANE 0

double getRes(double x, double y, double z);
double getNextValue(double hx, double hy, double hz, 
    int i, int j, int k, int rank, double* planes, double* ro);
void initExchange(int rank, MPI_Request* reqUpSend, MPI_Request* reqDownSend, 
    MPI_Request* reqUpRec, MPI_Request* reqDownRec, double* results, int size);
void waitAll(int rank, MPI_Request* reqUpSend, MPI_Request* reqDownSend, 
    MPI_Request* reqUpRec, MPI_Request* reqDownRec, int size);
void copy(double* results, double* planes, int size);
int checkRes(double* planes, double* results, int size);

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double hx = (double)(XNX - X0) / (NX - 1);
    double hy = (double)(YNY - Y0) / (NY - 1);
    double hz = (double)(ZNZ - Z0) / (NZ_FOR_EACH * size - 1);

    double planes[NX * NY * (NZ_FOR_EACH + 2)];
    double ro[NX * NY * (NZ_FOR_EACH + 2)];
    double results[NX * NY * (NZ_FOR_EACH + 2)];
    for(int i = 0; i < NX; ++i){
            for(int k = 0; k < (NZ_FOR_EACH + 2); ++k){
                planes[k * NX * NY + i] = 
                    getRes(X0 + i * hx, Y0, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
                planes[k * NX * NY + i + (NY - 1) * NY] = 
                    getRes(X0 + i * hx, YNY, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
                results[k * NX * NY + i] = 
                    getRes(X0 + i * hx, Y0, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
                results[k * NX * NY + i + (NY - 1) * NY] = 
                    getRes(X0 + i * hx, YNY, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
            }
    }
    for(int j = 0; j < NY; ++j){
            for(int k = 0; k < (NZ_FOR_EACH + 2); ++k){
                planes[k * NX * NY + j * NX] = 
                    getRes(X0, Y0 + j * hy, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
                planes[k * NX * NY + NX - 1 + j * NX] = 
                    getRes(XNX, Y0 + j * hy, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
                results[k * NX * NY + j * NX] = 
                    getRes(X0, Y0 + j * hy, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
                results[k * NX * NY + NX - 1 + j * NX] = 
                    getRes(XNX, Y0 + j * hy, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
            }
    }
    for(int i = 1; i < NX - 1; ++i){
        for(int j = 1; j < NY - 1; ++j){
            for(int k = 0; k < (NZ_FOR_EACH + 2); ++k){
                if(rank == FIRST_PROC && k == FIRST_PLANE + 1){
                    planes[k * NX * NY + j * NX + i] = getRes(X0 + i * hx, Y0 + j * hy, Z0);
                    results[k * NX * NY + j * NX + i] = getRes(X0 + i * hx, Y0 + j * hy, Z0);
                }
                else if(rank == size - 1 && k == FIRST_PLANE + NZ_FOR_EACH){
                    planes[k * NX * NY + j * NX + i] = getRes(X0 + i * hx, Y0 + j * hy, ZNZ);
                    results[k * NX * NY + j * NX + i] = getRes(X0 + i * hx, Y0 + j * hy, ZNZ);
                }
                else {
                    planes[k * NX * NY + j * NX + i] = DEFAULT;
                    results[k * NX * NY + j * NX + i] = DEFAULT;
                }
                ro[k * NX * NY + j * NX + i] = 6 - A * 
                    getRes(X0 + i * hx, Y0 + j * hy, Z0 + (rank * NZ_FOR_EACH + k - 1) * hz);
            }
        }
    }

        

    MPI_Request reqUpSend, reqDownSend, reqUpRec, reqDownRec;
    int isEnd = 0, isChecked = 0;
    do{
        for(int i = 1; i < NX - 1; ++i){
            for(int j = 1; j < NY - 1; ++j){
                if(rank != FIRST_PROC){
                    results[(FIRST_PLANE + 1) * NX * NY + j * NX + i] = 
                        getNextValue(hx, hy, hz, i, j, FIRST_PLANE + 1, rank, planes, ro);
                }
                if(rank != FIRST_PROC + size - 1){
                    results[(FIRST_PLANE + NZ_FOR_EACH) * NX * NY + j * NX + i] = 
                        getNextValue(hx, hy, hz, i, j, FIRST_PLANE + NZ_FOR_EACH, 
                        rank, planes, ro);
                }
            }
        }
        initExchange(rank, &reqUpSend, &reqDownSend, &reqUpRec, &reqDownRec, results, size);
        for(int i = 1; i < NX - 1; ++i){
            for(int j = 1; j < NY - 1; ++j){
                for(int k = 2; k < FIRST_PLANE + NZ_FOR_EACH - 1; ++k){
                    results[k * NX * NY + j * NX + i] = 
                        getNextValue(hx, hy, hz, i, j, k,
                        rank, planes, ro);
                }
            }
        }
        waitAll(rank, &reqUpSend, &reqDownSend, &reqUpRec, &reqDownRec, size);
        isChecked = checkRes(&planes[NX * NY], &results[NX * NY], NX * NY * NZ_FOR_EACH);
        MPI_Allreduce(&isChecked, &isEnd, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
        copy(results, planes, NX * NY * (NZ_FOR_EACH + 2));
    } while(!isEnd);

    for(int i = 0; i < size; ++i){
        MPI_Barrier(MPI_COMM_WORLD);
    if(rank == i){
        printf("%d\n", rank);
        printf("hx - %f, hy - %f, hz - %f\n", hx, hy, hz);
        for(int i = 0; i < NX; ++i){
        for(int j = 0; j < NY; ++j){
            printf("%.3f ", results[NZ_FOR_EACH * NX * NY + j * NX + i]);
        }
        printf("\n");
    }
    }
    }

    
    MPI_Finalize();
    return 0;
}

void waitAll(int rank, MPI_Request* reqUpSend, MPI_Request* reqDownSend, 
        MPI_Request* reqUpRec, MPI_Request* reqDownRec, int size){
    if(rank != FIRST_PROC + size - 1){
        MPI_Wait(reqUpSend, MPI_STATUS_IGNORE);
        MPI_Wait(reqUpRec, MPI_STATUS_IGNORE);
    }
    if(rank != FIRST_PROC){
        MPI_Wait(reqDownSend, MPI_STATUS_IGNORE);
        MPI_Wait(reqDownRec, MPI_STATUS_IGNORE);
    }
}

void initExchange(int rank, MPI_Request* reqUpSend, MPI_Request* reqDownSend, 
        MPI_Request* reqUpRec, MPI_Request* reqDownRec, double* results, int size){
    if(rank != FIRST_PROC + size - 1){
        MPI_Isend(&results[(FIRST_PLANE + NZ_FOR_EACH) * NX * NY], 
            NX * NY, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, reqUpSend);
        MPI_Irecv(&results[(FIRST_PLANE + NZ_FOR_EACH + 1) * NX * NY], 
            NX * NY, MPI_DOUBLE, rank + 1, 2, MPI_COMM_WORLD, reqUpRec);
    }
    if(rank != FIRST_PROC){
        MPI_Isend(&results[(FIRST_PLANE + 1) * NX * NY], 
            NX * NY, MPI_DOUBLE, rank - 1, 2, MPI_COMM_WORLD, reqDownSend);
        MPI_Irecv(&results[FIRST_PLANE * NX * NY], 
            NX * NY, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD, reqDownRec);
    }
}

double getNextValue(double hx, double hy, double hz, int i, 
        int j, int k, int rank, double* planes, double* ro){
    double firstMul = 1.0 / (2.0 / (hx * hx) + 2.0 / (hy * hy) + 2.0 / (hz * hz) + A);
    double xCount = (planes[k * NX * NY + j * NX + i + 1] + 
        planes[k * NX * NY + j * NX + i - 1]) / hx / hx;
    double yCount = (planes[k * NX * NY + (j + 1) * NX + i] + 
        planes[k * NX * NY + (j - 1) * NX + i]) / hy / hy;
    double zCount = (planes[(k + 1) * NX * NY + j * NX + i + 1] + 
        planes[(k - 1) * NX * NY + j * NX + i - 1]) / hz / hz;
    return firstMul * (xCount + yCount + zCount - ro[k * NX * NY + j * NX + i]);
}

double getRes(double x, double y, double z){
    return x * x + y * y + z * z;
}

void copy(double* results, double* planes, int size){
    for(int i = 0; i < size; ++i){
        planes[i] = results[i];
    }
}

int checkRes(double* planes, double* results, int size){
    int isChecked = 0;
    double max = 0, difference;
    for(int i = 0; i < size; ++i){
        difference = planes[i] - results[i];
        difference = (difference < 0) ? -difference : difference;
        max = (difference > max) ? difference : max;
    }
    return (max < E);
}