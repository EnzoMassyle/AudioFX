#include "../../include/convreverb.h"
vector<vector<double>> Reverb::convReverb(vector<vector<double>>& samples, const vector<vector<double>> & irSamples)
{
    if (samples.size() == 0 || irSamples.size() == 0) {
        throw "Must have at least one channel of audio";
    }
    int numChannels = samples.size();
    vector<thread> threads;
    vector<vector<double>> output(numChannels, vector<double>(samples[0].size(), 0.0));

    vector<int> sizes(numChannels);
    for (int chan = 0; chan < numChannels; chan++)
    {
        sizes[chan] = samples[chan].size();
        threads.emplace_back(Utils::convolve, ref(samples[chan]), irSamples[0]);
    }

    for (thread &t : threads)
    {
        t.join();
    }

    for (int chan = 0; chan < numChannels; chan++)
    {
        samples[chan].resize(sizes[chan]);
    }

    Utils::normalize(samples);
    FFT::destroyPlan();
    return samples;
    
}
