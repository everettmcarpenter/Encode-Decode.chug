// Calculation of re and rv in first order models as defined by Gerzon

// "Here we list some basic "primitive" models, describing them in terms of the information received by the ear/brain system when responding to a number of n equally distant sound signals P placed in direction with direction cosines (x,y,z).
@import "../classes/Speaker.ck"
@import "../classes/Source.ck"

90.0 => float SOURCE_DIRECTION;
0.0 => float SOURCE_ELEVATION;
4 => int BUFFER_SIZE;
float b_buffer[4][BUFFER_SIZE];

AmbiMath calc;
Encode1 encode[2];
SinOsc sine(354.0)[2];
sine[1].freq(578.0);
Gain scale(1.0/(sine.size()+sine.size()))[sine.size()];
Gain decode[4][4];
Gain out[4];
Speaker speak[4]; // first order, 4 speakers
Source sound(SOURCE_DIRECTION,SOURCE_ELEVATION); // one sound source 

vec3 r_v;

[45.0, 135.0, 225.0, 315.0] @=> float direction[]; // azimuths of speakers
[0.0, 0.0, 0.0, 0.0] @=> float elevation[]; // zeniths of speakers

float sound_sh[2][4];
calc.all(SOURCE_DIRECTION,SOURCE_ELEVATION,sound_sh[0],1);
calc.all(SOURCE_DIRECTION+45.0, SOURCE_ELEVATION, sound_sh[1], 1);
encode[0].sh(sound_sh[0]);
encode[1].sh(sound_sh[1]);

sine[0] => scale[0] => encode[0] => blackhole;
// sine[1] => scale[1] => encode[1] => blackhole;
fun void visual()
{
    GOrbitCamera cam --> GG.scene();
    GWindow.mouseMode(GWindow.MouseMode_Disabled);
    GG.scene().camera(cam);
    WireframeMaterial wire;
    wire.thickness(0.02);
    wire.topology(2);
    GSphere sphere;
    GCircle point;
    point.pos(@(0,0,0));
    sphere.pos(@(0,0,0));
    sphere.sca(2.05);
    sphere.mat(wire);
    point.color(@(1.0, .427, .76));
    point.sca(0.225);
    sphere --> GG.scene();
    point --> GG.scene();
    vec3 swap; // since in ambisonics, the y axis is forwards, and z upwards. swapping y for z is only done to fix the visual

    while (true) 
    {
        @(r_v.x,r_v.z,r_v.y) @=> swap;
        point.pos(swap);
        point.lookAt(@(0,0,0));
        GG.nextFrame() => now;
    }
}

fun vec3 eulers(vec3 placement)
{
    vec3 eulers;
    // x axis
    Math.acos((placement.dot(@(1,0,0)))/(placement.magnitude())) => eulers.x;
    // y axis
    Math.acos((placement.dot(@(0,1,0)))/(placement.magnitude())) => eulers.y;
    // z axis
    Math.acos((placement.dot(@(0,0,1)))/(placement.magnitude())) => eulers.z;
    return eulers;
}

fun void rotateSound(Encode1 enc, Source sound)
{
    float h;
    float temp_c[4];
    while(true)
    {
        calc.all(45.0+h, 0.0, temp_c, 1);
        sound.update(45.0+h, 10.0);
        enc.sh(temp_c);
        0.005 +=> h;
        GG.nextFrame() => now;
    }
}

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
    return (top * (1.0/(bottom)));
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
        // cherr <= temp[j] <= " ";
        encode[0].chan(j) => decode[i][j] => out[i] => blackhole;
        encode[1].chan(j) => decode[i][j] => out[i] => blackhole;
    }
}

spork ~ visual();
// spork ~ rotateSound(encode[0], sound);

while(true) 
{
    float pressures[4];
    for (int i; i < out.size(); i++) 
    {
        out[i].last() => pressures[i];  // Get current sample
    }
    velocity(speak, pressures) @=> r_v;
    // cherr <= "Velocity vector: " <= r_v <= " (magnitude: " <= r_v.magnitude() <= ")" <= IO.newline();
    1::samp => now;
}