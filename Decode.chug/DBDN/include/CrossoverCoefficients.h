//----------------------------------------------
//	Functiosn 
//----------------------------------------------

#ifndef BIQUAD_H
#define BIQUAD_H

#ifndef SAMPLE
#define SAMPLE float
#endif /* SAMPLE */

#ifndef pi
#define pi 3.141592653589793
#endif

#include <cmath>

struct FilterCoefficients;
void calcLowpass(FilterCoefficients* lo);
void calcHipass(FilterCoefficients* hi);

struct FilterCoefficients
{
	enum filtertype { hipass = 0, lowpass = 1 };

	FilterCoefficients(unsigned f_s, float f_c, int t_ype)
	{
		type = t_ype;
		fs = (float)f_s;
		fc = f_c;
		if (t_ype) { calcLowpass(this); }
		else { calcHipass(this); }
	}
	int type = 0;
	float b0 = 0.0, b1 = 0.0, b2 = 0.0, a0 = 0.0, a1 = 0.0, a2 = 0.0;
	float fs = 0.0, fc = 0.0;
};

void calcLowpass(FilterCoefficients* lo)
{
	float k = std::tan(pi * lo->fc / lo->fs);
	float k2 = k * k;
	float d = k2 + (2.0 * k) + 1.0;
	lo->b0 = k2 / (k2 + (2.0 * k) + 1.0);
	lo->b1 = 2.0 * lo->b0;
	lo->b2 = lo->b0;
	lo->a0 = 1.0;
	lo->a1 = 2.0 * (k2 - 1.0) / d;
	lo->a2 = (k2 - (2.0 * k) + 1.0) / d;
}

void calcHipass(FilterCoefficients* hi)
{
	float k = std::tan(pi * hi->fc / hi->fs);
	float k2 = k * k;
	float d = k2 + (2.0 * k) + 1.0;
	hi->b0 = 1.0 / (k2 + (2.0 * k) + 1.0);
	hi->b1 = -2.0 * hi->b0;
	hi->b2 = hi->b0;
	hi->a0 = 1.0;
	hi->a1 = 2.0 * (k2 - 1.0) / d;
	hi->a2 = (k2 - (2.0 * k) + 1.0) / d;
}

#endif