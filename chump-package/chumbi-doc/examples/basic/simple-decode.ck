//   name: simple-decode.ck
//   author: everett m. carpenter
//   desc: basic ambisonic decoding using Chumbi

// homer simpson enters the ambisonic universe, and exits using Decode
SndBuf doh("special:doh") => Encode1 encoder => SAD1 decoder => dac; 

[ [45.0, 0.0,], // SAD (Sampling Ambisonic Decoder) 
  [135.0, 0.0], // configured by giving it the spherical coordinates of the speakers used
  [225.0, 0.0], // SAD assumes the first angle pair is the placement of the first output's speaker
  [315.0, 0.0] ] @=> float speakerAngles[][]; // these angles are site specific! higher detail = better

// give the decoder your speaker arrangement
decoder.placement(speakerAngles);
// the .placement() call returns the spherical harmonics of the angles you previously gave
decoder.placement() @=> float speakerSH[][];

// go!
while(true)
{
    // retrieve last given azimuth 
    // add a few degrees, rotating the sound
    encoder.azi() + 6.0 => encoder.azi;
    <<< "azimuth: ", encoder.azi() >>>;

    1::second => now; // advance time
}