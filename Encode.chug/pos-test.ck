SinOsc sin => Encode1 enc => blackhole;

enc.pos(45.0,-12.0);

500::ms => now;

enc.sh() @=> float sh[];

for(int i; i < sh.size(); i++)
{
	enc.sh(Math.randomf() * 360.0, i);
	cherr <= sh[i] <= " ";
}

cherr <= IO.nl();
