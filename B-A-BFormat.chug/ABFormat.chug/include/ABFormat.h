#include "chugin.h"

class ABFormat
{
public:
	void virtual tick() {};

protected:
	unsigned channel_count = 4;
	unsigned order = 0;
};

class ABFormat1 : public ABFormat
{
public:

	ABFormat1(t_CKFLOAT fs) {};

	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * channel_count * nframes); // clear
		for (int f = 0; f < nframes; f++) // assume input is Lf Lb Rf Rb
		{
			out[f * channel_count + 0] = 0.25 * (in[f * this->channel_count + 0] + in[f * this->channel_count + 3] + in[f * this->channel_count + 2] + in[f * this->channel_count + 1]); // W
			out[f * channel_count + 1] = 0.25 * (in[f * this->channel_count + 0] - in[f * this->channel_count + 3] - in[f * this->channel_count + 2] + in[f * this->channel_count + 1]); // Y
			out[f * channel_count + 2] = 0.25 * (in[f * this->channel_count + 0] + in[f * this->channel_count + 3] - in[f * this->channel_count + 2] - in[f * this->channel_count + 1]); // Z
			out[f * channel_count + 3] = 0.25 * (in[f * this->channel_count + 0] - in[f * this->channel_count + 3] + in[f * this->channel_count + 2] - in[f * this->channel_count + 1]); // X
		}
	}
};