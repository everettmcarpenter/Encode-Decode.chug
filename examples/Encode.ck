Encode1 encode; // try switching around Encode1, Encode2, Encode3 etc.. you can see the difference in channel count
Gain sum((1.0/(encode.chans()*5)))[encode.chans()]; // sum for headphone purposes
SinOsc osc(Math.random2f(134,562))[encode.chans()]; // one oscillator for each coordinate (simply just to show increase in channels through higher orders)
float coordinates[encode.chans()]; // array of current coordinates
float target_coordinates[encode.chans()]; // array of target coordinates

fun void shuffle(float storage[]) { // randomize position
    for(int i; i < storage.size(); i++) {
    Math.random2f(-1.0,1.0) => storage[i];
    }
    for(int i; i < storage.size(); i++) {
    // cherr <= "Real: " <= storage[i] <= " | Chugin: " <= encode.sh(i) <= IO.newline();
    }
}

fun void interpolator(int id) // interpolate through the coordinates
{
    while(true)
    {
        if(coordinates[id] != target_coordinates[id])
        {
            ((target_coordinates[id] - coordinates[id]) * 0.008 + coordinates[id]) => coordinates[id];
        }
        else 
        {
            cherr <= "waiting on: " <= id <= IO.newline();
        }
        encode.sh(coordinates[id],id); // set assigned encoder coefficient (id) to current array entry
        5::ms => now;
    }
}

for(int i; i < encode.chans(); i++) { // spork however you need
    spork ~ interpolator(i);
}

for(int i; i < encode.chans(); i++) { // patch to encode
   
    osc[i] => encode;
    encode.chan(i) => sum[i] => dac.chan(i%2); // patch to dac
}



while(true){
    shuffle(target_coordinates); // shuffle around every once and a while
    Math.random2(100,10000)::ms => now; 
}
