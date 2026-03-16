<<< "Testing ABFormat and BAFormat." >>>;

ABFormat ab;
BAFormat ba;

SinOsc sine[4] => ab => ba => dac;
5::second => now;
ba =< dac;

<<< "ABFormat & BAFormat operational." >>>;

sine[0] =< ab;

<<< "Testing EncodeN" >>>;

sine[0] => Encode1 enc1 => dac;

enc1.pos(45.0, 0.0);
2::second => now;
enc1.sh() @=> float sh1[];
for(int i; i < sh1.size(); i++)
{
    cherr <= sh1[i] <= " ";
}
cherr <= IO.nl();
enc1 =< dac;
<<< "Encode1 operational" >>>;
//------------------------------------------
sine[0] => Encode2 enc2 => dac;

enc2.pos(45.0, 0.0);
2::second => now;
enc2.sh() @=> float sh2[];
for(int i; i < sh2.size(); i++)
{
    cherr <= sh2[i] <= " ";
}
cherr <= IO.nl();
enc2 =< dac;
<<< "Encode2 operational" >>>;
//------------------------------------------
sine[0] => Encode3 enc3 => dac;

enc3.pos(45.0, 0.0);
2::second => now;
enc3.sh() @=> float sh3[];
for(int i; i < sh3.size(); i++)
{
    cherr <= sh3[i] <= " ";
}
cherr <= IO.nl();
enc3 =< dac;
<<< "Encode3 operational" >>>;
//------------------------------------------
sine[0] => Encode4 enc4 => dac;

enc4.pos(45.0, 0.0);
2::second => now;
enc4.sh() @=> float sh4[];
for(int i; i < sh4.size(); i++)
{
    cherr <= sh4[i] <= " ";
}
cherr <= IO.nl();
enc4 =< dac;
<<< "Encode4 operational" >>>;
//------------------------------------------
sine[0] => Encode5 enc5 => dac;

enc5.pos(45.0, 0.0);
2::second => now;
enc5.sh() @=> float sh5[];
for(int i; i < sh5.size(); i++)
{
    cherr <= sh5[i] <= " ";
}
cherr <= IO.nl();
enc5 =< dac;
<<< "Encode5 operational" >>>;
//------------------------------------------
<<< "Testing SADN" >>>;

SAD3 sad;
float angles[sad.channels()][2];
float sh[][];

for(int i; i < sad.channels(); i++)
{
	Math.random2f(0.0,90.0) => angles[i][0];
	0.0 => angles[i][1];
	cherr <= angles[i][0] <= " " <= angles[i][1] <= " ";
}
cherr <= IO.nl();
sad.placement(angles);
angles.zero();
sad.sh() @=> sh;

for(int i; i < sh.size(); i++)
{
	for(int j; j < sh[i].size(); j++)
	{
		cherr <= sh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();

<<< "Testing DecodeN" >>>;

Decode3 decode;
sh.size(decode.channels());
for(int i; i < sh.size(); i++)
{
	for(int j; j < sh[i].size(); j++)
	{
        Math.random2f(-1.0,1.0) => sh[i][j];
		cherr <= sh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();
decode.sh(sh);
sh.zero();
decode.sh() @=> sh;

for(int i; i < sh.size(); i++)
{
	for(int j; j < sh[i].size(); j++)
	{
		cherr <= sh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();

<<< "Testing DBDN" >>>;

DBD3 dualband;
float dbdnsh[16][2];
for(int i; i < dbdnsh.size(); i++)
{
	for(int j; j < dbdnsh[i].size(); j++)
	{
        Math.randomf() * 360.0 => dbdnsh[i][j];
		cherr <= dbdnsh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();
dualband.placement(dbdnsh);
dbdnsh.zero();
dualband.sh() @=> dbdnsh;

for(int i; i < dbdnsh.size(); i++)
{
	for(int j; j < dbdnsh[i].size(); j++)
	{
		cherr <= dbdnsh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();


<<< "Testing MonoDecode5" >>>;
SinOsc sinu(432.0) => Encode5 encode => OrderGain5 volume(0.5) => MonoDecode5 mono => dac;

encode.pos(45.0, 0.0);
mono.sh(Math.sh(5, 45.0, 0.0));

repeat(5)
{
	encode.pos(encode.azi()+12.0, 0.0);
	cherr <= mono.rms() <= IO.nl();
	1::second => now;
}