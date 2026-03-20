#ifndef AMBICORDER_H
#define AMBICORDER_H

// stk includes
#include "WvOut.h"
#include "FileWvOut.h"
#include "FileWrite.h"
#include "chugin.h"

class AmbiCorder1 : public FileWvOut
{
	AmbiCorder1( t_CKFLOAT fs );
};

class AmbiCorder2 : public FileWvOut
{
	AmbiCorder2(t_CKFLOAT fs);
};

#endif