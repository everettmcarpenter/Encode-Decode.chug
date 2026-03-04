float speak[16][2];

for(int i; i < speak.size(); i++)
{
    (360.0/(speak.size()-1))*i => speak[i][0];
}

Encode2 enc;
SAD3 sad(speak);
Impulse imp;
LPF lp;
lp.set(452.0, 25);
WvOut SpeakFeed[sad.channels()];

imp.gain(1.0);
enc.gain(1.0);

float place[][];
float encplace[];

sad.placement() @=> place;
enc.sh() @=> encplace;

fun void varImpulse(Impulse a, dur speed)
{
	while(true)
	{
		a.next(1.0);
        speed => now;
    }
}

for(int i; i < place.size(); i++)
{
    cherr <= "Speaker: " <= i+1 <= " angle: " <= (360.0/(speak.size()-1))*i <= IO.newline();
    for(int j; j < place[i].size(); j++)
    {
        cherr <= place[i][j] <= " ";
    }
    cherr <= IO.newline();
}

cherr <= "Virtual source @: ";
for(int i; i < encplace.size(); i++)
{
	cherr <= encplace[i] <= " ";
}
cherr <= IO.newline();

imp => lp => enc => sad => blackhole;

for(int i; i < sad.channels(); i++)
{
    //SpeakFeed[i].wavFilename("SAD_TEST_SPEAKER_"+(i+1));
    sad.chan(i) => SpeakFeed[i] => blackhole;
    SpeakFeed[i].record();
    if(dac.channels() >= sad.channels())
    {
    	sad.chan(i) => dac.chan(i);
    }
}

spork ~ varImpulse(imp, 34::ms);

while(true)
{
    float azi;
    Math.random2f(45.0,5000.6)::ms => dur wait;
    lp.set(Math.random2f(236.0, 875.0), 25);
    Math.random2(-45,360) => int i;
    while(i >= azi)
    {
        azi+0.1 => azi;
        enc.pos(azi, 0);
    }
    //enc.pos(90,0);
    wait => now;
}
