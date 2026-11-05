#ifndef ENERGYCALC_H
#define ENERGYCALC_H

#include "chugin.h"
#include <iostream>
#include <cmath>
#include "efficientSHvanilla.h"
#include "emc-vectorSupplement.h" // this is included with the above file but for the sake of clarity i am including it here
#include "hammerAitovSample.h"
#include "MaxRE.h"

#define maxOrder 7
#define maxInputChannels ( maxOrder + 1 ) * ( maxOrder + 1 )

class EnergyCalculator
{
public:
    // create all the data
    EnergyCalculator( unsigned int sampleRate, unsigned int bufsize )
    {
        // set
        fs = sampleRate;
        bs = bufsize;
        
        // columns
        decoderMatrix = new float*[nSamplePoints];
        
        // rows
        for( unsigned int i = 0; i < nSamplePoints; i++ )
            decoderMatrix[i] = new float[maxInputChannels];
        
        // rms
        rms = new float[nSamplePoints];
        // fill with zeros ( i know there's a loop just above that does this, we're in the constructor )
        for( unsigned int i = 0; i < nSamplePoints; i++ )
            rms[i] = 0.0f;
        
        // this is somewhat of a temp variable where we will perform some math to derive the information we need
        sampledSignal = new float[bs];

        // weights
        weights = new float[maxInputChannels];
        
        // time constant
        this->setTimeConstant( 500.0, bs, maxInputChannels );

        // calc
        for( unsigned int p = 0; p < nSamplePoints; p++ ) // columns decoderMatrix[c][?]
        {
            // evaluate harmonics
            SHEval( maxOrder, // i think our overload is coming from how we rewrote this function
                    hammerAitovSampleX[p],
                    hammerAitovSampleY[p],
                    hammerAitovSampleZ[p],
                    decoderMatrix[p],
                    false );
            // convert to n3d
            multiplyVectorByVector( decoderMatrix[p], sn3d2n3d, maxInputChannels );
            // undo correction
            for( unsigned int r = 0; r < maxInputChannels; r++ )
            {
                // undo seventh order correction
                decoderMatrix[p][r] *= ( 1.0 / decodeCorrection( 7 ) );
            }
        }
    };

    // delete all the data
    ~EnergyCalculator()
    {
        // backwards, rows first
        for( unsigned int i = 0; i < nSamplePoints; i++ )
            CK_SAFE_DELETE_ARRAY( decoderMatrix[i] );
        // columns next
        CK_SAFE_DELETE_ARRAY( decoderMatrix );
        // delete sampledSignal
        CK_SAFE_DELETE_ARRAY( sampledSignal );
        // rms
        CK_SAFE_DELETE_ARRAY( rms );
        // weights
        CK_SAFE_DELETE_ARRAY( weights );
    };

    // in - a b-format stream of incomingOrder
    // out - a vector of length nSamplePoints
    // incomingOrder - the order at which the input stream is operating
    // nframes - the number of frames that incoming buffer holds
    void tick( float* in, unsigned int nframes )
    {
        // for ambiguity, we'll let the caller specify the incoming order
        unsigned int inChannels = ( myOrder + 1 ) * ( myOrder + 1 );
        
        // it is important to note we are creating a buffer of nframes * maxSH length but will only use nframes * inChannels
        // we need this
        float oneMinusTC = 1.0f - timeConstant;

        // time to increase our computation time
        // it is important to know that point i is whatever hammerAitovSampleN[i] is
        for( int point = 0; point < nSamplePoints; point++ )
        {
            // cycle through frames
            for( unsigned int f = 0; f < nframes; f++ )
            {
                // copy the 0th channel for this frame, and decode & weight it
                sampledSignal[f] = in[f * maxInputChannels + 0] * weights[0] * decoderMatrix[point][0];
                // cycle only through the channels we're using ( we get 64, but might only be using 16 or 9, etc )
                for( unsigned int c = 1; c < inChannels; c++ ) // c++!
                {
                    // decode !
                    sampledSignal[f] += in[f * maxInputChannels + c] * weights[c] * decoderMatrix[point][c];
                }
            }

            // calculate rms of the point
            float summation = 0.f;
            for( unsigned int r = 0; r < nframes; r++ )
            {
                const float sample = sampledSignal[r];
                summation += sample * sample; // squared sum
            }

            // time averaged rms
            rms[point] = timeConstant * rms[point] + oneMinusTC * std::sqrt( summation / nframes );
        }
    }

    // set time constant
    void setTimeConstant( float RMStimeConstant, unsigned int bufferSize, unsigned int inChannels )
    {
        // calc
        timeConstant = std::exp( -1.0 / ( fs * ( RMStimeConstant / 1000.0 ) / ( bufferSize  * inChannels ) ) );
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
        {
        	return;
        }
        else // if we're good
        {
            location[0] = hammerAitovSampleX[point];
            location[1] = hammerAitovSampleY[point];
            location[2] = hammerAitovSampleZ[point];
        }
    }

    // get individual coordinates of a point seems even safer than passing a buffer
    float getPointX( unsigned int point )
    {
        if( point >= nSamplePoints )
        {
            return 0.f;
        }
        else // if we're good
        {
            return hammerAitovSampleX[point];
        }
    }

    float getPointY( unsigned int point )
    {
        if( point >= nSamplePoints )
        {
            return 0.f;
        }
        else // if we're good
        {
            return hammerAitovSampleY[point];
        }
    }

    float getPointZ( unsigned int point )
    {
        if( point >= nSamplePoints )
        {
        	return 0.f;
        }
        else // if we're good
        {
            return hammerAitovSampleZ[point];
        }
    }

    void setOrder( unsigned int ord )
    {
        if( ord >= 0 && ord <= maxOrder )
            myOrder = ord;
        else
            myOrder = 7;

        // retrieve our weights ( weights is of length maxInputChannels but we will ignore entries which are > incoming order's SH count
        copyMaxRE( myOrder, weights );
        // multiply the maxRE and decode corrections
        multiplyVectorByScalar( weights, maxRECorrection[myOrder] * decodeCorrection( myOrder ), ( myOrder + 1 ) * ( myOrder + 1 ) );
        
        if( sn3d ) // use sn3d
            multiplyVectorByVector( weights, n3d2sn3d, ( myOrder + 1 ) * ( myOrder + 1 ) );
    }

    unsigned int getOrder() 
    { return myOrder; }

    // get rms
    // rmsBuffer - should be of size nSamplePoints
    void getRMS( float* rmsBuffer )
    {
    	copyVector( rmsBuffer, rms, nSamplePoints );
    }

    float getRMSAtPoint( unsigned int point )
    {
        if ( point >= nSamplePoints )
        {
            return 0.f;
        }
        else // if we're good
        {
            return rms[point];
        }
    }

private:
    float** decoderMatrix = nullptr;
    float* rms = nullptr;
    float* weights = nullptr;
    float* sampledSignal = nullptr;
    float timeConstant = 1.0f;
    unsigned int fs = 0;
    unsigned int bs = 0;
    unsigned int myOrder = 7;
    bool sn3d = true; // if we wanna use sn3d
};

#endif /* ENERGYCALC_H */
