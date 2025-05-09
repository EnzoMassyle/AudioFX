#ifndef REVERB_H
#define REVERB_H

#include <iostream>
#include <vector>
#include <thread>
#include <filesystem>
#include <string>
#include <unordered_map>
#include "eq.h"
#include "filehandler.h"
#include "utils.h"


/**
 * @class Reverb
 * @brief Convolutional reverb music effect
 * 
 */
class Reverb
{
public:

    /**
     * @brief Perform fast-convolution with FFT between audio samples and an impulse response
     * @param samples -> audio samples separated by channel
     * @param room -> room type to emulate reverberation
     * 
     * @returns Modified audio samples
     */
    static vector<vector<double>> convReverb(vector<vector<double>>& samples, const vector<vector<double>>& irSamples);
};

#endif