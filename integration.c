#define INTEGRATION_C
#include "integration.h"

bool setQuadFormula(QuadFormula* qf, char* name)
{
  return true;
}

/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}


/* Approximate the integral of function f from a to b.
   - f is a pointer to a function pointer
   - a and b are the integration bounds
   - Interval [a,b] is split in N subdivisions [ai,bi]
   - Integral of f on each subdivision [ai,bi] is approximated by the quadrature formula qf.
*/
double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
	double result = 0;
	double *(xk) = qf->x;
	double *(wk) = qf->w;
	double coef = 0;
	double ai[N];
	double bi[N];
	for(int i = 0; i < N;i++)
	{
		ai[i] = a + i*((b-a)/N);
		bi[i] = a +((i+1)*((b-a)/N));
	}
	if(strcmp(qf->name,"simpson") == 0)
	{
		for(int i = 0; i < 3;i++)
		{
			xk[i] = 0.5 * i;
			if(i%2 == 0)
				wk[i] = 0.165;
			else
				wk[i] = 0.67;
		}
		for(int j = 0; j < N;j++)
		{
			coef = 0;
			for(int i = 0; i < 3 + 1; i++)
			{
				coef+= wk[i]*((*f)(ai[j] + xk[i]*(bi[j]-ai[j])));
			}
			result += (bi[j] - ai[j])*coef;
			printf("%f\n",result);
		}
	}
	else if(strcmp(qf->name,"gauss2") == 0)
	{
		xk[0] = 0.5 -(1/(2*sqrt(3)));
		xk[1] = 0.5 +(1/(2*sqrt(3)));
		wk[0] = 0.5;
		wk[1] = 0.5;
		for(int j = 0; j < N;j++)
		{
			coef = 0;
			for(int i = 0; i < 2; i++)
			{
				coef+= wk[i]*((*f)(ai[j] + xk[i]*(bi[j]-ai[j])));
			}
			result += (bi[j] - ai[j])*coef;
			printf("%f\n",result);
		}
	}
	else if(strcmp(qf->name,"gauss3") == 0)
	{
		xk[0] = 0.5*(1 - sqrt(3.0/5.0));
		xk[1] = 0.5;
		xk[2] = 0.5*(1 + sqrt(3.0/5.0));
		for(int i = 0; i < 3;i++)
		{
			if(i%2 == 0)
				wk[i] = 5.0/18.0;
			else
				wk[i] = 4.0/9.0;
			printf("%f , %f\n",xk[i],wk[i]);
		}
		for(int j = 0; j < N;j++)
		{
			coef = 0;
			for(int i = 0; i < 3; i++)
			{
				coef+= wk[i]*((*f)(ai[j] + xk[i]*(bi[j]-ai[j])));
			}
			result += (bi[j] - ai[j])*coef;
			printf("%f\n",result);
		}
	}
	return result;
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  return 0.0;
}


