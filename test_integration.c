/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods and show your numericzal results */
double f(double x)
{
	double result = 15*x*sqrt((3*x)/2);
	return result;
}
int main()
{
	double (*fun)(double) = &f;
	double a = 0;
	double b = 1;
	int n = 23;
	char *na = "simpson";
	printf("%f\n",(*fun)(2));
	QuadFormula *k = malloc(sizeof(QuadFormula));
	for(int i = 0 ; i < 7;i++)
		k->name[i] = na[i];
	double result = integrate(fun,a,b,n,k);
	printf("%f\n",result);
	return 0;
}
