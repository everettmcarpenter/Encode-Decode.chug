// instantiate a EnergyCalculator
SinOsc sine( 200.0 ) => Encode5 enc => EnergyCalculator obj( 5 ) => blackhole;

enc.pos( 45.0, 0.0 );

10::second => now;

for( int i; i < 426; i++ )
{
	<<< obj.point( i ), obj.RMS( i ) >>>;
}

