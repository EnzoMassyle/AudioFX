#ifndef TIMESHIFT_H
#define TIMESHIFT_H

#include<iostream>
#include<vector>
#include<sndfile.h>
#include "filehandler.h"
#include "utils.h"

using namespace std;
class TimeShift {
  public: 
    static void changeSpeed(const char* fn, double shiftFactor) {
        SF_INFO info;
        vector<vector<double>> samples = FileHandler::open(fn, info);
        vector<vector<double>> output(info.channels, vector<double>(samples[0].size() * shiftFactor, 0.0));

        int chunkSize = 4096;
        int numOverlap = 4;
        int step = chunkSize / numOverlap;
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
                for (int i = 0; i < chunkSize; i++) {
                    output[chan][i + shiftedStart] += audioSlice[i] / numOverlap;
                }
            }
        }
        Utils::normalize(output);
        FileHandler::write(output);
    }
};

#endif