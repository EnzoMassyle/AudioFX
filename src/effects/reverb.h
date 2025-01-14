#ifndef REVERB_H
#define REVERB_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include "filehandler.h"
#include "utils.h"
#include <thread>
#include <future>

class Reverb
{
private:
    inline static unordered_map<string, string> types = {
        {"CHURCH", "church.wav"},
        {"CAVE", "cave.wav"},
        {"AIRY", "airy.wav"}};

public:
    static void convReverb(const char *fn, string t = "CHURCH")
    {
        if (types.find(t) == types.end())
        {
            cout << t << " is not a valid type" << endl;
            throw;
        }
        SF_INFO fnInfo;
        SF_INFO irInfo;
        vector<vector<double>> samples = FileHandler::open(fn, fnInfo);
        string outFile = "../samples/ir/" + types.at(t);
        vector<double> irSamples = FileHandler::open(outFile.c_str(), irInfo)[0];
        vector<thread> threads;
        int sizes[fnInfo.channels];
        for (int chan = 0; chan < fnInfo.channels; chan++)
        {
            sizes[chan] = samples[chan].size();
            threads.emplace_back(Utils::convolve, ref(samples[chan]), irSamples);
        }

        for (thread &t : threads)
        {
            t.join();
        }

        for (int chan = 0; chan < fnInfo.channels; chan++)
        {
            samples[chan].resize(sizes[chan]);
        }

        Utils::normalize(samples);
        FileHandler::write(samples, fnInfo);
    }
};

#endif