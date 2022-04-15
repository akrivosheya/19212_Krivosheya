#include <stdio.h>
#include <stdlib.h>

#define START_CUT 3
#define STEP 0.1
#define LAST_POINT 10
#define FIRST_POINT 0
#define DELIM 125
#define R 1.25

double getStartingRes(int x);
double getRes(int point, int pointsSize);
int getNormalInt(double badDouble);

int main(){
	double timeStep = R * STEP;
	printf("0\t1\t5\t\n");
	for(int i = 0; i <= 100; ++i){
		printf("%.10lf\t%.10lf\t%.10lf\t%.10lf\n", i * STEP, getRes(i, 0), getRes(i, 1 + 1000 / DELIM), getRes(i, 1 + 5000 / DELIM));
		/*printf("%lf\t", i * STEP);
		for(int j = 5; j <= 5; ++j){
			printf("%lf\t", getRes(34, j));
		}
		printf("\n");*/
	}
	printf("\t1\n");
	for(int i = 0; i <= 100; ++i){
		printf("%.10lf\n", getRes(i, 1 + 1000 / DELIM));
	}
	printf("\t2\n");
	for(int i = 0; i <= 100; ++i){
		printf("%.10lf\n", getRes(i, 1 + 5000 / DELIM));
	}
}

double getRes(int point, int pointsSize){
	if(pointsSize == 0){
		pointsSize = 1;
	}
	double *points = (double*)malloc(sizeof(double) * pointsSize);
	double *previousPoints = (double*)malloc(sizeof(double) * pointsSize);
	double *tmp;
	int nextTime = 0;
	int limit = 1;
	for(int i = 0; i < pointsSize; ++i){
		previousPoints[i] = getStartingRes(point - i);
	}
	/*for(int i = 0; i < pointsSize; ++i){
		printf("%d\t%lf\n", 0, previousPoints[i]);
	}*/
	for(;nextTime < pointsSize - 1; ++nextTime){
		for(int i = 0; i < pointsSize - limit; ++i){
			/*if(i == 0){
				for(int j = 0; j < pointsSize - limit + 1; ++j){
					printf("%d\t%lf\n", nextTime + 1, previousPoints[j]);
				}
			}*/
			points[i] = previousPoints[i] - R * (previousPoints[i] - previousPoints[i + 1]);
		}
		tmp = points;
		points = previousPoints;
		previousPoints = tmp;
		++limit;
	}
	double value = previousPoints[0];
	free(points);
	free(previousPoints);
	return value;
}

int getNormalInt(double badDouble){
	int normalInt = 0;
	while(0 < badDouble){
		++normalInt;
		badDouble -= 1.0;
	}
	return normalInt;
}

double getStartingRes(int x){
	if(x <= 30){
		return 5;
	}
	else{
		return 1;
	}
}