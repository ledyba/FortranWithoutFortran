void start()
{}

#include "./lib.c"

#define PI (fpi())

static double sum(double const*const x, int const size)
{
	double s = 0;
	for( int i=0; i<size; ++i ){
		s += x[i];
	}
	return s;
}
static double sumCross(double const*const x, double const*const y, int const size)
{
	double s = 0;
	for( int i=0; i<size; ++i ){
		s += x[i] * y[i];
	}
	return s;
}
static double sumSq(double const*const x, int const size)
{
	return sumCross(x,x,size);
}

static double avg(double const*const x, int const size)
{
	return sum(x,size) / size;
}

static double cov(double const*const x, double const*const y, int const size)
{
	double s = 0;
	for( int i=0;i<size;++i ){
		s += x[i] * y[i];
	}
	return (s/size) - avg(x,size)*avg(y,size);
}

double calcSy(double const*const x, double const*const y, int const size, double a, double b)
{
	double s = 0;
	for( int i=0; i<size; ++i ){
		double v = (a * x[i] + b ) - y[i];
		s += v * v;
	}
	return s / (size-2);
}

void lsfit(double const*const x, double const*const y, int const size, double* a, double* b, double* t)
{
	double avgX = avg(x,size);
	double avgY = avg(y,size);
	double avgX2 = sumSq(x,size) / size;
	double avgXY = sumCross(x,y,size) / size;
	*a = (avgXY - (avgX * avgY)) / (avgX2 - (avgX * avgX));
	*b = (avgX2 * avgY - (avgX * avgXY)) / (avgX2 - (avgX * avgX));
	if(t){
		double sy = calcSy(x, y, size, *a, *b);
		double sa = sy / (size * (avgX2 - (avgX*avgX)));
		*t = fabs(*a) / fsqrt(sa);
	}
}

void tape(double const * const in, double * const out , int const size)
{
	int const n = size / 10;
	for(int i=0; i < size; ++i){
		out[i] = in[i];
	}
	for(int i=0; i < n; ++i){
		out[i] = in[i] * (0.5 - 0.5 * fcos(2*PI*i / (2*n-1)));
	}
	for(int i=0; i < n; ++i){
		out[size-n+i] = in[size-n+i] * (0.5 - 0.5 * fcos(2*PI*(n+i) / (2*n-1)));
	}
}

void spect(double const * const in, double * const out, int const size, int const count)
{
	for(int c=0; c < count; ++c) {
		double a=0;
		double b=0;
		for(int i=0; i < size; ++i){
			a += in[i] * fcos(2.0*PI*c*i/size);
			b += in[i] * fsin(2.0*PI*c*i/size);
		}
		a /= size;
		b /= size;
		out[c] = fsqrt(a*a + b*b) * size;
	}
}

double getItem(double const * const in, int const idx, int const size)
{
	if(idx < 0){
		return in[0];
	}else if(idx >= size){
		return in[size-1];
	}else{
		return in[idx];
	}
}

void flatAvg(double const * const in, double * const out, int const size, int const count)
{
	const int base = -count/2;
	for(int c=0; c < size; ++c) {
		double s = 0;
		for( int i = 0; i<count;++i) {
			s = s + getItem(in, c+base+i, size);
		}
		out[c] = s / size;
	}
}

int ep(double* ptr)
{
	int const n = (int) ptr[0];
	double* ys = &ptr[1];
	double* xs = &ptr[n+1];
	double* ys2 = &ptr[2*n+1];
	double* ys3 = &ptr[3*n+1];
	double* spec = &ptr[4*n+1];
	double* specAvg = &ptr[6*n+1];

	double* specD = &ptr[7*n+1];
	double* specU = &ptr[8*n+1];
	for(int i=0; i< n; ++i)
	{
		xs[i] = i;
	}
	double a,b;
	lsfit(xs,ys,n,&a,&b,0);
	for(int i=0; i< n; ++i)
	{
		ys2[i] = ys[i] - (i*a + b);
	}
	tape(ys2, ys3, n);
	spect(ys3, spec, n, n);
	flatAvg(spec, specAvg, n, 20);

	const int items = n/2;
	ptr[0] = items; //要素数
	for(int i=0; i< items; ++i)
	{
		ptr[i+1] = specAvg[i] /*結果の出力*/;
	}
	return 0;
}

void end()
{}

