#include "integration.h"

double f1(double x)
{
    return x*x;
}

double f2(double x)
{
    return sin(x);
}

int main()
{
    QuadFormula qf;
    setQuadFormula(&qf,"simpson");
    printf("x^2 0-1 = %f\n",integrate_dx(f1,0,1,0.001,&qf));
    printf("sin 0-pi = %f\n",integrate_dx(f2,0,M_PI,0.001,&qf));
    return 0;
}