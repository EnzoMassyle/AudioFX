#include <../headers/timestretch.h>

vector<vector<double>> TimeStretch::changeSpeed(vector<vector<double>> samples, double shiftFactor)
    {
        int numChannels = samples.size();
        vector<vector<double>> output(numChannels, vector<double>(samples[0].size() * shiftFactor, 0.0));
        vector<thread> threads;

        for (int chan = 0; chan < numChannels; chan++)
        {
            threads.emplace_back(stretchChannel, samples[chan], shiftFactor, ref(output[chan]));
        }

        for (thread &t : threads)
        {
            t.join();
        }

        return output;
    }

void TimeStretch::stretchChannel(vector<double> samples, double shiftFactor, vector<double> &out)
    {
        random_device device;
        mt19937 gen(device());
        uniform_int_distribution grainStart(-TIME_OFFSET,TIME_OFFSET);
        uniform_int_distribution grainSize(TIME_CHUNK_SZ,TIME_CHUNK_SZ + 2000);
        int step = TIME_CHUNK_SZ / NUM_OVERLAP;
        vector<thread> threads;
        for (int start = 0; start < samples.size(); start += step)
        {
            int randStart = max(0, start + grainStart(gen));
            int randEnd = grainSize(gen) + randStart;
            if (randEnd >= samples.size()) {
                continue;
            }
            int shiftedStart = randStart * shiftFactor;
            vector<double> audioSlice(samples.begin() + randStart, samples.begin() + randEnd);
            Utils::applyWindow(audioSlice);
            threads.emplace_back(processSlice, audioSlice, shiftedStart, ref(out));
        }

        for (thread &t : threads)
        {
            t.join();
        }
    }

void TimeStretch::processSlice(vector<double> grain, int shiftedStart, vector<double> &out)
{
    for (int i = 0; i < grain.size(); i++)
    {
        if (i + shiftedStart < out.size())
        {
            out[i + shiftedStart] += grain[i];
        }
    }
}