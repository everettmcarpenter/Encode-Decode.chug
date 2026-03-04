//   name: encode.ck
//   author: everett m. carpenter
//   desc: basic ambisonic encoding using Chumbi

/* 
   ideally, you would not want such a large time advance
   it would be best to quickly rotate the encoder by small amounts
   this would create an smoother, "interpolated" movement
   this script rotates by 6 degrees every second
   meaning that it would require 60 seconds to generate a full rotation 
*/

// homer simpson enters the ambisonic universe
SndBuf doh("special:doh") => Encode3 encoder => blackhole; 

// go!
while(true)
{
    // retrieve last given azimuth 
    // add a few degrees, rotating the sound
    encoder.azi() + 6.0 => encoder.azi;
    <<< "azimuth: ", encoder.azi() >>>;

    1::second => now; // advance time
}