//----------------------------------------------------------------------------
// name: energy-vector.ck
// desc: collect an overall energy value from accelerometers from 
//       the app DataOSC
//----------------------------------------------------------------------------
// see if port is supplied on command line
int port;
Event go;
OscOut out;
string hostname;

float current[2];

if( me.args() ) { me.arg(0) => hostname; me.arg(1) => Std.atoi => port; }
    
// default port
else 6449 => port;

out.dest(hostname, port);

// print
cherr <= "listening for OSC messages over port: " <= port
      <= "..." <= IO.newline();

fun void oscDo(string address, int port, int who)
{
    OscIn oin;
    OscMsg msg;
    port => oin.port;
    oin.addAddress(address);
    float y_1; // n-1
    float y_0; // current 
    float x; // in 
    1.0 => float scale;
    while(true)
    {
        go => now;
        while(oin.recv(msg))
        {
            <<< y_1, scale , msg.getFloat(0), y_0 >>>;
            (y_1 + scale) * Math.fabs(msg.getFloat(0)) => y_0;
            y_0 / (scale*scale*scale*scale) => current[who];
            y_0 => y_1;
        }
    }
}

spork ~ oscDo("/data/motion/accelerometer/x", port, 0);
spork ~ oscDo("/data/motion/accelerometer/y", port, 1);

// infinite time loop
while( true )
{
    go.broadcast();
    10::ms => now;
    out.start("/data/motion/energy");
    out.add(current[0]);
    out.add(current[1]); 
    out.send();
    // <<< current[0], current[1] >>>;
}
