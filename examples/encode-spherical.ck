Encode3 enc;
enc.pos(45.0, 0.0);
enc.sh() @=> float n_sh[];
for(int i; i < n_sh.size(); i++)
{
	cherr <= n_sh[i] <= " ";
}
cherr <= IO.nl();
