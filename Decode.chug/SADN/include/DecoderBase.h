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
		weights.fill(1.0f);
	}

	virtual void tick(SAMPLE* in, SAMPLE* out, unsigned nframes) = 0;

	void setSpeakerSH(std::vector<std::vector<float>> n_SpeakSH) // set SH given all speaker SHs
	{
		for (int i = 0; i < n_channels; i++)
		{
			for (int j = 0; j < n_channels; j++)
			{
				SpeakSH[i][j] = n_SpeakSH[i][j];
			}
		}
	}

	void setSpeakerSH(std::vector<float> n_SpeakSH, unsigned o) // set SH given a certain speaker
	{
		for (int i = 0; i < n_SpeakSH.size(); i++)
		{
			SpeakSH[o][i] = n_SpeakSH[i];
		}
	}

	std::vector<std::vector<float>> getSpeakerSH() // retrieve all speaker SHs
	{
		std::vector<std::vector<float>> store;
		store.resize(n_channels);
		for (int i = 0; i < SpeakSH.size(); i++)
		{
			store[i].resize(n_channels);
			for (int j = 0; j < SpeakSH[i].size(); j++)
			{
				store[i][j] = SpeakSH[i][j];
			}
		}
		return store;
	}

	std::vector<float> getSpeakerSH(unsigned o) // retrieve a speaker's SHs
	{
		std::vector<float> store;
		store.resize(n_channels);
		if (o < (n_channels - 1))
		{
			for (int i = 0; i < SpeakSH[o].size(); i++)
			{
				store[i] = SpeakSH[o][i];
			}
			return store;
		}
		else return store;
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
					std::vector<float> temp = SH(order, API->object->array_float_get_idx(row, 0), API->object->array_float_get_idx(row, 1), 0);
					setSpeakerSH(temp, i);
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

protected:
	static constexpr unsigned order = order_; // order
	static constexpr unsigned n_channels = (order + 1) * (order + 1); // how many channels
	std::array<std::array<float, n_channels>, n_channels> SpeakSH{}; // spherical harmonics
	std::array<float, n_channels> weights{ 1.f }; // weights
	static constexpr float channelBalance = (1.f / n_channels);
};

#endif /* DECODE_BASE_H */