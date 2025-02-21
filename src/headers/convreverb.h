#ifndef REVERB_H
#define REVERB_H

#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <filters/lp.h>
#include <filehandler.h>
#include <utils.h>
class Reverb
{
private:
    static unordered_map<string, string> types;

public:

    /**
     * @param samples -> audio samples separated by channel
     * @param room -> room type to emulate reverberation
     * 
     * Perform fast-convolution with FFT between audio samples and an impulse response
     */
    static vector<vector<double>> convReverb(vector<vector<double>> samples, string room);
};

#endif