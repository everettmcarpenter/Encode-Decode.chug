@import "../../classes/plucked-string.ck"

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
Impulse imp[n];
Gain up(4.0)[n];
StringModel obj[n];
[0, 156, 50, 78, 100] @=> int spaces[];

278 => int mod;

SAD2 deco(speaks); // constructor!

fun void randomPlacement(Encode2 p)
{
    Math.random2f(0.0, 360.0) => float randomAzi;
    while(true)
    {
        randomAzi+Math.random2f(0.5,1.5) => randomAzi;
        if(randomAzi > 360) randomAzi-360.0 => randomAzi;
        p.pos(randomAzi,0);
        <<< randomAzi >>>;
        100::ms => now;
    }
}

fun void randomStrike(Impulse s)
{
    while(true)
    {
        for(int i; i < 6; i++)
        {
            s.next(1.0);
            Math.random2f(600,2450)::ms => now;
            s.next(1.0);
            Math.random2f(4.5,450)::ms => now;
            2000::ms => now;
        }
        5000::ms => now;
    }
}


for(int i; i < n; i++)
{
    enc[i].gain(1.0); // scale
    obj[i].set(spaces[Math.random2(0,spaces.size()-1)]+mod,Math.random2f(0.99,0.999));
    imp[i] => obj[i] => up[i] => rev[i] => enc[i] => deco => blackhole;
    rev[i].mix(0.0125);
    spork ~ randomPlacement(enc[i]);
    spork ~ randomStrike(imp[i]);
}

for(int i; i < deco.channels(); i++)
{
    deco.chan(i) => dac.chan(i);
}

while(true)
{
    100::ms => now;
}

