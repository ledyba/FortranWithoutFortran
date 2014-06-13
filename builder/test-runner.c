#include "calc.c"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N (1000000)

double readline()
{
	double n;
	scanf("%lf", &n);
	return n;
}

int main(int argc, char** argv)
{
	int n = 0;
	scanf("%d", &n);
	double* datas = malloc(sizeof(double) * N);
	datas[0] = n;
	for( int i=0;i<n;++i ) {
		datas[i+1] = readline();
	}
	ep(datas);
	int const r = (int) datas[0];
	for( int i=0;i<r;++i ) {
		printf("%f %f\n", (double)i/n, datas[i+1]);
	}
	return 0;
}
