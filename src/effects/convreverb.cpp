#include "convreverb.h"
unordered_map<string, string> Reverb::types = {
    {"CHURCH", string(ASSET) + "/ir/church.wav"},
    {"CAVE", string(ASSET) + "/ir/cave.wav"},
    {"AIRY", string(ASSET) + "/ir/airy.wav"}};

vector<vector<double>> Reverb::convReverb(vector<vector<double>>& samples, string room)
{
    if (Reverb::types.find(room) == Reverb::types.end())
    {
        cout << room << " is not a valid type" << endl;
    }
    int numChannels = samples.size();
    SF_INFO irInfo;
    

    FileHandler fh = FileHandler();
    vector<double> irSamples = fh.open(types.at(room).c_str())[0];
    vector<thread> threads;
    vector<vector<double>> output(numChannels, vector<double>(samples[0].size(), 0.0));

    vector<int> sizes(numChannels);
    for (int chan = 0; chan < numChannels; chan++)
    {
        sizes[chan] = samples[chan].size();
        threads.emplace_back(Utils::convolve, ref(samples[chan]), irSamples);
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
