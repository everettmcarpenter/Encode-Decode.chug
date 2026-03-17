#ifndef MONO_DECODEN_H
#define MONO_DECODEN_H

#include "DecoderBase.h"

template <const unsigned order_>
class MonoDecode : public Decoder<order_> // seems redundant, but essentially takes all decoder commonalities, gives to this "Basic decoder" class with a sampling tick function
{
public:
	MonoDecode()
	{
		// we only need one vector or row of SH so let's get rid of the matrix
		for (int i = 0; i < this->n_channels; i++)
		{
			delete[] this->SpeakSH[i];
		}
		delete[] this->SpeakSH;
	}

	~MonoDecode() override
	{
		delete[] mySH;
		delete[] this->weights;
	}

	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes) 
	{
		memset(out, 0, sizeof(SAMPLE) * this->n_channels * nframes); // clear
		for (int f = 0; f < nframes; f++)							 // go through each frame
		{
			SAMPLE sumd = 0;
			for (int n = 0; n < this->n_channels; n++) // each channel of the incoming stream is a spherical harmonic
			{
				sumd += (in[f * this->n_channels + n] * this->mySH[n]); // vector mult of speaker SHs and input stream
			}
			out[f * this->n_channels] = sumd;
		}
		// calculate rms for this buffer frame
		rms = RMS(out, nframes);
	}

	void CKsetSpeakSH(Chuck_ArrayFloat* coord, CK_DL_API API) // using an array of spherical harmonics, set the SHs of the decoder
	{
		if (API->object->array_float_size(coord) >= this->n_channels)
		{
			for (t_CKINT i = 0; i < this->n_channels; i++)
			{
				this->mySH[i] = API->object->array_float_get_idx(coord, i);
			}
		}
	}

	void CKsetSpeakAngles(const t_CKFLOAT azimuth, const t_CKFLOAT elevation) // set the position via azimuth and elevation
	{
		lastAzimuth = azimuth;
		lastElevation = elevation;
		float* temp = new float[this->n_channels]; // temporary memory storage
		SH(temp, this->order, azimuth, elevation, 0); // calculate SH
		for (int i = 0; i < this->n_channels; i++)
		{
			// move over
			this->mySH[i] = temp[i];
		}
		delete[] temp;
		temp = nullptr;
	}

	float RMS(SAMPLE* out, unsigned nframes)
	{
		t_CKFLOAT sum = 0.0;
		for (t_CKUINT n = 0; n < nframes; n++)
		{
			sum = out[n] * out[n];
		}
		return sqrt(sum * (1.0 / nframes));
	}

public:
	float* mySH = new float[this->n_channels];
	t_CKFLOAT rms = 0.0;
	t_CKFLOAT lastAzimuth = 0.0;
	t_CKFLOAT lastElevation = 0.0;
};

// this is actually what gets called and used by the chugin
class MonoDecode1 : public MonoDecode<1>
{
public:
	MonoDecode1(t_CKFLOAT fs) : MonoDecode() {};
};

class MonoDecode2 : public MonoDecode<2>
{
public:
	MonoDecode2(t_CKFLOAT fs) : MonoDecode() {};
};

class MonoDecode3 : public MonoDecode<3>
{
public:
	MonoDecode3(t_CKFLOAT fs) : MonoDecode() {};
};

class MonoDecode4 : public MonoDecode<4>
{
public:
	MonoDecode4(t_CKFLOAT fs) : MonoDecode() {};
};

class MonoDecode5 : public MonoDecode<5>
{
public:
	MonoDecode5(t_CKFLOAT fs) : MonoDecode() {};
};

#endif