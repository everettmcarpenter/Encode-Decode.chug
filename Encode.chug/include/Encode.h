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
        channel_matrix = new float[channel_count];
        temp_matrix = new float[channel_count];
        weights = new float[channel_count];

        for (int i = 0; i < channel_count; i++)
        {
            channel_matrix[i] = 0.0;
            temp_matrix[i] = 0.0;
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

        if (zeroCrossing) // zero crossing and matrices aren't the same?
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

    void position(t_CKFLOAT azimuth_, t_CKFLOAT zenith_)
    {
        lastAzimuth = azimuth_;
        lastElevation = zenith_;
        float* temp = new float[channel_count];
        SH(temp, order, lastAzimuth, lastElevation, 0); // simply just calls the spherical harmonic calculator
        for (int i = 0; i < channel_count; i++)
        {
            temp_matrix[i] = temp[i];
        }
        delete[] temp;
        temp = nullptr;
    }

public:
    // instance data
    const static t_CKUINT order = n_order;
    const static t_CKUINT channel_count = (n_order + 1) * (n_order + 1);
    float* channel_matrix; // current gain coeffs
    float* temp_matrix;    // temp coeffs to be shifted to current
    float* weights;
    t_CKFLOAT lastAzimuth = 0.f;
    t_CKFLOAT lastElevation = 0.f;
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
