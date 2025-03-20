#ifndef TIMESTRETCH_H
#define TIMESTRETCH_H

#include <vector>
#include <cassert>
#include "utils.h"
#include "params.h"

using namespace std;
/**
 * @class TimeStretch
 * @brief Class to stretch/compress an audio file without changing the pitch
 * 
 */
class TimeStretch
{
private:

    /**
     * @brief Stretch/compress a singular frame of audio
     * @param frame -> frame of audio samples
     * @param shiftedStart -> new start to audio grain
     * @param shiftFactor -> amount to stretch/compress audio
     * @param out -> modified audio
     *
     */
    static void stretchFrame(const vector<double> &frame, int shiftedStart, double shiftFactor, vector<double> &out);

public:
    /**
     * @brief Use phase vocoder to stretch/compress audio samples
     * @param channel -> channel of audio samples
     * @param shiftFactor -> amount to stretch/compress audio
     * @param out -> modified audio
     *
     */
    static void stretchChannel(const vector<double> &channel, double shiftFactor, vector<double> &out);

    /**
     * @brief Perform time stretching algorithm on each channel independently
     * @param fn -> path to a audio file
     * @param shiftFactor -> Amount to stretch/compress audio
     *
     * @returns Modified audio
     */
    static vector<vector<double>> changeSpeed(const vector<vector<double>>& samples, double shiftFactor);

};

#endif