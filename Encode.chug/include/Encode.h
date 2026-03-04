/*----------------------------------------------------------------------------
  ChucK Strongly-timed Audio Programming Language
    Compiler and Virtual Machine

  Copyright (c) 2003 Ge Wang and Perry R. Cook. All rights reserved.
    http://chuck.stanford.edu/
    http://chuck.cs.princeton.edu/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  U.S.A.
-----------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
*
* Encode.chug header file
*
-----------------------------------------------------------------------------*/
#include "chugin.h"
#include <limits.h>
#include <array>
//-----------------------------------------------------------------------------
// class definition for internal chugin data
// (NOTE this isn't strictly necessary, but is one example of a recommended approach)
//-----------------------------------------------------------------------------
const t_CKFLOAT ZERO_THRESHOLD = 1e-3; // this is the threshold to swap coordinates, if the input sample is less than this, change coefficients
template <unsigned n_order>
class Encoder
{
public:
    Encoder()
    {
        channel_matrix.resize(channel_count);
        temp_matrix.resize(channel_count);
        weights.resize(channel_count);
        for (int i = 0; i < weights.size(); i++)
        {
            weights[i] = 1.0;
        }
    };
    // for chugins extending UGen
    void tick(SAMPLE *in, SAMPLE *out, int nframes)
    {
        for (int f = 0; f < nframes; f++)
        {
            zeroCrossing = abs(in[f]) < ZERO_THRESHOLD ? TRUE : FALSE; //  less that threshold? zeroCrossing TRUE else FALSE
        }

        if (zeroCrossing && channel_matrix != temp_matrix) // zero crossing and matrices aren't the same?
        {
            for (int i = 0; i < channel_count; i++)
            {
                channel_matrix[i] = temp_matrix[i]; // swap it out
            }
        }

        memset(out, 0, sizeof(SAMPLE) * channel_count * nframes); // clear

        for (int f = 0; f < nframes; f++)
        {
            for (int i = 0; i < channel_count; i++) // as of 28/10/2025 weights are removed from tick function (need to justify their use)
            {
                out[f * channel_count + i] = (in[f] * channel_matrix[i]); // in stream is mono so frame is channel 0
            }
        }
    }

    void set_coefficients(Chuck_ArrayFloat *coord, CK_DL_API API)
    {
        int size = (API->object->array_float_size(coord));
        if (size >= channel_count)
        {
            for (int i = 0; i < size; i++)
            {
                temp_matrix[i] = (API->object->array_float_get_idx(coord, i));
            }
        }
    }

    t_CKFLOAT get_i(t_CKUINT index)
    {
        if (index < channel_count)
        {
            return channel_matrix[index];
        }
        else
            return 0.0;
    }

    void set_i(t_CKFLOAT value, t_CKUINT index)
    {
        if (index < channel_count)
        {
            temp_matrix[index] = value;
        }
        else
            NULL;
    }

    void CKsetWeights(Chuck_ArrayFloat *m_weights, CK_DL_API API)
    {
        unsigned size = API->object->array_float_size(m_weights);
        for (int i = 0; i < size; i++)
        {
            if (i < channel_count)
            {
                weights[i] = API->object->array_float_get_idx(m_weights, i);
            }
        }
    }

    std::vector<float> getWeights()
    {
        std::vector<float> store;
        store.resize(channel_count);
        for (int i = 0; i < weights.size(); i++)
        {
            store[i] = weights[i];
        }
        return store;
    }

    void position(t_CKFLOAT azimuth_, t_CKFLOAT zenith_)
    {
        last_azimuth = azimuth_;
        last_zenith = zenith_;
        temp_matrix = SH(order, last_azimuth, last_zenith, 0); // simply just calls the spherical harmonic calculator
    }

    std::vector<float> getSH()
    {
        std::vector<float> store;
        store.resize(channel_count);
        for (int i = 0; i < temp_matrix.size(); i++)
        {
            store[i] = temp_matrix[i];
        }
        return store;
    }

public:
    // instance data
    constexpr static unsigned order = n_order;
    constexpr static unsigned channel_count = (n_order + 1) * (n_order + 1);
    std::vector<float> channel_matrix; // current gain coeffs
    std::vector<float> temp_matrix;    // temp coeffs to be shifted to current
    std::vector<float> weights = { 1.0 };
    float last_azimuth = 0.f;
    float last_zenith = 0.f;
    bool zeroCrossing = FALSE; // is there a zero crossing?
};

class Encode1 : public Encoder<1> // these simply just act as wrappers of Encoder to chuck
{
public:
    Encode1(t_CKFLOAT fs) {};
};

class Encode2 : public Encoder<2>
{
public:
    Encode2(t_CKFLOAT fs) {};
};

class Encode3 : public Encoder<3>
{
public:
    Encode3(t_CKFLOAT fs) {};
};

class Encode4 : public Encoder<4>
{
public:
    Encode4(t_CKFLOAT fs) {};
};

class Encode5 : public Encoder<5>
{
public:
    Encode5(t_CKFLOAT fs) {};
};
