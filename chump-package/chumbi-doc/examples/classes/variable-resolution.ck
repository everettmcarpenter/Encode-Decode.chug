// patch
SawOsc seesaw(536.0) => Encode3 encoder => OrderGain3 sum(0.8) => blackhole;

float sh[encoder.channels()];
float weights[encoder.channels()];
float targetWeights[encoder.channels()];

1.0 => sh[0];
1.0 => weights[0];

for(int i; i < targetWeights.size(); i++) { Math.pow(1.0, i) => targetWeights[i]; }

fun void lerpArray(float origin[], float target[], float t)
{
    for(int i; i < origin.size(); i++)
    {
        origin[i] + t * (target[i] - origin[i]) => origin[i];
    }
}

// record
fun void beginRecord(OrderGain3 sum, WvOut recorder[])
{
    for(int i; i < sum.channels(); i++)
    {
        recorder[i].wavFilename("../recordings/"+"graincode"+"-"+i+".wav");
        sum.chan(i) => recorder[i] => blackhole;
    }
}

// recorder
WvOut bformat[encoder.channels()];

// lets record it
spork ~ beginRecord(sum, bformat);

for(int i; i < 1000; i++)
{
    //for(int j; j < sh.size(); j++) { cherr <= sh[j] <= " "; }
    //cherr <= IO.nl();
    lerpArray(sh, Math.sh(5, 45.0, 0.0), i/1000.0);
    lerpArray(weights, targetWeights, i/100.0);
    encoder.weights(weights);
    encoder.sh(sh);
    50::ms => now;
}