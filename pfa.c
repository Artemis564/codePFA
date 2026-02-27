#define PFA_C
#include "pfa.h"

bool init_integration(char* quadrature,double dt)
{
    setQuadFormula(&pfaQF,quadrature);
    pfa_dt=dt;
    return true;
}

double phi(double x)
{
    return 0.398942280401433*exp(-x*x/2);
}

double PHI(double x)
{
    return integrate_dx(phi,-10,x,pfa_dt,&pfaQF);
}

double optionPrice(Option* option)
{
    double d1=(log(option->S0/option->K)+(option->mu+option->sig*option->sig/2)*option->T)/(option->sig*sqrt(option->T));
    double d2=d1-option->sig*sqrt(option->T);
    double call=option->S0*PHI(d1)-option->K*exp(-option->mu*option->T)*PHI(d2);
    if(option->type==CALL)
        return call;
    else
        return call+option->K*exp(-option->mu*option->T)-option->S0;
}

double clientPDF_X(InsuredClient* client,double x)
{
    if(x<=0) return 0.0;
    return 1.0/(x*client->s*sqrt(2*M_PI))*exp(-(log(x)-client->m)*(log(x)-client->m)/(2*client->s*client->s));
}

double clientCDF_X(InsuredClient* client,double x)
{
    if(x<=0) return 0.0;
    return PHI((log(x)-client->m)/client->s);
}

static InsuredClient* localClient;
static double localX;

static double localProductPDF(double t)
{
    return clientPDF_X(localClient,localX-t)*clientPDF_X(localClient,t);
}

static double localPDF_X1X2(double x)
{
    localX=x;
    return integrate_dx(localProductPDF,0,x,pfa_dt,&pfaQF);
}

double clientPDF_X1X2(InsuredClient* client,double x)
{
    if(x<=0) return 0.0;
    localClient=client;
    return localPDF_X1X2(x);
}

double clientCDF_X1X2(InsuredClient* client,double x)
{
    localClient=client;
    return integrate_dx(localPDF_X1X2,0,x,pfa_dt,&pfaQF);
}

double clientCDF_S(InsuredClient* client,double x)
{
    double p0=client->p[0];
    double p1=client->p[1];
    double p2=client->p[2];
    return p0+p1*clientCDF_X(client,x)+p2*clientCDF_X1X2(client,x);
}