#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//10 20 50 100 1000

#define MIN_ARGUMENTS 5
#define MIN_POINTS 2
#define MAX_FUNCTION 256
#define INDEX_FUNCTION 1
#define INDEX_FIRST_POINT 2
#define INDEX_LAST_POINT 3
#define INDEX_POINTS 4
#define ELEMENT 1
#define REMAIN 1
#define SUCCESS 0
#define FAILURE -1
#define NOTHING 0
#define DELIM " "
#define POLINOM 'P'
#define COS 'c'
#define SIN 's'
#define E 'e'
#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'
#define POW '^'
#define LN 'l'
#define X 'x'
#define PI 'p'
#define FIRST_SYMB 0

#define FIRST_FUNCTION "^ x / 3 2 / ^"
#define FIRST_POINT_1 1
#define FIRST_POINT_2 9
#define FIRST_INTEGRAL 2
#define SECOND_FUNCTION "/ 1.0 ^ x 2.0"
#define SECOND_POINT_1 1
#define SECOND_POINT_2 2
#define SECOND_INTEGRAL 0.5
#define DEFAULT_POINTS 1000

int* getPoints(char** strings, int size);
double getRes(char* function, double x);
double doOperation(char* token, double x);
double getIntegralAverage(const char* function, double firstPoint, double secondPoint, int points);
double getIntegralRight(const char* function, double firstPoint, double secondPoint, int points);
double checkRunge(double (*method)(const char*, double, double, int), const char* function, 
	double firstPoint, double secondPoint, double integral);

int main(int argc, char** argv){
	if(argc < 5){
		fprintf(stderr, "Needs more arguments\nUsage: prog [function] [first point] [last point] [points]\n");
		return EXIT_FAILURE;
	}
	char* function = argv[INDEX_FUNCTION];
	double firstPoint = getRes(argv[INDEX_FIRST_POINT], 0.0);
	double lastPoint = getRes(argv[INDEX_LAST_POINT], 0.0);
	int* points = getPoints(argv, argc - INDEX_POINTS);
	printf("Average:\n");
	for(int i = 0; i < argc - INDEX_POINTS; ++i){
		printf("\t%d points: %.10lf\n", points[i], getIntegralAverage(function, firstPoint, lastPoint, points[i]));
	}
	printf("Right:\n");
	for(int i = 0; i < argc - INDEX_POINTS; ++i){
		printf("\t%d points: %.10lf\n", points[i], getIntegralRight(function, firstPoint, lastPoint, points[i]));
	}
	free(points);
	/*printf("Runge x^(3/2):\n");
	printf("\tAverage: %lf\n", checkRunge(getIntegralAverage, FIRST_FUNCTION, FIRST_POINT_1, FIRST_POINT_2, 
		FIRST_INTEGRAL));
	printf("\tRight: %lf\n", checkRunge(getIntegralRight, FIRST_FUNCTION, FIRST_POINT_1, FIRST_POINT_2, 
		FIRST_INTEGRAL));
	printf("Runge 1/(x^2):\n");
	printf("\tAverage: %lf\n", checkRunge(getIntegralAverage, SECOND_FUNCTION, SECOND_POINT_1, SECOND_POINT_2, 
		SECOND_INTEGRAL));
	printf("\tRight: %lf\n", checkRunge(getIntegralRight, SECOND_FUNCTION, SECOND_POINT_1, SECOND_POINT_2, 
		SECOND_INTEGRAL));*/
	return EXIT_SUCCESS;
}

double checkRunge(double (*method)(const char*, double, double, int), const char* function, 
	double firstPoint, double secondPoint, double integral){
	double nominator = method(function, firstPoint, secondPoint, DEFAULT_POINTS) - method(function, firstPoint, secondPoint, DEFAULT_POINTS * 2);
	nominator = (nominator < 0) ? -nominator : nominator;
	double denominator = method(function, firstPoint, secondPoint, DEFAULT_POINTS * 2) - method(function, firstPoint, secondPoint, DEFAULT_POINTS * 4);
	denominator = (denominator < 0) ? -denominator : denominator;
	return log2(nominator / denominator);
}

double getIntegralAverage(const char* function, double firstPoint, double secondPoint, int points){
	if(points < MIN_POINTS){
		return 0.0;
	}
	double step = (secondPoint - firstPoint) / points;
	double res = 0.0;
	double nextPoint = firstPoint + step / 2;
	char buf[MAX_FUNCTION];
	for(int i = 0; i < points; ++i){
		strcpy(buf, function);
		res += step * getRes(buf, nextPoint);
		nextPoint += step;
	}
	return res;
}
double getIntegralRight(const char* function, double firstPoint, double secondPoint, int points){
	if(points < MIN_POINTS){
		return 0.0;
	}
	double step = (secondPoint - firstPoint) / points;
	double res = 0.0;
	double nextPoint = firstPoint + step;
	char buf[MAX_FUNCTION];
	for(int i = 0; i < points; ++i){
		strcpy(buf, function);
		res += getRes(buf, nextPoint);
		nextPoint += step;
	}
	return step * res;
}

int* getPoints(char** strings, int size){
	int* points = (int*)malloc(sizeof(int) * size);
	if(!points){
		return NULL;
	}
	for(int i = 0; i < size; ++i){
		points[i] = atoi(strings[INDEX_POINTS + i]);
	}
	return points;
}

double getRes(char* function, double x){
	char* token = strtok(function, DELIM);
	return doOperation(token, x);
}

double doOperation(char* token, double x){
	double res = 0.0;
	double first, second;
	switch(token[FIRST_SYMB]){
		case POLINOM :
			token = strtok(NULL, DELIM);
			while(token[FIRST_SYMB] != POLINOM){
				res = res * x + atof(token);
				token = strtok(NULL, DELIM);
			}
			return res;
		case COS:
			token = strtok(NULL, DELIM);
			while(token[FIRST_SYMB] != COS){
				res += doOperation(token, x);
				token = strtok(NULL, DELIM);
			}
			return cos(res);
		case SIN:
			token = strtok(NULL, DELIM);
			while(token[FIRST_SYMB] != SIN){
				res += doOperation(token, x);
				token = strtok(NULL, DELIM);
			}
			return sin(res);
		case ADD:
			token = strtok(NULL, DELIM);
			first = doOperation(token, x);
			token = strtok(NULL, DELIM);
			second = doOperation(token, x);
			return first + second;
		case SUB:
			token = strtok(NULL, DELIM);
			first = doOperation(token, x);
			token = strtok(NULL, DELIM);
			second = doOperation(token, x);
			return first - second;
		case MUL:
			token = strtok(NULL, DELIM);
			first = doOperation(token, x);
			token = strtok(NULL, DELIM);
			second = doOperation(token, x);
			return first * second;
		case DIV:
			token = strtok(NULL, DELIM);
			first = doOperation(token, x);
			token = strtok(NULL, DELIM);
			second = doOperation(token, x);
			return first / second;
		case POW:
			token = strtok(NULL, DELIM);
			first = doOperation(token, x);
			token = strtok(NULL, DELIM);
			second = doOperation(token, x);
			return pow(first, second);
		case LN:
			token = strtok(NULL, DELIM);
			while(token[FIRST_SYMB] != LN){
				res += doOperation(token, x);
				token = strtok(NULL, DELIM);
			}
			return log(res);
		case X:
			return x;
		case E:
			return M_E;
		case PI:
			return M_PI;
		default:
			return atoi(token);
	}
}

