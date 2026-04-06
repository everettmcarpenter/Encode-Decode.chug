#ifndef ORDERGAIN_H
#define ORDERGAIN_H

#include "chugin.h"

template <unsigned int order_>
class OrderGain
{
public:
	OrderGain()
	{
		weights = new float[channel_count];
		for(int i = 0; i < channel_count; i++) { weights[i] = 1.0; }
	}

	~OrderGain()
	{
		delete[] weights;
	}

	void tick(SAMPLE *in, SAMPLE *out, unsigned nframes)
	{
		memset(out, 0, sizeof(SAMPLE) * channel_count * nframes); // clear
		for (int f = 0; f < nframes; f++)
		{
			for (int i = 0; i < channel_count; i++)
			{
				out[f * channel_count + i] = gain * (in[f * channel_count + i] * weights[i]); // just add a gain factor to it
			}
		}
	}

	void setGain(float n_gain)
	{
		gain = n_gain;
	}

	void setWeights(Chuck_ArrayFloat* gains, CK_DL_API API)
	{
		int size = (API->object->array_float_size(gains));
		if (size >= channel_count)
		{
			for (int i = 0; i < size; i++)
			{
				weights[i] = (API->object->array_float_get_idx(gains, i));
			}
		}
	}

	float getGain() { return gain; }

	void getWeights(float* buffer) { for (int i = 0; i < channel_count; i++) { buffer[i] = weights[i]; } }

public:
	float gain = 1.0f;
	float* weights;
	const static unsigned order = order_;
	const static unsigned channel_count = (order_ + 1) * (order_ + 1);
};

class OrderGain1 : public OrderGain<1> // these simply just act as wrappers of OrderGain to chuck
{
public:
	OrderGain1(t_CKFLOAT fs) {};
};

class OrderGain2 : public OrderGain<2>
{
public:
	OrderGain2(t_CKFLOAT fs) {};
};

class OrderGain3 : public OrderGain<3>
{
public:
	OrderGain3(t_CKFLOAT fs) {};
};

class OrderGain4 : public OrderGain<4>
{
public:
	OrderGain4(t_CKFLOAT fs) {};
};

class OrderGain5 : public OrderGain<5>
{
public:
	OrderGain5(t_CKFLOAT fs) {};
};

#endif
