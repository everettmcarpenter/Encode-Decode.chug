fun void IDSHT(OrderGain2 inputBformat, int resolution)
{
    MonoDecoder sample[resolution];
    for(int i; i < resolution; i++)
    {
        sample[i].sh(Math.sh(2, i * (360.0/resolution), (i * 180.0/resolution) - 90.0))
    }
}