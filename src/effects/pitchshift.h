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
     * Change the pitch of a audio file according to pitch factor using granular synthesis
     * (breaking up audio into chunks and resampling each chunk)
     */
    static void changePitch(const char *fn, double pitchFactor)
    {
        SF_INFO info;
        vector<vector<double>> samples = FileHandler::open(fn, info);
        vector<vector<double>> output(info.channels, vector<double>(samples[0].size(), 0.0));
        vector<thread> threads;

        for (int chan = 0; chan < info.channels; chan++)
        {
            threads.emplace_back(shiftChannel, samples[chan], pitchFactor, ref(output[chan]));
        }

        for (thread &t : threads)
        {
            t.join();
        }

        Utils::normalize(output);
        FileHandler::write(output, info);
    }

    /**
     * @param samples -> audio samples
     * @param pitchFactor -> Amount to shift pitch up or down
     * @param out -> pitch shifted output
     *
     * Perform granular synthesis with the overlap add method to resample each grain.
     * Use multithreading since we can process the grains independently
     */
    static void shiftChannel(vector<double> samples, double pitchFactor, vector<double> &out)
    {
        int step = CHUNK_SIZE / NUM_OVERLAP;
        vector<thread> threads;
        for (int start = 0, end = CHUNK_SIZE; end < samples.size(); start += step, end += step)
        {
            vector<double> slice(samples.begin() + start, samples.begin() + end);
            threads.emplace_back(resampleGrain, slice, start, pitchFactor, ref(out));
        }

        for (thread &t : threads)
        {
            t.join();
        }
    }
    /**
     * @param samples -> audio samples
     * @param pitchFactor -> pitch factor tells us how much to change the pitch up or down
     *
     * resample the audio chunk by performing linear interpolation
     */

    static void resampleGrain(vector<double> samples, int start, double pitchFactor, vector<double> &out)
    {
        vector<double> window = Utils::generateWindow(samples.size());
        for (int i = 0; i < samples.size(); i++)
        {
            samples[i] *= window[i];
        }

        vector<double> resampled(samples.size(), 0.0);
        resampled.push_back(samples.back());
        for (int i = 0; i < samples.size(); i++)
        {
            double exact = i * pitchFactor;
            if (exact < samples.size()) {
                int idx = (int)exact;
                double frac = exact - idx;
                double alpha = 1 - (exact - idx);
                resampled[i] += alpha * samples[idx] + (1 - alpha) * samples[idx + 1];
            }
        }

        for (int i = 0; i < samples.size(); i++)
        {
            out[i + start] += resampled[i];
        }
    }
};

#endif