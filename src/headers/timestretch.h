#ifndef TIMESTRETCH_H
#define TIMESTRETCH_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include <filehandler.h>
#include <utils.h>
#include <params.h>
#include <random>


using namespace std;
class TimeStretch
{
private:
    /**
     * @param samples -> audio samples
     * @param shiftFactor -> amount to stretch/compress audio
     * @param out -> modified audio
     *
     * Use granular synthesis to increase/decrease the space between grains
     */
    static void stretchChannel(const vector<double>& samples, double shiftFactor, vector<double> &out);

    /**
     * @param grain -> audio grain
     * @param shiftedStart -> new start to audio grain
     * @param out -> modified audio
     *
     * shift grain to start at the position indicated by shiftedStart
     */
    static void stretchFrame(const vector<double>& channel, int shiftedStart, double shiftFactor, vector<double> &out);
public:
    /**
     * @param fn -> path to a audio file
     * @param shiftFactor -> Amount to stretch/compress audio
     *
     * Perform time stretching algorithm on each channel independently
     */
    static vector<vector<double>> changeSpeed(vector<vector<double>> samples, double shiftFactor);
};

#endif