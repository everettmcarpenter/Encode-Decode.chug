//   name: advanced-decode.ck
//   author: everett m. carpenter
//   desc: advanced ambisonic decoding using Chumbi

// homer simpson enters the ambisonic universe, and exits using Decode
SndBuf doh("special:doh") => Encode1 encoder => Decode1 decoder => dac; 

float speakerSH[4][4]; // save the spherical harmonics here
for(int n; n < 4; n++)
{
    // math.sh(int order, float azimuth, float zenith)
    // this makes each speaker 90 degrees apart, with a 45.0 offset
    Math.sh(1, (n * 90.0) + 45.0, 0.0) @=> speakerSH[n];
}

// give the decoder our spherical harmonics
decoder.sh(speakerSH);
// retrieve them 
decoder.sh() @=> speakerSH;

// let's look at the spherical harmonics
for(int i; i < speakerSH.size(); i++)
{
    for(int j; j < speakerSH[i].size(); j++)
    {
        cherr <= "Speaker " <= i+1 <= "'s " <= j <= "th spherical harmonic is: " <= speakerSH[i][j] <= IO.nl();
    }
    cherr <= "----------------------------------------------------" <= IO.nl();
}
