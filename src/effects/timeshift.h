#ifndef TIMESHIFT_H
#define TIMESHIFT_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include "filehandler.h"
#include "utils.h"
#include "params.h"

using namespace std;
class TimeShift
{
public:
    /**
     * @param fn -> path to a audio file
     * @param shiftFactor -> Amount to stretch/compress audio
     *
     * Perform time stretching algorithm on each channel independently
     */
    static void changeSpeed(const char *fn, double shiftFactor)
    {
        SF_INFO info;
        vector<vector<double>> samples = FileHandler::open(fn, info);
        vector<vector<double>> output(info.channels, vector<double>(samples[0].size() * shiftFactor, 0.0));
        vector<thread> threads;

        for (int chan = 0; chan < info.channels; chan++)
        {
            threads.emplace_back(stretchChannel, samples[chan], shiftFactor, ref(output[chan]));
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
     * @param shiftFactor -> amount to stretch/compress audio
     * @param out -> modified audio
     *
     * Use granular synthesis to increase/decrease the space between grains
     */
    static void stretchChannel(vector<double> samples, double shiftFactor, vector<double> &out)
    {
        int step = CHUNK_SIZE / NUM_OVERLAP;
        vector<thread> threads;
        for (int start = 0, end = CHUNK_SIZE; end < samples.size(); start += step, end += step)
        {
            int shiftedStart = start * shiftFactor;
            vector<double> audioSlice(samples.begin() + start, samples.begin() + end);
            threads.emplace_back(processSlice, audioSlice, shiftedStart, ref(out));
        }

        for (thread &t : threads)
        {
            t.join();
        }
    }

    /**
     * @param grain -> audio grain
     * @param shiftedStart -> new start to audio grain
     * @param out -> modified audio
     *
     * shift grain to start at the position indicated by shiftedStart
     */
    static void processSlice(vector<double> grain, int shiftedStart, vector<double> &out)
    {
        vector<double> window = Utils::generateWindow(CHUNK_SIZE);
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            grain[i] *= window[i];
        }
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            if (i + shiftedStart < out.size())
            {
                out[i + shiftedStart] += grain[i];
            }
        }
    }
};

#endif