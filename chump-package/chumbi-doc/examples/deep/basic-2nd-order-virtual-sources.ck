if(dac.channels() < 9) me.exit(); // not enough channels?
int n;
if(me.args()) me.arg(0) => Std.atoi => n; // how many sources?

float speaks[9][2];
for(int i; i < speaks.size(); i++)
{
   i*(360.0/8.0) => speaks[i][0]; // ring of 8 dividing 360 degrees
}

Encode2 enc[n];
NRev rev[n];
SinOsc obj[n];
SAD2 deco(speaks); // constructor!

fun void randomPlacement(Encode2 p)
{
    Math.random2f(0.0, 360.0) => float randomAzi;
    while(true)
    {
        randomAzi+Math.random2f(-4.5,4.5) => randomAzi;
        p.pos(randomAzi,0);
        // <<< randomAzi >>>;
        10::ms => now;
    }
}

fun void randomPitch(SinOsc s)
{
    42.0 => float base;
    while(true)
    {
        Math.random2(1,5) => float random;
        Math.random2f(1.0,2.5) * random => random;
        base * random => s.freq;
        for(int i; i < 6; i++)
        {
            s.freq()*2 => s.freq;
            Math.random2f(4.5,450)::ms => now;
            //100::ms => now;
            s.gain(0.0);
            100::ms => now;
            s.gain(1.0);
            (s.freq()/random)*3 => s.freq;
            Math.random2f(4.5,450)::ms => now;
            //100::ms => now;
            s.freq()/8.5 => s.freq;
        }
        5000::ms => now;
    }
}


for(int i; i < n; i++)
{
    enc[i].gain(1.0/n); // scale
    obj[i].freq(Math.random2f(34.0,1652.0));
    obj[i] => rev[i] => enc[i] => deco => blackhole;
    rev[i].mix(0.125);
    spork ~ randomPlacement(enc[i]);
    spork ~ randomPitch(obj[i]);
}

for(int i; i < deco.channels(); i++)
{
    deco.chan(i) => dac.chan(i);
}

while(true)
{
    100::ms => now;
}

