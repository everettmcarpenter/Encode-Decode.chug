#pragma once

// emc
void multiplyVectorByScalar( float* vector, float scalar, const unsigned int size )
{
    for( int x = 0; x < size; x++ )
        vector[x] = vector[x] * scalar;
}

// emc
// multiply respective components of v2 into v1
void multiplyVectorByVector( float* v1, const float* v2, const unsigned int size )
{
    for( int x = 0; x < size; x++ )
        v1[x] *= v2[x];
}

// emc
// copy a source vector into a destination vector ( awesome )
void copyVector( float* dest, const float* src, const unsigned int size )
{
    for( int x = 0; x < size; x++ )
        dest[x] = src[x];
}

// emc
// multiply a src vector by a scalar and copy it to destination
void multiplyCopy( float* dest, const float* src, float scalar, const unsigned int size )
{
    for( int x = 0; x < size; x++ )
        dest[x] = src[x] * scalar;
}