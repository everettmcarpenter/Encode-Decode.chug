//   name: encode2.ck
//   author: everett m. carpenter
//   desc: a bit of a "hack" for ambisonic encoding in chumbi

// homer simpson enters the ambisonic universe
SndBuf doh("special:doh") => OrderGain3 encoder => blackhole; 

// go! (doh!)
while(true)
{
    // calculate spherical harmonics at a random position 
    // position is wrapped to [0, 360] for azimuth and [0, 90] for elevation angle
    // (typically best to stay in this range for Math.sh())
    Math.sh(3, Math.randomf() * 360.0, Math.randomf() * 90.0) @=> float sh[];

    // in this instance, the weights act as spherical harmonic coefficients
    encoder.weights(sh);

    1::second => now; // advance time
}