4 => int ORDER;
(ORDER+1)*(ORDER+1) => int N_CHANNELS;
64 => int FRAME_SIZE;

// 64 sample frame of a source
float frameOne[FRAME_SIZE][N_CHANNELS];

// 64 sample frame of another source
float frameTwo[FRAME_SIZE][N_CHANNELS];

fun float[] mean(float frame[][])
{
	float means[frame[0].size()];
	for(int f; f < frame.size(); f++)
	{
		for(int s; s < frame[f].size(); s++)
		{
			frame[f][s] +=> means[s];
		}
	}

	for(int f; f < frame[0].size(); f++)
	{
		frame.size() /=> means[f];
	}
	return means;
}

// source steadily rotating around the circle
for(int r; r < FRAME_SIZE; r++)
{
	Math.sh(ORDER, r * (360.0/FRAME_SIZE), 0.0) @=> frameOne[r];
}

// calculate means
mean(frameOne) @=> float frameMean[];

cherr <= "Mean of each dimension: ";
for(int i; i < frameMean.size(); i++)
{
	cherr <= frameMean[i] <= IO.nl();
}
