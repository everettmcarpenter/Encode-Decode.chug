Encode2 enc; 
SinOsc sin(Math.random2f(145,356));
sin => Gain g(0.24) => enc => dac;
while(true)
{
    for(int i; i < enc.chans(); i++)
    {
        Math.random2f(-1.0,1.0) => float temp;
        //cherr <= temp <= IO.newline();
        enc.sh(temp,i);
        cherr <= enc.sh(i) <= IO.newline();
    }
    100::ms => now;
}
