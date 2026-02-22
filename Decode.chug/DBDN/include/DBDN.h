#ifndef DBDN_H
#define DBDN_H

#include "DecoderBase.h"
#include "CrossoverCoefficients.h"

template <const unsigned order_>
class DBDN : public Decoder<order_>
{
public:
	DBDN(unsigned fs)
	{
		high = new FilterCoefficients(fs, 750.0, FilterCoefficients::hipass);
		low = new FilterCoefficients(fs, 750.0, FilterCoefficients::lowpass);
	}
	~DBDN()
	{
		delete high;
		delete low;
	}

	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * this->n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++)							 // go through each frame
		{
			for (int c = 0; c < this->n_channels; c++) // go through each channel
			{
				float n_lo = 0.0; // new input
				float n_hi = 0.0; // new output
				// lowpassed 
				n_lo = (low->b0 * in[f * this->n_channels + c]) + (low->b1 * lin[c][0]) + (low->b2 * lin[c][1]) + (-low->a1 * lout[c][0]) + (-low->a2 * lout[c][1]);
				// highpass
				n_hi = (high->b0 * in[f * this->n_channels + c]) + (high->b1 * hin[c][0]) + (high->b2 * hin[c][1]) + (-high->a1 * hout[c][0]) + (-high->a2 * hout[c][1]);

				// lowpass shift
				lout[c][1] = lout[c][0];
				lout[c][0] = n_lo;

				lin[c][1] = lin[c][0];
				lin[c][0] = in[f * this->n_channels + c];

				// highpass shift 
				hout[c][1] = hout[c][0];
				hout[c][0] = n_hi;

				hin[c][1] = hin[c][0];
				hin[c][0] = in[f * this->n_channels + c];
			}
			for (int c = 0; c < this->n_channels; c++)
			{
				for (int s = 0; s < this->n_channels; s++)
				{
					out[f * this->n_channels + c] = this->lout[s][0]; // add lowpassed s'th ACN
					out[f * this->n_channels + c] += this->hout[s][0]; // add highpassed s'th ACN 
					out[f * this->n_channels + c] *= this->SpeakSH[c][s]; // scale by speaker's s'th spherical harmonic
				}
			}
		}
	}
public:
	FilterCoefficients* high;
	FilterCoefficients* low;
	SAMPLE lin[(order_+1)*(order_+1)][2] = { 0.0 };
	SAMPLE lout[(order_+1)*(order_+1)][2] = { 0.0 };
	SAMPLE hin[(order_+1)*(order_+1)][2] = { 0.0 };
	SAMPLE hout[(order_+1)*(order_+1)][2] = { 0.0 };
};

class DBD1 : public DBDN<1> // wrapper for DBDN to chuck
{
public:
	DBD1(t_CKFLOAT fs) : DBDN<1>(static_cast<unsigned>(fs)) {};
};

class DBD2 : public DBDN<2>
{
public:
	DBD2(t_CKFLOAT fs) : DBDN<2>(static_cast<unsigned>(fs)) {};
};

class DBD3 : public DBDN<3>
{
public:
	DBD3(t_CKFLOAT fs) : DBDN<3>(static_cast<unsigned>(fs)) {};
};

class DBD4 : public DBDN<4>
{
public:
	DBD4(t_CKFLOAT fs) : DBDN<4>(static_cast<unsigned>(fs)) {};
};

class DBD5 : public DBDN<5> 
{
public:
	DBD5(t_CKFLOAT fs) : DBDN<5>(static_cast<unsigned>(fs)) {};
};

#endif