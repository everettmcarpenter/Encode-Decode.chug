@import "../classes/granulator"
@import "../classes/Transport"

2 => int ORDER; // ambisonic order
4 => int N; // how many grains per channel
Granulator grain("../audio/consolidated.wav")[(ORDER + 1) * (ORDER + 1)][N]; // 2nd order ambisonics, two grains for each channel
OrderGain2 encoder;
for(int i; i < grain.size(); i++)
{
    for(int j; j < grain[i].size(); j++)
    {
        // patch N granulators into each channel
        grain[i][j] => encoder.chan(i);
        grain[i][j].randomGrainSize(0.0);
        grain[i][j].randomPosition(0);
        grain[i][j].play();
    }
}

// record
fun void beginRecord(OrderGain2 sum, WvOut recorder[])
{
    for(int i; i < sum.channels(); i++)
    {
        recorder[i].wavFilename("../recordings/"+"graincode"+"-"+i+".wav");
        sum.chan(i) => recorder[i] => blackhole;
    }
}

// recorder
WvOut bformat[9];

// lets record it
spork ~ beginRecord(encoder, bformat);

encoder.gain(Math.sh(ORDER, 45.0, 0.0));

5::second => now;