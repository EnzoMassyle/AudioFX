#ifndef PITCHSHIFT_H
#define PITCHSHIFT_H

#include<iostream>
#include<vector>
#include<sndfile.h>
#include "filehandler.h"
#include "utils.h"

using namespace std;
class PitchShift {
  public: 
    static void changePitch(const char* fn, double pitchFactor) {
        SF_INFO info;
        vector<vector<double>> samples = FileHandler::open(fn, info);
        vector<vector<double>> output(info.channels, vector<double>(samples[0].size(), 0.0));

        int chunkSize = 8192;
        int numOverlap = 4;
        int step = chunkSize / numOverlap;
        vector<double> window = Utils::generateWindow(chunkSize);
        for (int chan = 0; chan < info.channels; chan++)
        {
            for (int start = 0, end = chunkSize; end < samples[chan].size(); start += step, end += step)
            {
                vector<double> audioSlice(samples[chan].begin() + start, samples[chan].begin() + end);
                for (int i = 0; i < chunkSize; i++)
                {
                    audioSlice[i] *= window[i];
                }
                vector<double> resampledGrain = resampleGrain(audioSlice, pitchFactor);
                for (int i = 0; i < chunkSize; i++) {
    
                    output[chan][i + start] += resampledGrain[i] / numOverlap;
                }
            }
        }
        Utils::normalize(output);
        FileHandler::write(output);
    }

    static vector<double> resampleGrain(vector<double> samples, double pitchFactor) {
        samples.push_back(samples[0]);
        vector<double> resampled(samples.size() / pitchFactor);
        for (int i = 0; i < resampled.size(); i++) {
            double exact = i * pitchFactor;
            int idx = (int) exact;
            double frac = exact - idx;
            double a = 1 - (exact - idx);
            resampled[i] = a*samples[idx] + (1-a)*samples[idx+1];
        }
        return resampled;
    }
};

#endif