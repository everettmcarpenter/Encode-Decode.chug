#pragma once

// emc
inline void multiplyVectorByScalar( float* vector, const float scalar, const unsigned int size )
{
    for( int x = 0; x < size; x++ )
        vector[x] *= scalar;
}

// emc
// multiply respective components of v2 into v1
inline void multiplyVectorByVector( float* v1, const float* v2, const unsigned int size )
{
    for( int x = 0; x < size; x++ )
        v1[x] *= v2[x];
}

// emc
// copy a source vector into a destination vector ( awesome )
inline void copyVector( float* dest, const float* src, const unsigned int size )
{
    for( int x = 0; x < size; x++ )
        dest[x] = src[x];
}

// emc
// copy the channel of an interleaved buffer to an interleaved buffer of the same channel count and length (will modulo)
// destination.length must be = nframes and src.length = totalChannels * nframes
inline void copyChannelToVector( float* dest, const float* src, const unsigned int channel, const unsigned int totalChannels, const unsigned int nframes )
{
    for( int f = 0; f < nframes; f++ )
    {
        dest[f] = src[f * totalChannels + channel]; // copy a channel to all channels
    }
}

// emc
// multiply a src vector by a scalar and copy it to destination
inline void multiplyCopy( float* dest, const float* src, float scalar, const unsigned int size )
{
    for( int x = 0; x < size; x++ )
        dest[x] = src[x] * scalar;
}