// -------------------------- chugl
// spawn points
GPoints points --> GG.scene();
// eyes
GOrbitCamera cam => GG.scene().camera;
// position
cam.posZ( 10 );
// color
GG.scene().backgroundColor( Color.WHITE );
// GWindow.mouseMode( GWindow.MOUSE_DISABLED );
// GWindow.fullscreen();

// instantiate a EnergyCalculator
SinOsc sine( 120.0 ) => Encode3 enc => EnergyCalculator obj( 3 ) => blackhole;

obj.gain( 0.5 );

// locations
vec3 p[0];
// go
for( int i; i < 426; i++ )
	p << 2.0 * obj.point( i );

// position
points.positions( p );
// color
points.color( Color.BLACK );
// size
// points.size( 0.0125 );
// look at me
points.billboard( 1 );

spork ~
	rmsCheck( obj, points );

while( true )
{
	GG.nextFrame() => now;
	GG.dt() * 45.0 + enc.azi() => float azi;
	if( azi >= 360.0 )
		azi - 360.0 => azi;
	else if( azi <= 0.0 )
		azi + 360.0 => azi;
	enc.pos( azi, 0.0 );
}

fun void rmsCheck( EnergyCalculator @ eng, GPoints @ p )
{
	while( true )
	{
		GG.nextFrame() => now;
		
		float rmsValues[0];

		for( int i; i < 426; i++ )
			rmsValues << ( ( 4.0 * eng.RMS( i ) ) + 0.185 );
		p.sizes( rmsValues );
	}
}
