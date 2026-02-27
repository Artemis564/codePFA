#include "pfa.h"

int main()
{
    init_integration("simpson",0.0001);
    Option opt;
    opt.type=CALL;
    opt.S0=100;
    opt.K=100;
    opt.T=1;
    opt.mu=0.05;
    opt.sig=0.2;
    printf("Option price = %f\n",optionPrice(&opt));
    double p[3]={0.7,0.2,0.1};
    init_integration("trapezes",100);
    InsuredClient c;
    c.m=6;
    c.s=0.5;
    c.p=p;
    for(int i = 100; i < 1001 ; i+=100)
    {
    	printf("CDF S(%d) = %f\n",i,clientCDF_S(&c,i));
    }
    return 0;
}
