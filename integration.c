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
	for(int i = 0; i < N + 1;i++)
	{
		xk[i] = 0.5 * i;
		if(i%2 == 0)
			wk[i] = 0.165;
		else
			wk[i] = 0.67;
		printf("%f , %f\n",xk[i],wk[i]);
	}
	double coef = 0;
	for(int i = 0; i < N + 1; i++)
	{
		coef+= wk[i]*(*f)(a+xk[i]*(b-a));
		printf("coef : %f\n",coef);
	}
	result = (b - a)*coef;
	
	return result;
}



double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
	double lon;
	double aire;
	if(strcmp(qf->name, "Methode 1") == 0){
		lon = f(a);}
	else if(strcmp(qf->name, "Methode 2") == 0){
		lon = f(b);}
	else if(strcmp(qf->name, "Méthode 3") == 0){
		lon = f((a+b)/2);}
	else if(strcmp(qf->name, "Methode 4") == 0){
	        lon = f(a)/2 + f(b)/2;}
	aire = (b-a) * lon;
/*	double paires_subdivs[2];
	double *subdivs[N];
	double a_i;
	double b_i;
	for(int i = 0; i<N; i++){
		a_i = a + i*(b-a)/N;
		b_i = a + (i+1)*(b-a)/N;
		if(b_i - a_i = (b-a)/N)
			return -1;
		paires_subdivs[0] = a_i;
		paires_subdivs[1] = b_i;
		subdivs[i] = paires_subdivs;
	}*/
	return 0.0;
}

