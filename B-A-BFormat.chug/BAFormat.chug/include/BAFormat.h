#ifndef BAFORMAT_H
#define BAFORMAT_H

#include "chugin.h"

class BAFormat
{
public:
	BAFormat(t_CKFLOAT fs) {};
	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes) // assume input is ACN... WYZX, output is Lf Lb Rf Rb
	{	// this algorithm is created from mathematical derivations in https://www.cieri.net/Area%20protetta/Wireless%20World/Soundfield%20microphone.pdf
		// these are supported by the definition of the Hadamard matrix https://en.wikipedia.org/wiki/Hadamard_matrix
		memset(out, 0, sizeof(SAMPLE) * channel_count * nframes); // clear
		for (int f = 0; f < nframes; f++) // assume input is Lf Lb Rf Rb
		{
			out[f * channel_count + 0] = 0.25 * (in[f * this->channel_count + 0] + in[f * this->channel_count + 3] + in[f * this->channel_count + 2] + in[f * this->channel_count + 1]); // Lf
			out[f * channel_count + 1] = 0.25 * (in[f * this->channel_count + 0] - in[f * this->channel_count + 3] - in[f * this->channel_count + 2] + in[f * this->channel_count + 1]); // Lb
			out[f * channel_count + 2] = 0.25 * (in[f * this->channel_count + 0] + in[f * this->channel_count + 3] - in[f * this->channel_count + 2] - in[f * this->channel_count + 1]); // Rf
			out[f * channel_count + 3] = 0.25 * (in[f * this->channel_count + 0] - in[f * this->channel_count + 3] + in[f * this->channel_count + 2] - in[f * this->channel_count + 1]); // Rb
		}
	}

	unsigned channel_count = 4;
};

#endif