// Calculation of re and rv in first order models as defined by Gerzon

// "Here we list some basic "primitive" models, describing them in terms of the information received by the ear/brain system when responding to a number of n equally distant sound signals P placed in direction with direction cosines (x,y,z).
@import "../classes/Speaker.ck"
@import "../classes/Source.ck"

45.0 => float SOURCE_DIRECTION;
15.0 => float SOURCE_ELEVATION;
4 => int BUFFER_SIZE;
float b_buffer[4][BUFFER_SIZE];

AmbiMath calc;
Encode1 encode;
SinOsc sine(354.0);
Gain decode[4][4];
Gain out[4];
Speaker speak[4]; // first order, 4 speakers
Source sound(SOURCE_DIRECTION,SOURCE_ELEVATION); // one sound source with azimuth 45 degrees and zenith 15 degrees

vec3 r_v;

[45.0, 135.0, 225.0, 315.0] @=> float direction[]; // azimuths of speakers
[0.0, 0.0, 0.0, 0.0] @=> float elevation[]; // zeniths of speakers

float sound_sh[4];
calc.all(sound.x,sound.y,sound.z,sound_sh,1);
encode.sh(sound_sh);
sine => encode => blackhole;

fun vec3 velocity(Speaker quad[], float pressure[])
{
    vec3 top;
    float bottom;
    for(int i; i < quad.size(); i++)
    {
        quad[i].placement * pressure[i] +=> top;
        pressure[i] +=> bottom;
    }
    if(bottom == 0.0) return @(0,0,0);
    cherr <= (top * (1.0/(bottom+0.0000000001))) <= IO.newline();
    return (top * (1.0/(bottom+0.0000000001)));
}

fun int collector(UGen in, float buffer[])
{
    for(int i; i < buffer.size(); i++)
    {
        in.last() => buffer[i];
        1::samp => now; 
    }
    return 1;
}

for(int i; i < decode.size(); i++)
{
    1.0/decode.size() => float weight;
    speak[i].update(direction[i], elevation[i]);
    float temp[decode[i].size()];
    calc.all(speak[i].x, speak[i].y, speak[i].z, temp, 1);
    weight *=> temp[0];
    (weight+weight) *=> temp[1];
    (weight+weight) *=> temp[2];
    (weight+weight) *=> temp[3];
    for(int j; j < decode[i].size(); j++)
    {
        decode[i][j].gain(temp[j]);
        cherr <= temp[j] <= " ";
        encode.chan(j) => decode[i][j] => out[i] => blackhole;
    }
}

while(true) 
{
    float pressures[4];
    for (int i; i < out.size(); i++) 
    {
        out[i].last() => pressures[i];  // Get current sample
    }
    velocity(speak, pressures) @=> r_v;
    cherr <= "Velocity vector: " <= r_v <= " (magnitude: " <= r_v.magnitude() <= ")" <= IO.newline();
    1::samp => now;
}