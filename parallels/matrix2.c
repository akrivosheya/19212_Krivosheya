#include <stdio.h>
#include <math.h>
#include "mpi.h"

#define N 15
#define E 0.00001
#define T 0.01

void MultiplicationMatrix(double* matrix, double* vector, double* res, int ownRows, int anotherRows, int offset);
void MultiplicationCoef(double* oldX, int rows);
void Addition(double* a, double* b, int rows);
void Subtraction(double* deductible, double* subtractor, int rows, int extraRowsForDed, int extraRowsForSub);
void GetSum(double* vector, double* sum, int rows);
void Clear(double* vector, int rows);
void PrintRes(double* res, int rows);
void Set(double* first, double* second, int rows);

int main (int argc, char** argv){
    MPI_Init(&argc, &argv);
    int ownRank, anotherRank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &ownRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    int minRows = N / size;
    int difference = N - minRows * size;
    int anotherRows, ownRows = ((ownRank >= (size - difference)) ? (N / size) + 1: (N / size));
    int extraRow = (ownRank >= (size - difference)) ? 1 : 0;
    int offset = extraRow * (ownRank - size + difference) + minRows * ownRank;
    double A[N * ownRows];
    double b[ownRows], x[minRows + 1];
    double ownX[ownRows], bufX[ownRows], xForSum[ownRows];
    double moduleB = 0.0;

    for(int i = 0; i < minRows + 1; ++i){
        b[i] = N + 1.0;
        x[i] = 0.0;
    }

    double ownSum = 0.0, sum = 0.0, anotherSum = 0.0;
    GetSum(b, &ownSum, ownRows);
    MPI_Allreduce(&ownSum, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    moduleB = sqrt(sum);

    for(int i = 0; i < ownRows; ++i){
        for(int j = 0; j < N; ++j){
            if(i + offset == j){
                A[i * N + j] = 2.0;
            }
            else{
                A[i * N + j] = 1.0;
            }
        }
    }

    
    anotherRank = ownRank;
    anotherRows = ownRows;
    Clear(ownX, ownRows);
    for(int i = 0; i < size; ++i){
        MultiplicationMatrix(A, x, xForSum, ownRows, anotherRows, anotherRank * minRows + 
                            ((anotherRank >= (size - difference)) ? anotherRank - size + difference : 0));
        Addition(ownX, xForSum, ownRows);
        MPI_Sendrecv_replace(x, minRows + 1, MPI_DOUBLE,
                                (ownRank + 1) % size, 123, (ownRank + size - 1) % size, 123,
                                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        anotherRank = (anotherRank + size - 1) % size;
        anotherRows = (anotherRank >= (size - difference)) ? (N / size) + 1: N / size;
    }
    Subtraction(ownX, b, ownRows, 0, 0);
    Set(bufX, ownX, ownRows);
    do {
        MultiplicationCoef(bufX, ownRows);
        Subtraction(x, bufX, ownRows, 0, 0);
        anotherRank = ownRank;
        anotherRows = ownRows;
        Clear(ownX, ownRows);
        for(int i = 0; i < size; ++i){
            MultiplicationMatrix(A, x, xForSum, ownRows, anotherRows, anotherRank * minRows + 
                                ((anotherRank >= (size - difference)) ? anotherRank - size + difference : 0));
            Addition(ownX, xForSum, ownRows);
            MPI_Sendrecv_replace(x, minRows + 1, MPI_DOUBLE,
                                    (ownRank + 1) % size, 123, (ownRank + size - 1) % size, 123,
                                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            anotherRank = (anotherRank + size - 1) % size;
            anotherRows = (anotherRank >= (size - difference)) ? (N / size) + 1: N / size;

        }
        Subtraction(ownX, b, ownRows, 0, 0);
        Set(bufX, ownX, ownRows);
        anotherSum = ownSum = sum = 0;
        GetSum(ownX, &ownSum, ownRows);
        MPI_Allreduce(&ownSum, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    } while(sqrt(sum) / moduleB >= E);

    for (int i = 0; i < size; ++i){ 
        MPI_Barrier(MPI_COMM_WORLD);
        if (ownRank == i){
             PrintRes(x, ownRows);
        }
    }

    
    MPI_Finalize();
}

void MultiplicationMatrix(double* matrix, double* vector, double* res, int ownRows, int anotherRows, int offset){
    for(int i = 0; i < ownRows; ++i){
        res[i] = 0.0;
    }
    for(int i = 0; i < ownRows; ++i){
        for(int j = 0; j < anotherRows; ++j){
            res[i] += matrix[i * N + j + offset] * vector[j];
        }
    }
}

void MultiplicationCoef(double* oldX, int rows){
    for(int i = 0; i < rows; ++i){
        oldX[i] *= T;
    }
}

void Subtraction(double* deductible, double* subtractor, int rows, int extraRowsForDed, int extraRowsForSub){
    for(int i = 0; i < rows; ++i){
        deductible[i + extraRowsForDed] -= subtractor[i + extraRowsForSub];
    }
}

void Addition(double* a, double* b, int rows){
    for(int i = 0; i < rows; ++i){
        a[i] += b[i];
    }
}

void GetSum(double* vector, double* sum, int rows){
    for(int i = 0; i < rows; ++i){
        *sum += vector[i] * vector[i];
    }
}

void Clear(double* vector, int rows){
    for(int i = 0; i < rows; ++i){
        vector[i] = 0.0;
    }
}

void PrintRes(double* res, int rows){
    for(int i = 0; i < rows; ++i){
        printf("%f\n", res[i]);
    }
}

void Set(double* first, double* second, int rows){
    for(int i = 0; i < rows; ++i){
        first[i] = second[i];
    }
}