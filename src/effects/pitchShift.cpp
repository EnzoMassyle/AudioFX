 
 #include <../headers/pitchshift.h>
 
vector<vector<double>> PitchShift::changePitch(vector<vector<double>> samples, double pitchFactor)
{

    int numChannels = samples.size();
    vector<vector<double>> output(numChannels, vector<double>(samples[0].size(), 0.0));
    vector<thread> threads;

    for (int chan = 0; chan < numChannels; chan++)
    {
        threads.emplace_back(shiftChannel, samples[chan], pitchFactor, ref(output[chan]));
    }

    for (thread &t : threads)
    {
        t.join();
    }
    return output;
}


void PitchShift::shiftChannel(vector<double> channel, double pitchFactor, vector<double> &out)
{
    int step = PITCH_CHUNK_SZ / NUM_OVERLAP;
    vector<thread> threads;
    random_device device;
    mt19937 gen(device());
    uniform_int_distribution grainStart(-PITCH_OFFSET,PITCH_OFFSET);
    uniform_int_distribution grainSize(PITCH_CHUNK_SZ,PITCH_CHUNK_SZ + 2000);
    for (int start = 0 ; start < channel.size(); start += step)
    {
        int randStart = max(0, start + grainStart(gen));
        int randEnd = grainSize(gen) + randStart;
        if (randEnd >= channel.size()) {
            continue;
        }
        vector<double> slice(channel.begin() + randStart, channel.begin() + randEnd);
        Utils::applyWindow(slice);
        threads.emplace_back(resampleGrain, slice, start, pitchFactor, ref(out));
    }

    for (thread &t : threads)
    {
        t.join();
    }
}

void PitchShift::resampleGrain(vector<double> samples, int start, double pitchFactor, vector<double> &out)
    {
        vector<double> resampled(samples.size(), 0.0);
        resampled.push_back(samples.back());
        for (int i = 0; i < samples.size(); i++)
        {
            double exact = i * pitchFactor;
            if (exact < samples.size()) {
                int idx = (int)exact;
                double frac = exact - idx;
                double alpha = 1 - (exact - idx);
                resampled[i] += alpha * samples[idx] + (1 - alpha) * samples[idx + 1];
            }
        }

        for (int i = 0; i < samples.size(); i++)
        {
            out[i + start] += resampled[i];
        }
    }