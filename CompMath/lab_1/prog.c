#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define E 0.001
#define STARTING_LENGTH 20.0
#define STEP 3.8
#define TRUE 1
#define FALSE 0

int getCoefs(double *a, double *b, double *c);
void getInterval(double *alfa, double *beta, double a, double b, double c);
void getIntervalFromInfinity(double *alfa, double *beta, int signInf, double a, double b, double c);
double func(double a, double b, double c, double x);
double getRoot(double alfa, double beta, double a, double b, double c);

int main(){
	double a, b, c;
	if(!getCoefs(&a, &b, &c)){
		printf("Wrong coefficients\nWrite only numbers with type double");
		return 0;
	}
	printf("Entered: %lf %lf %lf\n", a, b, c);
	double d = a * a - 3 * b;
	double alfa, beta;
	if(d <= 0){
		getInterval(&alfa, &beta, a, b, c);
		printf("Result: %lf\n", getRoot(alfa, beta, a, b, c));
	}
	else{
		alfa = (sqrt(d) - a) / 3;
		beta = (-sqrt(d) - a) / 3;
		if(alfa > beta){
			double tmp = alfa;
			alfa = beta;
			beta = tmp;
		}
		double funcAlfa = func(a, b, c, alfa);
		double funcBeta = func(a, b, c, beta);
		if((funcAlfa > E && funcBeta > E) || (funcAlfa < -E && funcBeta < -E)){
			getIntervalFromInfinity(&alfa, &beta, -1, a, b, c);
			printf("Result: %lf\n", getRoot(alfa, beta, a, b, c));
		}
		else if((funcAlfa > E && funcBeta < -E) || (funcAlfa < -E && funcBeta > E)){
			printf("Result 1: %lf\n", getRoot(alfa, beta, a, b, c));
			double tmpAlfa = alfa, tmpBeta = beta;
			getIntervalFromInfinity(&alfa, &beta, -1, a, b, c);
			printf("Result 2: %lf\n", getRoot(alfa, beta, a, b, c));
			alfa = tmpAlfa;
			beta = tmpBeta;
			//printf("%lf %lf\n", alfa, beta);
			getIntervalFromInfinity(&alfa, &beta, 1, a, b, c);
			printf("Result 3: %lf\n", getRoot(alfa, beta, a, b, c));
		}
		else if((funcAlfa > E || funcAlfa < -E) && funcBeta < E && funcBeta > -E){
			printf("Result 1: %lf\n", beta);
			getIntervalFromInfinity(&alfa, &beta, -1, a, b, c);
			printf("Result 2: %lf\n", getRoot(alfa, beta, a, b, c));
		}
		else if(funcAlfa > -E && funcAlfa < E && (funcBeta > E || funcBeta < -E)){
			printf("Result 1: %lf\n", alfa);
			getIntervalFromInfinity(&alfa, &beta, 1, a, b, c);
			printf("Result 2: %lf\n", getRoot(alfa, beta, a, b, c));
		}
		else if(funcAlfa > -E && funcAlfa < E && funcBeta < E && funcBeta > -E){
			printf("Result : %lf\n", (alfa + beta) / 2);
		}
	}
	return 0;
}

int getCoefs(double *a, double *b, double *c){
	int value;
	printf("Enter a:\n");
	if((value = scanf("%lf", a)) == EOF || value < 1){
		return FALSE;
	}
	printf("Enter b:\n");
	if((value = scanf("%lf", b)) == EOF || value < 1){
		return FALSE;
	}
	printf("Enter c:\n");
	if((value = scanf("%lf", c)) == EOF || value < 1){
		return FALSE;
	}
	return TRUE;
}


void getInterval(double *alfa, double *beta, double a, double b, double c){
	*beta = STARTING_LENGTH;
	*alfa = -1 * (*beta);
	double funcAlfa, funcBeta;
	int sign = (func(a, b, c, *alfa) < func(a, b, c, *beta)) ? 1 : -1;
	while(!((funcAlfa = func(a, b, c, *alfa) * sign) < 0 && 
	(funcBeta = func(a, b, c, *beta) * sign) > 0)){
		*alfa -= (funcAlfa < 0) ? 0 : STEP;
		*beta += (funcBeta > 0) ? 0 : STEP;
	}
}

void getIntervalFromInfinity(double *alfa, double *beta, int signInfinity, double a, double b, double c){
	if(signInfinity >= 0){
		*alfa = *beta;
		*beta = *alfa + STEP;
		signInfinity = 1;
	} else {
		*beta = *alfa;
		*alfa = *beta - STEP;
		signInfinity = -1;
	}
	double funcAlfa, funcBeta;
	while(!(((funcAlfa = func(a, b, c, *alfa)) < 0 && 
	(funcBeta = func(a, b, c, *beta)) > 0) ||
	(funcAlfa > 0 && funcBeta < 0))){
		*alfa += signInfinity * STEP;
		*beta += signInfinity * STEP;
	}
}

double getRoot(double alfa, double beta, double a, double b, double c){
	double root, funcRoot;
	int sign = (func(a, b, c, alfa) < func(a, b, c, beta)) ? 1 : -1;
	do{
		//printf("%lf %lf %lf %lf\n", alfa, beta, func(a, b, c, alfa), func(a, b, c, beta));
		//sleep(1);
		root = (alfa + beta) / 2;
		funcRoot = func(a, b, c, root) * sign;
		if(funcRoot == 0){
			break;
		}
		if(funcRoot < 0){
			alfa = root;
		}
		else{
			beta = root;
		}
	}while(!(funcRoot < E && funcRoot > -1 * E)/* && beta - alfa > E*/);
	printf("func: %lf\n", funcRoot);
	return root;
}

double func(double a, double b, double c, double x){
	return c + (b + (a + x) * x) * x;
}