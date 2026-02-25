// name: sh-test.ck
// author: everett m. carpenter
// desc: used to ensure the proper exchange of ChucK float arrays between chugins and user

<<< "Testing SADN" >>>;

SAD3 sad;
float angles[sad.channels()][2];
float sh[][];

for(int i; i < sad.channels(); i++)
{
	Math.random2f(0.0,90.0) => angles[i][0];
	0.0 => angles[i][1];
	cherr <= angles[i][0] <= " " <= angles[i][1] <= " ";
}
cherr <= IO.nl();
sad.placement(angles);
angles.zero();
sad.sh() @=> sh;

for(int i; i < sh.size(); i++)
{
	for(int j; j < sh[i].size(); j++)
	{
		cherr <= sh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();

<<< "Testing DecodeN" >>>;

Decode3 decode;
sh.size(decode.channels());
for(int i; i < decode.channels(); i++)
{
	Math.random2f(-1.0,1.0)	=> sh[i];
	cherr <= sh[i] <= " ";
}
cherr <= IO.nl();
decode.sh(sh);
sh.zero();
decode.sh() @=> sh;

for(int i; i < sh.size(); i++)
{
	for(int j; j < sh[i].size(); j++)
	{
		cherr <= sh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();

<<< "Testing DBDN" >>>;

DBD3 dualband;
sh.size(dualband.channels());
for(int i; i < sh.size(); i++)
{
	for(int j; j < sh[i].size(); j++)
	{
		cherr <= sh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();
dualband.sh(sh);
sh.zero();
dualband.sh() @=> sh;

for(int i; i < sh.size(); i++)
{
	for(int j; j < sh[i].size(); j++)
	{
		cherr <= sh[i][j] <= " ";
	}
	cherr <= IO.nl();
}
cherr <= IO.nl();