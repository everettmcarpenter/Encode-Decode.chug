// name: weights-test.ck
// author: everett m. carpenter
// desc: used to ensure the proper exchange of ChucK float arrays between chugins and the user

SAD1 decoder;
float weights[decoder.channels()];

for(int i; i < decoder.channels(); i++)
{
	Math.random2f(-1.0,1.0)	=> weights[i];
	cherr <= weights[i] <= " ";
}
cherr <= IO.nl();
decoder.weights(weights);
weights.zero();
decoder.weights() @=> weights;

for(int i; i < decoder.channels(); i++)
{
	cherr <= weights[i] <= " ";
}
