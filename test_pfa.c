#include "pfa.h"

int main()
{
    init_integration("simpson",0.0001);
    Option opt;
    opt.type=PUT;
    opt.S0=100;
    opt.K=114;
    opt.T=2;
    opt.mu=0.05;
    opt.sig=0.02;
    printf("Option price = %f\n",optionPrice(&opt));
    double p[3]={0.9,0.05,0.05};
    init_integration("left",1000);
    InsuredClient c;
    c.m=1;
    c.s=1;
    c.p=p;
    for(int i = 0; i < 4 ; i++)
    {
    	printf("CDF S(%d) = %f\n",i,clientCDF_S(&c,i));
    }
    return 0;
}
