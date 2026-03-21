#ifndef AMBICORDER_H
#define AMBICORDER_H

// stk includes
#include "WvOut.h"
#include "FileWvOut.h"
#include "FileWrite.h"
#include "Stk.h"
#include "chugin.h"

class AmbiCorder1 : public stk::FileWvOut
{
public:
	AmbiCorder1(t_CKFLOAT fs)
	{
	};
	void tick(SAMPLE* in, SAMPLE* out, unsigned nframes)
	{

	}

	stk:StkFrames* passAlong;
};

class AmbiCorder2 : public stk::FileWvOut
{
public:
	AmbiCorder2(t_CKFLOAT fs) {};
};

#endif