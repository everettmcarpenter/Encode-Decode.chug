SinOsc sinu(432.0) => Encode5 encode => OrderGain5 volume(0.5) => MonoDecode5 mono => dac;

encode.pos(45.0, 0.0);
mono.sh(Math.sh(5, 45.0, 0.0));

while(true)
{
	encode.pos(encode.azi()+12.0, 0.0);
	cherr <= mono.rms() <= IO.nl();
	1::second => now;
}
