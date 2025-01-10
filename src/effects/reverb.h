#ifndef REVERB_H
#define REVERB_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include "filehandler.h"
#include "utils.h"

class Reverb
{
private:
    inline static unordered_map<string, string> types = {
        {"CHURCH", "church.wav"},
        {"CAVE", "church.wav"},
        {"AIRY", "airy.wav"}};

public:
    static void apply(const char *fn, string t = "CHURCH")
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

        for (int chan = 0; chan < fnInfo.channels; chan++)
        {
            int n = samples[chan].size();
            samples[chan] = Utils::convolve(samples[chan], irSamples);
            samples[chan].resize(n);
        }
        
        Utils::normalize(samples);
        Utils::gain(samples, 1.35);
        FileHandler::write(samples, fnInfo);
    }
};

#endif