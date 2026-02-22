#include "DecoderBase.h"
#include "CrossoverCoefficients.h"

template <unsigned order_>
class DBDN : public Decoder<order_>
{
public:
	DBDN(float fs)
	{
		high = new FilterCoefficients((unsigned)fs, 750.0, FilterCoefficients::hipass);
		low = new FilterCoefficients((unsigned)fs, 750.0, FilterCoefficients::lowpass);
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
					out[f * this->n_channels + c] = lout[s][0]; // add lowpassed s'th ACN
					out[f * this->n_channels + c] += hout[s][0]; // add highpassed s'th ACN 
					out[f * this->n_channels + c] *= SpeakSH[c][s]; // scale by speaker's s'th spherical harmonic
				}
			}
		}
	}
private:
	FilterCoefficients* high;
	FilterCoefficients* low;
	SAMPLE lin[n_channels][2] = { 0.0 };
	SAMPLE lout[n_channels][2] = { 0.0 };
	SAMPLE hin[n_channels][2] = { 0.0 };
	SAMPLE hout[n_channels][2] = { 0.0 };
};
