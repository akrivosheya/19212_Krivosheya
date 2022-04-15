#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 16
#define THREADS 4
#define E 0.00001
#define T 0.01

void MultiplicationMatrix(double* matrix, double* vector, double* res);
void MultiplicationCoef(double* oldX);
void Subtruction(double* deductible, double* subtractor);
double GetSum(double* vector);
void PrintRes(double* res);
void Set(double* first, double* second);

void GetInBrackets(double* res, double* matrix, double* vector, double* subtractor);
void GetNewX(double* oldX, double* subtractor);

int main (int argc, char** argv){

    double b[N], x[N];
    double A[N * N];
    double xForMul[N];
    double moduleB = 0.0;

    omp_set_num_threads(THREADS);
    #pragma omp parallel for
        for(int i = 0; i < N; ++i){
            b[i] = N + 1.0;
            x[i] = 0;
        }
    moduleB = sqrt(GetSum(b));

    #pragma omp parallel for
        for(int i = 0; i < N * N; ++i){
            if(i % N == i / N){
                A[i] = 2.0;
            }
            else{
                A[i] = 1.0;
            }
        }

    GetInBrackets(xForMul, A, x, b);

    double sum;
    do{
        GetNewX(x, xForMul);
        GetInBrackets(xForMul, A, x, b);
        sum = GetSum(xForMul);
    } while(sqrt(sum) / moduleB >= E);

    PrintRes(x);
}

void GetInBrackets(double* res, double* matrix, double* vector, double* subtractor){
    MultiplicationMatrix(matrix, vector, res);
    Subtruction(res, subtractor);
}

void GetNewX(double* oldX, double* subtractor){
    MultiplicationCoef(subtractor);
    Subtruction(oldX, subtractor);
}

void MultiplicationMatrix(double* matrix, double* vector, double* res){
    #pragma omp parallel for
        for(int i = 0; i < N; ++i){
            res[i] = 0.0;
        }
    #pragma omp parallel for shared(vector)
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                res[i] += matrix[i * N + j] * vector[j];
            }
        }
}

void MultiplicationCoef(double* oldX){
    #pragma omp parallel for
        for(int i = 0; i < N; ++i){
            oldX[i] *= T;
        }
}

void Subtruction(double* deductible, double* subtractor){
    #pragma omp parallel for
        for(int i = 0; i < N; ++i){
            deductible[i] -= subtractor[i];
        }
}

double GetSum(double* vector){
    double sum = 0.0;
    #pragma omp parallel for reduction (+:sum)
        for(int i = 0; i < N; ++i){
            sum += vector[i] * vector[i];
        }
    return sum;
}

void PrintRes(double* res){
    for(int i = 0; i < N; ++i){
        printf("%f\n", res[i]);
    }
}