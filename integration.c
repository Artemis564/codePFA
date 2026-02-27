#define INTEGRATION_C
#include "integration.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

bool setQuadFormula(QuadFormula* qf, char* name)
{
	strncpy(qf->name, name, 20);
	qf->name[19] = '\0';
	return true;
}

void printQuadFormula(QuadFormula* qf)
{
	printf("Quadrature formula: %s\n", qf->name);
}

double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
	double result = 0;
	double ai[N];
	double bi[N];
	double h = (b - a) / N;
	for(int i = 0; i < N; i++)
	{
		ai[i] = a + i*h;
		bi[i] = a + (i+1)*h;
	}
	double xk[3], wk[3], coef;

	if(strcmp(qf->name, "simpson") == 0)
	{
		xk[0] = 0.0; xk[1] = 0.5; xk[2] = 1.0;
		wk[0] = 1.0/6.0; wk[1] = 4.0/6.0; wk[2] = 1.0/6.0;
		for(int j = 0; j < N; j++)
		{
			coef = 0;
			for(int i = 0; i < 3; i++)
				coef += wk[i] * f(ai[j] + xk[i]*(bi[j]-ai[j]));
			result += (bi[j]-ai[j])*coef;
		}
	}
	else if(strcmp(qf->name, "gauss2") == 0)
	{
		xk[0] = 0.5 - 1.0/(2*sqrt(3.0));
		xk[1] = 0.5 + 1.0/(2*sqrt(3.0));
		wk[0] = 0.5; wk[1] = 0.5;
		for(int j = 0; j < N; j++)
		{
			coef = 0;
			for(int i = 0; i < 2; i++)
				coef += wk[i] * f(ai[j] + xk[i]*(bi[j]-ai[j]));
			result += (bi[j]-ai[j])*coef;
		}
	}
	else if(strcmp(qf->name, "gauss3") == 0)
	{
		xk[0] = 0.5*(1 - sqrt(3.0/5.0));
		xk[1] = 0.5;
		xk[2] = 0.5*(1 + sqrt(3.0/5.0));
		wk[0] = 5.0/18.0; wk[1] = 4.0/9.0; wk[2] = 5.0/18.0;
		for(int j = 0; j < N; j++)
		{
			coef = 0;
			for(int i = 0; i < 3; i++)
				coef += wk[i] * f(ai[j] + xk[i]*(bi[j]-ai[j]));
			result += (bi[j]-ai[j])*coef;
		}
	}
	else if(strcmp(qf->name, "left") == 0)
	{
		for(int j = 0; j < N; j++)
			result += f(ai[j]) * h;
	}
	else if(strcmp(qf->name, "right") == 0)
	{
		for(int j = 0; j < N; j++)
			result += f(bi[j]) * h;
	}
	else if(strcmp(qf->name, "middle") == 0)
	{
		for(int j = 0; j < N; j++)
			result += f((ai[j]+bi[j])/2.0) * h;
	}
	else if(strcmp(qf->name, "trapezes") == 0)
	{
		for(int j = 0; j < N; j++)
		{
			coef = 0;
			for(int i = 0 ; i < 2 ;i++)
			{
				if(i == 0)
					coef += 0.5*f(ai[j]);
				else
					coef += 0.5*f(bi[j]);	
			}
			result += (bi[j]-ai[j])*coef;
		};
	}
	printf("%f\n",result);
	return result;
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
	int N = (int)round(fabs(b-a)/dx);
	return integrate(f, a, b, N, qf);
}
