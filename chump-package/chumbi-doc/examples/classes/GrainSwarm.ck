@import "granulator.ck"

public class GrainSwarm extends Chugraph
{
    Granulator grains[32] => Gain sum(1.0/24.0) => outlet;

    float cpitch; float cposition; float csize; string cfile; int cloop; float crandomsize; float crandompos;

    fun void GrainSwarm(string file)
    {
        for(int i; i < grains.size(); i++)
        {
            grains[i].fileChange(file);
            grains[i].grainSize(50.0);
            1.0 => grains[i].rand_grain_duration;
            grains[i].play();
        }
    }

    fun void GrainSwarm()
    {
        for(int i; i < grains.size(); i++)
        {
            grains[i].grainSize(50.0);
            1.0 => grains[i].rand_grain_duration;
            grains[i].play();
        }
    }

    fun void interpolation(int type)
    {
        for(int i; i < grains.size(); i++)
        {
            grains[i].interpolation(type);
        }
    }

    fun void loop(int onOff)
    {
        for(int i; i < grains.size(); i++)
        {
            grains[i].loop(onOff);
        }
        onOff => cloop;
    }

    fun void fileSwap(string nfile)
    {
        for(int i; i < grains.size(); i++)
        {
            grains[i].fileChange(nfile);
        }
        nfile => cfile;
    }

    fun string file() { return cfile; }

    fun void grainSize(float size)
    {
        size => csize;
        for(int i; i < grains.size(); i++)
        {
            grains[i].grainSize(size);
        }
    }

    fun float grainSize() { return csize; }

    fun void randomGrainSize(float rand)
    {
        if(rand < 0) return;
        rand => crandomsize;
        for(int i; i < grains.size(); i++)
        {
            grains[i].randomGrainSize(rand);
        }
    }

    fun float randomGrainSize() { return crandomsize; }

    fun void pitch(float pitches[])
    {
        for(int i; i < grains.size(); i++)
        {
            grains[i].setPitch(pitches[i%pitches.size()]);
        }
    }

    fun void pitch(float npitch)
    {
        npitch => cpitch;
        for(int i; i < grains.size(); i++)
        {
            grains[i].setPitch(npitch);
        }
    }

    fun float pitch() { return cpitch; }

    fun void position(float nposition)
    {
        if(nposition < 0.0) me.exit();
        nposition => cposition;
        for(int i; i < grains.size(); i++)
        {
            grains[i].setPosition(nposition);
        }
    }

    fun float position() { return cposition; }

    fun void randomPosition(float rand)
    {
        if(rand < 0) me.exit();
        rand => crandompos;
        for(int i; i < grains.size(); i++)
        {
            grains[i].randomGrainSize(rand);
        }
    }

    fun float randomPosition() { return crandompos; }
}
