WvOut record[4];
SinOsc sin(440) => Encode1 enc => BAFormat ba => ABFormat ab => blackhole;

enc.pos(26.0,34.0);

for(int i; i < record.size(); i++)
{
    record[i].wavFilename("abba-"+i+".wav");
    enc.chan(i) => record[i] => blackhole;
}

5::second => now;

for(int i; i < record.size(); i++)
{
    record[i].closeFile();
}