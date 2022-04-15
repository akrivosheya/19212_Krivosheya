#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define N1 8
#define N2 2
#define N3 8
#define P1 2
#define P2 2
#define BASERANK 0

void createGroup(MPI_Comm gridComm, MPI_Group* newGroup, int* ranks, int size);
void getRow(MPI_Comm gridComm, int* row);
void getCol(MPI_Comm gridComm, int* col);
int createMatrixes(double** A, double** B, double** C, int sizeA, int sizeB, int sizeC);
void freeAll(MPI_Comm *gridComm, MPI_Comm *commX, MPI_Comm *commY);
void bcastBaseRank(int* baseRank, MPI_Comm comm, int* coords, int myRank, int coord, int limit);
void mulMatrixes(double* A, double* B, double* C);

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    MPI_Comm gridComm;
    int dims[] = {N1 / P1, N3 / P2};
    int periods[] = {0, 0};
    int reorder = 1;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &gridComm);
    int rank, size, coords[2];
    MPI_Comm_rank(gridComm, &rank);
    MPI_Comm_size(gridComm, &size);
    MPI_Cart_coords(gridComm, rank, 2, coords);

    int row[N3 / P2], col[N1 / P1];
    getRow(gridComm, row);
    getCol(gridComm, col);
    MPI_Group groupX, groupY;
    createGroup(gridComm, &groupX, row, N3 / P2);
    createGroup(gridComm, &groupY, col, N1 / P1);
    MPI_Comm commX, commY;
    MPI_Comm_create(gridComm, groupX, &commX);
    MPI_Comm_create(gridComm, groupY, &commY);
    MPI_Group_free(&groupX);
    MPI_Group_free(&groupY);

    double *A = NULL, *B = NULL, *C = NULL;
    double Apart[P1 * N2], Bpart[N2 * P2], Cpart[P1 * P2];
    int error = 0;
    if(rank == BASERANK){
        error = createMatrixes(&A, &B, &C, N1 * N2, N2 * N3, N1 * N3);
        A[0] = 1; A[1] = 2; A[2] = 3; A[3] = 4; A[4] = 5; A[5] = 6; A[6] = 7; A[7] = 8; 
        A[8] = 9; A[9] = 10; A[10] = 11; A[11] = 12; A[12] = 13; A[13] = 14; A[14] = 15; A[15] = 16; 
        B[0] = 1; B[1] = 2; B[2] = 3; B[3] = 4; B[4] = 5; B[5] = 6; B[6] = 7; B[7] = 8; 
        B[8] = 9; B[9] = 10; B[10] = 11; B[11] = 12; B[12] = 13; B[13] = 14; B[14] = 15; B[15] = 16; 
    }
    MPI_Bcast(&error, 1, MPI_INT, BASERANK, MPI_COMM_WORLD);
    if(!error){
        MPI_Finalize();
        return 0;
    }

    MPI_Datatype ROWS;
    MPI_Datatype BCOLUMS;
    MPI_Datatype CBLOCKS;
    MPI_Type_contiguous(P1 * N2, MPI_DOUBLE, &ROWS);
    MPI_Type_vector(N2, P2, N3, MPI_DOUBLE, &BCOLUMS);
    MPI_Type_vector(P1, P2, N3, MPI_DOUBLE, &CBLOCKS);
    MPI_Type_commit(&ROWS);
    MPI_Type_commit(&BCOLUMS);
    MPI_Type_commit(&CBLOCKS);

    if(!(rank % (N3 / P2))){
        MPI_Scatter(A, 1, ROWS, Apart, P1 * N2, MPI_DOUBLE, BASERANK, commY);
    }
    if(rank < N3 / P2){
        if(rank == BASERANK){
            for(int i = 0; i < N3 / P2; ++i){
                MPI_Send(B + i * P2, 1, BCOLUMS, i, 123, commX);
            }
        }
        MPI_Recv(Bpart, N2 * P2, MPI_DOUBLE, BASERANK, 123, commX, MPI_STATUS_IGNORE); 
    }

    MPI_Bcast(Apart, P1 * N2, MPI_DOUBLE, BASERANK, commX);
    MPI_Bcast(Bpart, P2 * N2, MPI_DOUBLE, BASERANK, commY);

    mulMatrixes(Apart, Bpart, Cpart);
    
    MPI_Send(Cpart, P1 * P2, MPI_DOUBLE, BASERANK, 123, gridComm);
    if(rank == BASERANK){
        for(int i = 0; i < N1 / P1; ++i){
            for(int j = 0; j < N3 / P2; ++j){
                MPI_Recv(C + i * P1 * N3 + j * P2, 1, CBLOCKS, i * N3 / P2 + j, 123, gridComm, MPI_STATUS_IGNORE);
            }
        }
    } 

    /*for(int i = 0; i < size; ++i){
        MPI_Barrier(gridComm);
    if(rank == i){
        printf("%d\n", rank);
        for(int j = 0; j < P1; ++j){
            for(int k = 0; k < P2; ++k){
                printf("%.0f ", Cpart[j * P2 + k]);
            }
            printf("\n");
        }
    }
    }*/
    
    if(rank == BASERANK){
        for(int j = 0; j < N1; ++j){
            for(int k = 0; k < N3; ++k){
                printf("%.0f ", C[j * N3 + k]);
            }
            printf("\n");
        }
    }

    MPI_Type_free(&ROWS);
    MPI_Type_free(&BCOLUMS);
    MPI_Type_free(&CBLOCKS);
    freeAll(&gridComm, &commX, &commY);
    MPI_Finalize();

    return 0;
}

void getRow(MPI_Comm gridComm, int* row){
    int rank, coords[2];
    MPI_Comm_rank(gridComm, &rank);
    MPI_Cart_coords(gridComm, rank, 2, coords);
    for(int i = 0; i < N3 / P2; ++i){
        coords[1] = i;
        MPI_Cart_rank(gridComm, coords, row + i);
    }
}

void getCol(MPI_Comm gridComm, int* col){
    int rank, coords[2];
    MPI_Comm_rank(gridComm, &rank);
    MPI_Cart_coords(gridComm, rank, 2, coords);
    for(int i = 0; i < N1 / P1; ++i){
        coords[0] = i;
        MPI_Cart_rank(gridComm, coords, col + i);
    }
}

void createGroup(MPI_Comm gridComm, MPI_Group* newGroup, int* ranks, int size){
    MPI_Group group;
    MPI_Comm_group(gridComm, &group);
    MPI_Group_incl(group, size, ranks, newGroup);
}

int createMatrixes(double** A, double** B, double** C, int sizeA, int sizeB, int sizeC){
    *A = (double*)malloc(sizeof(double) * sizeA);
    *B = (double*)malloc(sizeof(double) * sizeB);
    *C = (double*)malloc(sizeof(double) * sizeC);
    if(!(*A && *B && *C)){
        free(*A);
        free(*B);
        free(*C);
        return 0;
    }
    return 1;
}

void bcastBaseRank(int* baseRank, MPI_Comm comm, int* coords, int myRank, int coord, int limit){
    if(myRank == *baseRank){
        int neighbour;
        for(int i = 0; i < limit; ++i){
            coords[coord] = i;
            MPI_Cart_rank(comm, coords, &neighbour);
            MPI_Send(baseRank, 1, MPI_INT, neighbour, 123, comm);
        }
    } else {
        MPI_Recv(baseRank, 1, MPI_INT, BASERANK, 123, comm, MPI_STATUS_IGNORE);
    }
}

void mulMatrixes(double* A, double* B, double* C){
    for(int i = 0; i < P1; ++i){
        for(int j = 0; j < N2; ++j){
            for(int k = 0; k < P2; ++k){
                C[i * P2 + k] += A[i * N2 + j] * B[j * P2 + k];
            }
        }
    }
}

void freeAll(MPI_Comm *gridComm, MPI_Comm *commX, MPI_Comm *commY){
    MPI_Comm_free(gridComm);
    MPI_Comm_free(commX);
    MPI_Comm_free(commY);
}