/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods and show your numericzal results */
double f(double x)
{
	double result = 2*x;
}
int main()
{
	double (*fun)(double) = &f;
	double a = 0;
	double b = 1;
	int n = 1;
	QuadFormula *k = malloc(sizeof(QuadFormula));
	double result = integrate(fun,a,b,n,k);
	printf("%f\n",result);
	return 0;
}
