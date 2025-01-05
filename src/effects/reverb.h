#ifndef REVERB_H
#define REVERB_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include "filehandler.h"
#include "utils.h"
#include "../../FFT/kiss_fft.h"

class Reverb
{
private:
    // enum TYPES = {};
public:
    static void apply(const char *fn)
    {
        SF_INFO fnInfo;
        SF_INFO irInfo;
        vector<vector<double>> samples = FileHandler::open(fn, fnInfo);
        vector<double> irSamples = FileHandler::open("../samples/ir.wav", irInfo)[0];

        for (int chan = 0; chan < fnInfo.channels; chan++)
        {
            int n = samples[chan].size();
            samples[chan] = Utils::convolve(samples[chan], irSamples);
            samples[chan].resize(n);
        }

        Utils::normalize(samples);
        FileHandler::write(samples, fnInfo);
    }
};

#endif