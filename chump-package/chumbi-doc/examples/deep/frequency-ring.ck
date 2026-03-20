//-----------------------------------------------------------
// name: frequency-ring.ck
// author: everett m. carpenter
// desc: takes a mono input source and spreads it's spectrum
//       into a horizontal ring in ambisonics. be sure to 
//       use FrequencyRing.out as your output stream, since
//       multichannel chugraphs are not yet supported. if you
//       overload the constructor, you can set the number of 
//       frequency bands to be spatialized.
//-----------------------------------------------------------

public class FrequencyRing extends Chugraph
{
    // ambi encode
    Encode2 @ enc[];
    // sum
    OrderGain2 out;
    // freq split
    ResonZ @ split[];
    // number of bands
    4 => int numBands;

    fun void FrequencyRing()
    {
        // allocate filters and encoders
        new ResonZ[numBands] @=> split;
        new Encode2[numBands] @=> enc;
        out.gain(1.0/numBands); // volume control
        // patchbay & config
        for(int i; i < numBands; i++)
        {
            // set freq and Q
            split[i].set((14000.0/numBands) * (i+1.0), 24.0);
            // set position
            enc[i].pos((360.0/numBands) * (i), 0.0);
            // route
            inlet => split[i] => enc[i] => out;
        }
    }

    fun void FrequencyRing(int n)
    {
        // allocate filters and encoders
        n => numBands;
        new ResonZ[numBands] @=> split;
        new Encode2[numBands] @=> enc;
        out.gain(1.0/numBands); // volume control
        // patchbay & config
        for(int i; i < numBands; i++)
        {
            // set freq and Q
            split[i].set((14000.0/numBands) * (i+1.0), 24.0);
            // set position
            enc[i].pos((360.0/numBands) * (i), 0.0);
            // route
            inlet => split[i] => enc[i] => out;
        }
    }

    fun void rotate(float delta)
    {
        for(int i; i < numBands; i++)
        {
            enc[i].azi() + delta => enc[i].azi;
            <<< enc[i].azi() >>>;
        }
    }
}
