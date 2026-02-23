int SOURCE_COUNT;
if(me.args()) me.arg(0) => Std.atoi => SOURCE_COUNT;
else me.exit();

Encode3 enc[SOURCE_COUNT];
SinOsc sin[SOURCE_COUNT];
OrderGain3 sum(1.0/(SOURCE_COUNT));
WvOut record[sum.channels()]; // record

for(int i; i < SOURCE_COUNT; i++)
{
    enc[i].pos(i*(360.0/SOURCE_COUNT),i*(15.0/SOURCE_COUNT));
    Math.random2f(46.0,1687.0) => sin[i].freq;
    sin[i] => enc[i] => sum;
}

for(int i; i < record.size(); i++)
{
    sum.chan(i) => record[i] => blackhole;
    record[i].wavFilename("spat"+"_"+i);
}

fun void cameraSetup()
{
    GOrbitCamera cam --> GG.scene();
    GWindow.mouseMode(GWindow.MouseMode_Disabled);
    GG.scene().camera(cam);
    GG.scene().ambient(@(0.1,0.7,1));
    GG.scene().backgroundColor(Color.SKYBLUE);
}

fun void createSpace()
{
    WireframeMaterial wire;
    wire.thickness(2);
    wire.topology(Material.Topology_LineList);
    GSphere sphere;
    sphere.pos(@(0,0,0));
    wire.color(@(0,0,0));
    sphere.sca(2.25);
    sphere.mat(wire);
    sphere --> GG.scene();
}

fun void encodeTracker(Encode3 ncode[])
{
    ncode.size() => int size;
    vec3 where[size];
    float azi[size];
    float zeni[size];
    GSuzanne suz[size];
    for(int i; i < size; i++)
    {
        suz[i].sca(0.075);
        suz[i] --> GG.scene();
        suz[i].rotX(Math.pi*2.5);
        suz[i].aoFactor(50.0);
        suz[i].shine(Math.random2f(10.0,50.0));
        suz[i].color(Color.random());
    }
    while(true)
    {
        for(int i; i < size; i++)
        {
            ncode[i].azi()*(Math.pi/180.0) => azi[i];
            ncode[i].zeni()*(Math.pi/180.0) => zeni[i];
            //@(Math.cos(azi[i]),0.0,Math.sin(azi[i])) => where[i]; 
            @(Math.sin(azi[i])*Math.cos(zeni[i]),Math.sin(azi[i])*Math.sin(zeni[i]),Math.cos(azi[i])) => where[i]; 
            //<<< azi[i], zeni[i], where[i] >>>;
            suz[i].pos(where[i]);
            suz[i].rotX(azi[i]*zeni[i]*1.75);
        }
        GG.nextFrame() => now;
    }
}

fun void visual()
{
    cameraSetup();
    createSpace();
    spork ~ encodeTracker(enc);
    GPointLight forward;
    forward.falloff(2.5);
    forward.radius(2.0);
    forward.intensity(10.0);
    forward.posWorld(@(1.0,0.0,0.0));
    forward.color(@((.827, .69, .514)));
    forward --> GG.scene();
    while (true) 
    {
        GG.nextFrame() => now;
    }
}

spork ~ visual();

int count;
float temp;
float speed[SOURCE_COUNT];

for(int i; i < SOURCE_COUNT; i++)
{
	Math.random2f(0.0,0.5) => speed[i];
}

while(true)
{
    
    for(int i; i < SOURCE_COUNT; i++)
    {
        if(count%360 == 0 && Math.random2(0,1) == 1) Math.random2f(-1.0,1.0) => speed[i];
        if(enc[i].azi() > 360.0) 
		{
        	enc[i].azi() - 360.0 => temp; 
 			enc[i].pos(temp + (speed[i]*Math.random2f(0.0,5.0)), (enc[i].zeni() + (speed[i]*Math.random2f(0.0,0.125))));
		}
		else if(enc[i].azi() < 0.0)
		{
			enc[i].azi() + 360.0 => temp;
			enc[i].pos(temp + (speed[i]*Math.random2f(0.0,5.0)), (enc[i].zeni() + (speed[i]*Math.random2f(0.0,0.125)))); 
		}
		else enc[i].pos(enc[i].azi() + (speed[i]*Math.random2f(0.0,5.0)), (enc[i].zeni() + (speed[i]*Math.random2f(0.0,0.125))));  
    }
    count++;
    if(count == 1200)
    {
        for(int i; i < record.size(); i++)
        {
            record[i].closeFile();
        }
        me.exit();
    }
    GG.nextFrame() => now;
}
