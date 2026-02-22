// --------------------------------------
// Encode OSC controller   
//      example by : everett m. carpenter
//
// Uses radar style touchOSC controller where the magnitude of the circular coordinate vector is mapped so when 
// it's fully extended, it is along the equator directly level with listener's ears. When at it's shortest, it
// is 90 degrees above the listener's head. Angle between the vector and a unit vector pointing directly infront 
// of the listener corresponds to the azimuth of the sound source.
// --------------------------------------

OscIn wireIn; // receive data
OscMsg wireDecrypt; // decrypt data
Encode1 enco; // first order ambisonic encoder

float angles[2]; // store angles here
4559 => int port => wireIn.port; // some UDP port to use, can be any

wireIn.listenAll(); // for the sake of translatability, we'll listen to all addresses

while(true)
{
    wireIn => now; // wait till the mail comes in
    while(wireIn.recv(wireDecrypt))
    {
        if(wireDecrypt.numArgs() == 2)
        {
            (wireDecrypt.getFloat(1) * 360.0)  => angles[0]; // OSC values are 0.0,1.0 so make it from 0.0,360.0
            90.0 - (wireDecrypt.getFloat(0) * 90.0) => angles[1]; // constrain to 0.0 and 90.0
            cherr <= "Azimuth " <= angles[0] <= " Zenith " <= angles[1] <= IO.newline();
        }
    }
    enco.pos(angles[0], angles[1]); // update our position, can also be spork'd if expecting multiply OSC messages regarding different things
}