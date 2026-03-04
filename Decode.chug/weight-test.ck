// name: weights-test.ck
// author: everett m. carpenter
// desc: used to ensure the proper exchange of ChucK float arrays between chugins and user

<<< "Testing SADN" >>>;

SAD1 sad;
float weights[sad.channels()];

for(int i; i < sad.channels(); i++)
{
	Math.random2f(-1.0,1.0)	=> weights[i];
	cherr <= weights[i] <= " ";
}
cherr <= IO.nl();
sad.weights(weights);
weights.zero();
sad.weights() @=> weights;

for(int i; i < sad.channels(); i++)
{
	cherr <= weights[i] <= " ";
}
cherr <= IO.nl();

<<< "Testing DecodeN" >>>;

Decode1 decode;
weights.size(decode.channels());
for(int i; i < decode.channels(); i++)
{
	Math.random2f(-1.0,1.0)	=> weights[i];
	cherr <= weights[i] <= " ";
}
cherr <= IO.nl();
decode.weights(weights);
weights.zero();
decode.weights() @=> weights;

for(int i; i < decode.channels(); i++)
{
	cherr <= weights[i] <= " ";
}
cherr <= IO.nl();

<<< "Testing DBDN" >>>;

DBD5 dualband;
weights.size(dualband.channels());
for(int i; i < dualband.channels(); i++)
{
	Math.random2f(-1.0,1.0)	=> weights[i];
	cherr <= weights[i] <= " ";
}
cherr <= IO.nl();
dualband.weights(weights);
weights.zero();
dualband.weights() @=> weights;

for(int i; i < dualband.channels(); i++)
{
	cherr <= weights[i] <= " ";
}
cherr <= IO.nl();