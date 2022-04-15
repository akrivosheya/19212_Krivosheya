#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define N 15
#define E 0.00001
#define T 0.01

void MultiplicationMatrix(double* matrix, double* vector, double* res, int rows);
void MultiplicationCoef(double* oldX, int rows);
void Subtruction(double* deductible, double* subtractor, int rows, int extraRowsForDed, int extraRowsForSub);
void GetSum(double* vector, double* sum, int rows);
void PrintRes(double* res);
void Set(double* first, double* second, int rows, int offsetForFirst, int offsetForSecond);

int main (int argc, char** argv){
    MPI_Init(&argc, &argv);
    int myRank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    double b[N], x[N];
    int minRows = N / size;
    int maxRows = minRows + 1;
    int difference = N - minRows * size;
    int rows = ((myRank >= (size - difference)) ? (N / size) + 1: (N / size));
    int extraRow = (myRank >= (size - difference)) ? 1 : 0;
    int offset = extraRow * (myRank - size + difference) + minRows * myRank;
    double A[N * rows];
    double ownX[maxRows], bufX[maxRows];
    double xForAllGather[maxRows * size];
    double moduleB = 0.0;

    for(int i = 0; i < N; ++i){
        b[i] = N + 1.0;
        x[i] = 0;
    }
    GetSum(b, &moduleB, N);
    moduleB = sqrt(moduleB);

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < N; ++j){
            if(i + offset == j){
                A[i * N + j] = 2.0;
            }
            else{
                A[i * N + j] = 1.0;
            }
        }
    }

    double ownSum, sum, anotherSum;
    MultiplicationMatrix(A, x, ownX, rows);
    Subtruction(ownX, b, rows, 0, offset);
    Set(bufX, ownX, rows, 0, 0);
    do {
        MultiplicationCoef(bufX, rows);
        Subtruction(x, bufX, rows, offset, 0);
        Set(ownX, x, rows, 0, offset);
        MPI_Allgather(ownX, maxRows, MPI_DOUBLE, xForAllGather, maxRows, MPI_DOUBLE, MPI_COMM_WORLD);
        for(int i = 0; i < size; ++i){
            Set(x, xForAllGather, ((i >= (size - difference)) ? (N / size) + 1: (N / size)), 
                ((i >= size - difference) ? 1 : 0) * (i - size + difference) + minRows * i, i * maxRows);
        }
        MultiplicationMatrix(A, x, ownX, rows);
        Subtruction(ownX, b, rows, 0, offset);
        Set(bufX, ownX, rows, 0, 0);
        anotherSum = ownSum = sum = 0;
        GetSum(ownX, &ownSum, rows);
        MPI_Allreduce(&ownSum, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    } while(sqrt(sum) / moduleB >= E);

    if(myRank == 0){
        PrintRes(x);
    }
    
    MPI_Finalize();
}

void MultiplicationMatrix(double* matrix, double* vector, double* res, int rows){
    for(int i = 0; i < rows; ++i){
        res[i] = 0.0;
    }
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < N; ++j){
            res[i] += matrix[i * N + j] * vector[j];
        }
    }
}

void MultiplicationCoef(double* oldX, int rows){
    for(int i = 0; i < rows; ++i){
        oldX[i] *= T;
    }
}

void Subtruction(double* deductible, double* subtractor, int rows, int extraRowsForDed, int extraRowsForSub){
    for(int i = 0; i < rows; ++i){
        deductible[i + extraRowsForDed] -= subtractor[i + extraRowsForSub];
    }
}

void GetSum(double* vector, double* sum, int rows){
    for(int i = 0; i < rows; ++i){
        *sum += vector[i] * vector[i];
    }
}

void PrintRes(double* res){
    for(int i = 0; i < N; ++i){
        printf("%f\n", res[i]);
    }
}

void Set(double* first, double* second, int rows, int offsetForFirst, int offsetForSecond){
    for(int i = 0; i < rows; ++i){
        first[i + offsetForFirst] = second[i + offsetForSecond];
    }
}