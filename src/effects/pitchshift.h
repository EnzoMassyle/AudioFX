#ifndef PITCHSHIFT_H
#define PITCHSHIFT_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include "filehandler.h"
#include "utils.h"

using namespace std;
class PitchShift
{
public:
    /**
     * @param fn -> file path
     * @param pitchFactor -> pitch factor tells us how much to change the pitch up or down
     *
     * Change the pitch of a audio file according to pitch factor using granular synthesis (breaking up audio into chunks and resampling each chunk)
     */
    static void changePitch(const char *fn, double pitchFactor)
    {
        SF_INFO info;
        vector<vector<double>> samples = FileHandler::open(fn, info);
        vector<vector<double>> output(info.channels, vector<double>(samples[0].size(), 0.0));

        int chunkSize = 4096;
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
                for (int i = 0; i < chunkSize; i++)
                {

                    output[chan][i + start] += resampledGrain[i] / numOverlap;
                }
            }
        }
        Utils::normalize(output);
        FileHandler::write(output, info);
    }

    /**
     * @param samples -> audio samples
     * @param pitchFactor -> pitch factor tells us how much to change the pitch up or down
     *
     * resample the audio chunk by performing linear interpolation
     */

    static vector<double> resampleGrain(vector<double> samples, double pitchFactor)
    {
        samples.push_back(samples[0]);
        vector<double> resampled(samples.size() / pitchFactor, 0.0);
        for (int i = 0; i < resampled.size(); i++)
        {
            double exact = i * pitchFactor;
            int idx = (int)exact;
            double frac = exact - idx;
            double alpha = 1 - (exact - idx);
            resampled[i] += alpha * samples[idx] + (1 - alpha) * samples[idx + 1];
        }
        return resampled;
    }
};

#endif