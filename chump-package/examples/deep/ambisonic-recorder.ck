//--------------------------SETUP-------------------------------
string name;
if(me.args()) me.arg(0) => name;
else me.exit();
1 => int N_OBJECTS; // how many sound sources
["W","Y","Z","X","V","T","R","S","U","Q","O","M","K","L","N","P"] @=> string letters[]; // symbols

Encode2 enc[2]; // ENCODE
WvOut record[enc[0].channels()]; // record
Gain input(1.0)[2]; // input "fader"
for(int i; i < enc[0].channels(); i++)
{
    enc[0].chan(i) => record[i] => blackhole;
    enc[1].chan(i) => record[i] => blackhole;
    record[i].wavFilename(name+"_"+i);
}
//--------------------------------------------------------------
// sound sources + modifiers
Impulse imp[2];
NRev rev[2];
LPF reso[2];
// set reverb
rev[0].mix(0.02);
rev[1].mix(0.05);
// set resonators
reso[0].set(892.0, 15);
reso[1].set(657.0, 15);
// patchbay
imp[0] => reso[0] => rev[0] => input[0] => dac;
imp[1] => reso[1] => rev[1] => input[1] => dac;
// plug into our encoders
input[0] => enc[0];
input[1] => enc[1];
// control direction w/ constant elevation
float direction[2];
0.0 => float elevation;

fun void varImpulse(Impulse a, dur speed)
{
    while(true)
    {
        a.next(1.0);
        speed => now;
    } 
}

spork ~ varImpulse(imp[0], 48::ms); // rapid rate impulse
spork ~ varImpulse(imp[1], 36::ms);

for(int tick; tick < 360; tick++)
{
    tick => direction[0]; // rotate
    360-tick => direction[1]; // rotate opposite direction
    reso[0].freq(Math.random2f(456.0, 457.9999)); // random reson are nice
    reso[1].freq(Math.random2f(742.0, 744.9999));
    enc[0].pos(direction[0],elevation); // move!
    enc[1].pos(direction[1], elevation);
    10::ms => now;
}

for(int i; i < record.size(); i++)
{
    record[i].closeFile(); // safely exit
}
