Encode2 enc;
AmbiMath calc;
SinOsc sin(432.0);
WvOut BFormat[enc.channels()];
["X","Y","Z","W","R","S","T","U","V"] @=> string coordinateMarkers[]; // just used to print messages for assurance

for(int i; i < BFormat.size(); i++)
{
    BFormat[i].wavFilename(coordinateMarkers[i]+"-test");
    BFormat[i].record();
    enc.chan(i) => BFormat[i] => blackhole;
}

calc.all(45.0, 15.0, 2) @=> float coord[];

sin.gain(0.5);

enc.sh(coord);

sin => enc => dac;
for(int i; i < coord.size(); i++)
{    
    cherr <= coordinateMarkers[i] <= " " <= coord[i] <= " ";
}
cherr <= IO.newline();

5::second => now;

for(int i; i < BFormat.size(); i++)
{
    BFormat[i].closeFile();
}
