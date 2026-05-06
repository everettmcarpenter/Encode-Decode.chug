#ifndef AMBICORDER_H
#define AMBICORDER_H

#include "chugin.h"
#include <sndfile.h>

template <const unsigned n_order>
class AmbiCorder
{
public:
	AmbiCorder( t_CKFLOAT fs )
	{
	};

	void tick( SAMPLE* in, SAMPLE* out, unsigned nframes )
	{

	}

	int openFile( const char* path )
	{
		// attempt to read 
		myFile = sf_open( path, // where
						  SFM_WRITE, // only write
						  myFileInformation ); // tell me what it is
		// if we failed
		if( !myFileInformation ) { wipeInternalFile(); // play it safe
								   return 1; }
		// otherwise . . . 
		else if ( myFile && myFileInformation ) { return 0; }
	}

	void wipeInternalFile() { delete myFile; // delete
							  delete myFileInformation;
							  myFile = nullptr; // cleanup
							  myFileInformation = nullptr; }

	int samplerate() { if( myFileInformation ) return myFileInformation->samplerate;
					   else return 0; }

	int channels() { if( myFileInformation ) return myFileInformation->channels;
					 else return 0;}


	// my order
	unsigned order = n_order;
	// how many channels I need
	unsigned nchannels = (order + 1) * (order + 1);
	// pointer to my eventual file
	FILE* myFile;
	// pointer to my struct describing the file above
	SF_INFO* myFileInformation;
};

#endif