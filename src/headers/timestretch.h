#ifndef TIMESTRETCH_H
#define TIMESTRETCH_H

#include <iostream>
#include <vector>
#include <cassert>
#include <utils.h>
#include <params.h>

using namespace std;
class TimeStretch
{
private:
    /**
     * @param channel -> channel of audio samples
     * @param shiftFactor -> amount to stretch/compress audio
     * @param out -> modified audio
     *
     * Use phase vocoder to stretch/compress audio samples
     */
    static void stretchChannel(const vector<double> &channel, double shiftFactor, vector<double> &out);

    /**
     * @param frame -> frame of audio samples
     * @param shiftedStart -> new start to audio grain
     * @param shiftFactor -> amount to stretch/compress audio
     * @param out -> modified audio
     *
     * Stretch/compress a singular frame of audio
     */
    static void stretchFrame(const vector<double> &frame, int shiftedStart, double shiftFactor, vector<double> &out);

public:
    /**
     * @param fn -> path to a audio file
     * @param shiftFactor -> Amount to stretch/compress audio
     *
     * Perform time stretching algorithm on each channel independently
     */
    static vector<vector<double>> changeSpeed(const vector<vector<double>> &samples, double shiftFactor);
};

#endif