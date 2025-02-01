#ifndef PITCHSHIFT_H
#define PITCHSHIFT_H

#include <iostream>
#include <vector>
#include <sndfile.h>
#include <filehandler.h>
#include <utils.h>
#include <random>

using namespace std;
class PitchShift
{
private:

    /**
     * @param samples -> audio samples
     * @param pitchFactor -> Amount to shift pitch up or down
     * @param out -> pitch shifted output
     *
     * Perform granular synthesis with the overlap add method to resample each grain.
     * Use multithreading since we can process the grains independently
     */
    static void shiftChannel(vector<double> channel, double pitchFactor, vector<double> &out);
    
    /**
     * @param samples -> audio samples
     * @param pitchFactor -> pitch factor tells us how much to change the pitch up or down
     *
     * resample the audio chunk by performing linear interpolation
     */
    static void resampleGrain(vector<double> samples, int start, double pitchFactor, vector<double> &out);
public:
    /**
     * @param fn -> file path
     * @param pitchFactor -> pitch factor tells us how much to change the pitch up or down
     *
     * Change the pitch of a audio file according to pitch factor using granular synthesis
     * (breaking up audio into chunks and resampling each chunk)
     */
    static vector<vector<double>> changePitch(vector<vector<double>> samples, double pitchFactor);
};

#endif