#ifndef TIMESHIFT_H
#define TIMESHIFT_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include "filehandler.h"
#include "utils.h"
#include "vocoder.h"

using namespace std;
class TimeShift
{
public:
    static void changeSpeed(const char *fn, double shiftFactor)
    {
        SF_INFO info;
        vector<vector<double>> samples = FileHandler::open(fn, info);
        // info.samplerate = 44100;
        // FileHandler::write(samples, info);
        vector<vector<double>> output(info.channels, vector<double>(samples[0].size() * shiftFactor, 0.0));

        int chunkSize = 16384;
        int numOverlap = 3;
        int step = chunkSize / 3;
        vector<double> window = Utils::generateWindow(chunkSize);
        for (int chan = 0; chan < info.channels; chan++)
        {
            for (int start = 0, end = chunkSize; end < samples[chan].size(); start += step, end += step)
            {
                int shiftedStart = start * shiftFactor;
                int shiftedEnd = shiftedStart + end;
                vector<double> audioSlice(samples[chan].begin() + start, samples[chan].begin() + end);
                for (int i = 0; i < chunkSize; i++)
                {
                    audioSlice[i] *= window[i];
                }
                vector<double> shiftedSlice = Vocoder::timeShift(audioSlice, shiftFactor, info.samplerate, start == 0);
                for (int i = 0; i < chunkSize; i++)
                {
                    if (i + shiftedStart < output[chan].size()) {
                        output[chan][i + shiftedStart] += audioSlice[i] / numOverlap;
                    }
                }
            }
        }
        Utils::normalize(output);
        FileHandler::write(output, info);
    }
};

#endif