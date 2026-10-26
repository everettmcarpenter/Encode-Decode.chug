/*
 ==============================================================================
 This file is part of the IEM plug-in suite. ( HACKED BY EMC )
 Author: Daniel Rudrich
 Copyright (c) 2017 - Institute of Electronic Music and Acoustics (IEM)
 https://iem.at

 The IEM plug-in suite is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 The IEM plug-in suite is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this software.  If not, see <https://www.gnu.org/licenses/>.
 ==============================================================================
 */

#include "emc-vectorSupplement.h"

void SHEval0 (const float fX, const float fY, const float fZ, float* SHcoeffs);
void SHEval1 (const float fX, const float fY, const float fZ, float* SHcoeffs);
void SHEval2 (const float fX, const float fY, const float fZ, float* SHcoeffs);
void SHEval3 (const float fX, const float fY, const float fZ, float* SHcoeffs);
void SHEval4 (const float fX, const float fY, const float fZ, float* SHcoeffs);
void SHEval5 (const float fX, const float fY, const float fZ, float* SHcoeffs);
void SHEval6 (const float fX, const float fY, const float fZ, float* SHcoeffs);
void SHEval7 (const float fX, const float fY, const float fZ, float* SHcoeffs);

#ifndef M_2_SQRTPI
    #define M_2_SQRTPI 1.12837916709551257389615890312154517
#endif

#ifndef sqrt4PI
    #define sqrt4PI 3.544907701811032
#endif

// encoding and decoding with same direction and order yields the same encoded signal
// normalization is done at the decoding stage
constexpr float decodeCorrection (const int N)
{
    return sqrt4PI / (N + 1) / (N + 1);
}

inline void SHEval (const int N,
                    const float fX,
                    const float fY,
                    const float fZ,
                    float* SHcoeffs,
                    const bool doEncode = true)
{
    unsigned int nChan = ( N + 1 ) * ( N + 1 ); // emc
    switch ( N )
    {
        case 0:
            SHEval0 (fX, fY, fZ, SHcoeffs); // calc sh
            multiplyVectorByScalar( SHcoeffs, doEncode ? sqrt4PI : decodeCorrection( N ), nChan ); // emc ( normalize )
            break;
        case 1:
            SHEval1 (fX, fY, fZ, SHcoeffs);
            multiplyVectorByScalar( SHcoeffs, doEncode ? sqrt4PI : decodeCorrection( N ), nChan ); // emc ( normalize )
            break;
        case 2:
            SHEval2 (fX, fY, fZ, SHcoeffs);
            multiplyVectorByScalar( SHcoeffs, doEncode ? sqrt4PI : decodeCorrection( N ), nChan ); // emc ( normalize )
            break;
        case 3:
            SHEval3 (fX, fY, fZ, SHcoeffs);
            multiplyVectorByScalar( SHcoeffs, doEncode ? sqrt4PI : decodeCorrection( N ), nChan ); // emc ( normalize )
            break;
        case 4:
            SHEval4 (fX, fY, fZ, SHcoeffs);
            multiplyVectorByScalar( SHcoeffs, doEncode ? sqrt4PI : decodeCorrection( N ), nChan ); // emc ( normalize )
            break;
        case 5:
            SHEval5 (fX, fY, fZ, SHcoeffs);
            multiplyVectorByScalar( SHcoeffs, doEncode ? sqrt4PI : decodeCorrection( N ), nChan ); // emc ( normalize )
            break;
        case 6:
            SHEval6 (fX, fY, fZ, SHcoeffs);
            multiplyVectorByScalar( SHcoeffs, doEncode ? sqrt4PI : decodeCorrection( N ), nChan ); // emc ( normalize )
            break;
        case 7:
            SHEval7 (fX, fY, fZ, SHcoeffs);
            multiplyVectorByScalar( SHcoeffs, doEncode ? sqrt4PI : decodeCorrection( N ), nChan ); // emc ( normalize )
            break;
    }
}

/* // removed by emc
inline void SHEval (const int N,
                    const juce::Vector3D<float> position,
                    float* pSH,
                    const bool doEncode = true)
{
    SHEval (N, position.x, position.y, position.z, pSH, doEncode);
}
*/

// -----------------------------------------------
//      Stole this from ambisonicTools.h
// -----------------------------------------------

const float sn3d2n3d[64] = {
    1.0000000000000000e+00f, 1.7320508075688772e+00f, 1.7320508075688772e+00f,
    1.7320508075688772e+00f, 2.2360679774997898e+00f, 2.2360679774997898e+00f,
    2.2360679774997898e+00f, 2.2360679774997898e+00f, 2.2360679774997898e+00f,
    2.6457513110645907e+00f, 2.6457513110645907e+00f, 2.6457513110645907e+00f,
    2.6457513110645907e+00f, 2.6457513110645907e+00f, 2.6457513110645907e+00f,
    2.6457513110645907e+00f, 3.0000000000000000e+00f, 3.0000000000000000e+00f,
    3.0000000000000000e+00f, 3.0000000000000000e+00f, 3.0000000000000000e+00f,
    3.0000000000000000e+00f, 3.0000000000000000e+00f, 3.0000000000000000e+00f,
    3.0000000000000000e+00f, 3.3166247903553998e+00f, 3.3166247903553998e+00f,
    3.3166247903553998e+00f, 3.3166247903553998e+00f, 3.3166247903553998e+00f,
    3.3166247903553998e+00f, 3.3166247903553998e+00f, 3.3166247903553998e+00f,
    3.3166247903553998e+00f, 3.3166247903553998e+00f, 3.3166247903553998e+00f,
    3.6055512754639891e+00f, 3.6055512754639891e+00f, 3.6055512754639891e+00f,
    3.6055512754639891e+00f, 3.6055512754639891e+00f, 3.6055512754639891e+00f,
    3.6055512754639891e+00f, 3.6055512754639891e+00f, 3.6055512754639891e+00f,
    3.6055512754639891e+00f, 3.6055512754639891e+00f, 3.6055512754639891e+00f,
    3.6055512754639891e+00f, 3.8729833462074170e+00f, 3.8729833462074170e+00f,
    3.8729833462074170e+00f, 3.8729833462074170e+00f, 3.8729833462074170e+00f,
    3.8729833462074170e+00f, 3.8729833462074170e+00f, 3.8729833462074170e+00f,
    3.8729833462074170e+00f, 3.8729833462074170e+00f, 3.8729833462074170e+00f,
    3.8729833462074170e+00f, 3.8729833462074170e+00f, 3.8729833462074170e+00f,
    3.8729833462074170e+00f
};

const float n3d2sn3d[64] = {
    1.0000000000000000e+00f, 5.7735026918962584e-01f, 5.7735026918962584e-01f,
    5.7735026918962584e-01f, 4.4721359549995793e-01f, 4.4721359549995793e-01f,
    4.4721359549995793e-01f, 4.4721359549995793e-01f, 4.4721359549995793e-01f,
    3.7796447300922720e-01f, 3.7796447300922720e-01f, 3.7796447300922720e-01f,
    3.7796447300922720e-01f, 3.7796447300922720e-01f, 3.7796447300922720e-01f,
    3.7796447300922720e-01f, 3.3333333333333331e-01f, 3.3333333333333331e-01f,
    3.3333333333333331e-01f, 3.3333333333333331e-01f, 3.3333333333333331e-01f,
    3.3333333333333331e-01f, 3.3333333333333331e-01f, 3.3333333333333331e-01f,
    3.3333333333333331e-01f, 3.0151134457776363e-01f, 3.0151134457776363e-01f,
    3.0151134457776363e-01f, 3.0151134457776363e-01f, 3.0151134457776363e-01f,
    3.0151134457776363e-01f, 3.0151134457776363e-01f, 3.0151134457776363e-01f,
    3.0151134457776363e-01f, 3.0151134457776363e-01f, 3.0151134457776363e-01f,
    2.7735009811261457e-01f, 2.7735009811261457e-01f, 2.7735009811261457e-01f,
    2.7735009811261457e-01f, 2.7735009811261457e-01f, 2.7735009811261457e-01f,
    2.7735009811261457e-01f, 2.7735009811261457e-01f, 2.7735009811261457e-01f,
    2.7735009811261457e-01f, 2.7735009811261457e-01f, 2.7735009811261457e-01f,
    2.7735009811261457e-01f, 2.5819888974716110e-01f, 2.5819888974716110e-01f,
    2.5819888974716110e-01f, 2.5819888974716110e-01f, 2.5819888974716110e-01f,
    2.5819888974716110e-01f, 2.5819888974716110e-01f, 2.5819888974716110e-01f,
    2.5819888974716110e-01f, 2.5819888974716110e-01f, 2.5819888974716110e-01f,
    2.5819888974716110e-01f, 2.5819888974716110e-01f, 2.5819888974716110e-01f,
    2.5819888974716110e-01f,
};

const float sn3d2n3d_short[8] = { 1.0000000000000000e+00f, 1.7320508075688772e+00f,
                                  2.2360679774997898e+00f, 2.6457513110645907e+00f,
                                  3.0000000000000000e+00f, 3.3166247903553998e+00f,
                                  3.6055512754639891e+00f, 3.8729833462074170e+00f };

const float n3d2sn3d_short[8] = { 1.0000000000000000e+00f, 5.7735026918962584e-01f,
                                  4.4721359549995793e-01f, 3.7796447300922720e-01f,
                                  3.3333333333333331e-01f, 3.0151134457776363e-01f,
                                  2.7735009811261457e-01f, 2.5819888974716110e-01f };

