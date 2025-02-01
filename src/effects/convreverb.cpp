#include <../headers/convreverb.h>


unordered_map<string, string> Reverb::types = {
        {"CHURCH", "church.wav"},
        {"CAVE", "cave.wav"},
        {"AIRY", "airy.wav"}};

vector<vector<double>> Reverb::convReverb(vector<vector<double>> samples, string room)
    {
        if (Reverb::types.find(room) == Reverb::types.end())
        {
            cout << room << " is not a valid type" << endl;
        }
        int numChannels = samples.size();
        SF_INFO irInfo;
        string outFile = "../samples/ir/" + Reverb::types.at(room);

        FileHandler fh = FileHandler();
        vector<double> irSamples = fh.open(outFile.c_str())[0];
        vector<thread> threads;
        int sizes[numChannels];
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
        return samples;
    }