float speak[4][2];

for(int i; i < speak.size(); i++)
{
    (360.0/speak.size())*i => speak[i][0];
}

Encode1 enc;
DBDN sad;
sad.placement(speak);
Impulse imp;
WvOut SpeakFeed[sad.channels()];

imp.gain(1.0);
enc.gain(1.0);

float place[][];
float encplace[];

// sad.placement() @=> place;
enc.sh() @=> encplace;

fun void varImpulse(Impulse a, dur speed)
{
	while(true)
	{
		a.next(1.0);
        speed => now;
    }
}
/*
for(int i; i < place.size(); i++)
{
    cherr <= "Speaker: " <= i+1 <= " angle: " <= 90*i <= IO.newline();
    for(int j; j < place[i].size(); j++)
    {
        cherr <= place[i][j] <= " ";
    }
    cherr <= IO.newline();
}
*/
cherr <= "Virtual source @: ";
for(int i; i < encplace.size(); i++)
{
	cherr <= encplace[i] <= " ";
}
cherr <= IO.newline();

imp => enc => sad => blackhole;

for(int i; i < sad.channels(); i++)
{
    SpeakFeed[i].wavFilename("DBDN_TEST_SPEAKER_"+(i+1));
    sad.chan(i) => SpeakFeed[i] => blackhole;
    SpeakFeed[i].record(1);
    if(dac.channels() >= sad.channels())
    {
    	sad.chan(i) => dac.chan(i);
    }
}

spork ~ varImpulse(imp, 34::ms);
int stop;
while(true)
{
    float azi;
    15::ms => dur wait;
    Math.random2(-45,360) => int i;
    while(i >= azi)
    {
        azi+0.1 => azi;
        enc.pos(azi, 0);
    }
    //enc.pos(90,0);
    stop++;
    wait => now;
    if(stop == 500) 
    {
        for(int i; i < SpeakFeed.size(); i++)
        {
            SpeakFeed[i].closeFile();
        }
        me.exit();
    }
}
