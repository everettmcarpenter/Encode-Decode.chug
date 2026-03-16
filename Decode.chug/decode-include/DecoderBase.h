// Decoder base class for inheritance 
// ==========================================================
// All decoders ever will be of some order N and have some number of channels which is directly related to the order N
// All decoders ever will store and reference a set of spherical harmonics attributed to each channel of the decoder
// All decoders ever will be able to retrieve 
// All decoders ever will store weights and apply them to their spherical harmonics when received 

#ifndef DECODE_BASE_H
#define DECODE_BASE_H

#include "chugin.h"
#include "chuckSH.h"
#include <array>

template<const unsigned order_>
class Decoder
{
public:
	Decoder()
	{
		SpeakSH = new float*[n_channels];
		for (int i = 0; i < n_channels; i++)
		{
			SpeakSH[i] = new float[n_channels];
		}
		weights = new float[n_channels];
	}

	virtual ~Decoder()
	{
		for (int i = 0; i < n_channels; i++)
		{
			delete[] SpeakSH[i];
		}
		delete[] SpeakSH;
		delete[] weights;
	}

	virtual void tick(SAMPLE* in, SAMPLE* out, unsigned nframes) = 0;

	void setSpeakerSH(float** n_SpeakSH) // set SH given all speaker SHs
	{
		for (int i = 0; i < n_channels; i++)
		{
			for (int j = 0; j < n_channels; j++)
			{
				SpeakSH[i][j] = n_SpeakSH[i][j];
			}
		}
	}

	void setSpeakerSH(float* n_SpeakSH, unsigned o) // set SH given a certain speaker
	{
		for (int i = 0; i < n_channels; i++)
		{
			SpeakSH[o][i] = n_SpeakSH[i];
		}
	}


	void CKsetSpeakAngles(Chuck_Object* coord, CK_DL_API API) // using a multi-dimensional chuck array of speaker angles, set the SHs of each speaker
	{
		Chuck_ArrayInt* column = (Chuck_ArrayInt*)coord;
		if (API->object->array_int_size(column) >= n_channels)
		{
			for (t_CKINT i = 0; i < n_channels; i++)
			{
				Chuck_ArrayFloat* row = (Chuck_ArrayFloat*)API->object->array_int_get_idx(column, i);
				t_CKUINT size = API->object->array_float_size(row);
				if (size == 2)
				{
					float* temp = new float[n_channels];
					SH(temp, order, API->object->array_float_get_idx(row, 0), API->object->array_float_get_idx(row, 1), 0);
					setSpeakerSH(temp, i);
					delete[] temp;
					temp = nullptr;
				}
			}
		}
	}

	void CKsetWeights(Chuck_ArrayFloat* m_weights, CK_DL_API API)
	{
		unsigned size = API->object->array_float_size(m_weights);
		for (int i = 0; i < size; i++)
		{
			if (i < n_channels)
			{
				weights[i] = API->object->array_float_get_idx(m_weights, i);
				for (int j = 0; j < n_channels; j++)
				{
					SpeakSH[j][i] = SpeakSH[j][i] * weights[i];
				}
			}
		}
	}

	float** getSpeakerSH() // retrieve all speaker SHs
	{
		return SpeakSH;
	}

	float* getSpeakerSH(unsigned o) // retrieve a speaker's SHs
	{	
		if(o < n_channels)	return SpeakSH[o];
	}

	float* getWeights()
	{
		return weights;
	}

	static const unsigned order = order_; // order
	static const unsigned n_channels = (order + 1) * (order + 1); // how many channels

public:
	float** SpeakSH; // spherical harmonics
	float* weights; // weights
	float channelBalance = (1.f / n_channels);
};

#endif /* DECODE_BASE_H */