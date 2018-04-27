
#include <assert.h>
#include <math.h>

double nearbyint(double f)
{
	return round(f);
}

double round(double f)
{
	return rint(f);
}

double trunc(double f)
{
	return round(f-0.5);
}

double tgamma(double f)
{
	assert("Gamma function not implemented" != NULL);
	return 0;
}

double log2(double f)
{
	return log(f)/log(2);
}
