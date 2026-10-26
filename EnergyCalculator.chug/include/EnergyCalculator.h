#ifndef ENERGYCALC_H
#define ENERGYCALC_H

#include "chugin.h"
#include "efficientSHvanilla.h"
#include "emc-vectorSupplement.h" // this is included with the above file but for the sake of clarity i am including it here
#include "hammerAitovSample.h"
#include "MaxRE.h"

#define nSamplePoints 426
#define maxOrder 7
#define maximumSH ( maxOrder + 1 ) * ( maxOrder + 1 )

class EnergyCalculator
{
public:
    // create all the data
    EnergyCalculator( unsigned int sampleRate, unsigned int nframes )
    {
        // set
        fs = sampleRate;
        bs = nframes;
        // columns
        decoderMatrix = new float*[nSamplePoints];
        // rows
        for( int i = 0; i < nSamplePoints; i++ )
            decoderMatrix[i] = new float[maximumSH];
        // rms
        rms = new float[nSamplePoints];
        // fill with zeros ( i know there's a loop just above that does this, we're in the constructor )
        for( int i = 0; i < nSamplePoints; i++ )
            rms[i] = 0.0f;
        // weights
        weights = new float[maximumSH];
        
        // calc
        for( int c = 0; c < nSamplePoints; c++ ) // columns decoderMatrix[c][?]
        {
            // evaluate harmonics
            SHEval( maxOrder, hammerAitovSampleX[c], hammerAitovSampleY[c], hammerAitovSampleZ[c], decoderMatrix[c] );
            // undo correction
            for( int r = 0; r < maximumSH; r++ )
            {
                // undo seventh order correction
                decoderMatrix[c][r] = decoderMatrix[c][r] * ( 1.0 / decodeCorrection( 7 ) );
                // conver to n3d
                multiplyVectorByVector( decoderMatrix[c], sn3d2n3d, 64 );
            }
        }
    };

    // delete all the data
    ~EnergyCalculator()
    {
        // backwards, rows first
        for( int i = 0; i < nSamplePoints; i++ )
            CK_SAFE_DELETE_ARRAY( decoderMatrix[i] );
        // columns next
        CK_SAFE_DELETE_ARRAY( decoderMatrix );
        // rms
        CK_SAFE_DELETE_ARRAY( rms );
        // weights
        CK_SAFE_DELETE_ARRAY( weights );
    };

    // in - a b-format stream of incomingOrder
    // out - a vector of length nSamplePoints
    // incomingOrder - the order at which the input stream is operating
    // nframes - the number of frames that incoming buffer holds
    void tick( float* in, float* out, unsigned int incomingOrder, unsigned int nframes )
    {
        // for ambiguity, we'll let the caller specify the incoming order
        unsigned int inChannels = ( incomingOrder + 1 ) * ( incomingOrder + 1 ); 
        
        // take a guess
        unsigned int bufferLength = nframes * inChannels;
        
        // this is somewhat of a temp variable where we will perform some math to derive the information we need
        float* sampledSignal = new float[bufferLength];

        // retrieve our weights ( weights is of length maximumSH but we will ignore entries which are > incoming order's SH count
        copyMaxRE( incomingOrder, weights );

        // multiply the maxRE and decode corrections
        multiplyVectorByScalar( weights, maxRECorrection[incomingOrder] * decodeCorrection( incomingOrder ), maximumSH );

        // we need this
        float oneMinusTC = 1.0f - timeConstant;

        // time to increase our computation time
        // it is important to know that point 0 is whatever hammerAitovSampleN[i] is
        for( int point = 0; point < nSamplePoints; point++ )
        {
            // copy entire signal
            copyVector( sampledSignal, in, bufferLength );
            // cycle through frames
            for( int f = 0; f < nframes; f++ )
            {
                // cycle through channels
                for( int c = 0; c < inChannels; c++ )
                {
                    // decode !
                    sampledSignal[f * inChannels + c] = in[f * inChannels + c] * weights[c] * decoderMatrix[point][c];
                }
            }

            // calculate rms of the point
            float summation = 0.f;
            for( int r = 0; r < nframes * inChannels; r++ )
            {
                float sample = sampledSignal[r];
                summation += sample * sample; // squared sum
            }

            // time averaged rms
            rms[point] = timeConstant * rms[point] + oneMinusTC * std::sqrt( summation / bufferLength );
        }
    }

    // set time constant
    void setTimeConstant( float RMStimeConstant, unsigned int nframes, unsigned int inChannels )
    {
        // calc
        timeConstant = std::exp( -1.0 / ( fs * ( RMStimeConstant / 1000.0 ) / nframes * inChannels ) );
    }

    // get num points
    unsigned int pointCount()
    { return nSamplePoints; }

    // get operating order
    unsigned int order()
    { return maxOrder; }

    // get point
    // this seems safer than passing a two dimensional array and trusting the caller
    // the buffer passed should be of size 3 (cartesian coordinates)
    void getPoint( float* location, unsigned int point )
    {
        if( point >= nSamplePoints )
            return;
        else // if we're good
        {
            location[0] = hammerAitovSampleX[point];
            location[1] = hammerAitovSampleY[point];
            location[2] = hammerAitovSampleZ[point];
        }
    }

private:
    float** decoderMatrix = nullptr;
    float* rms = nullptr;
    float* weights = nullptr;
    float timeConstant = 0.0f;
    unsigned int fs = 0;
    unsigned int bs = 0;
};

#endif /* ENERGYCALC_H */
