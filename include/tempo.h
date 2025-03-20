#ifndef TEMPO_H
#define TEMPO_H

#include <vector>
#include <thread>
#include <cassert>
#include "utils.h"
/**
 * @class Tempo
 * @brief Class for changing tempo of an audio file
 * 
 */
class Tempo
{
private:
    /**
     * @brief Resample a single frame of audio from channel starting at frameStart and is frameSize in length 
     * @param channel -> singular channel of audio samples
     * @param frameStart -> starting index for frame
     * @param frameSize -> size of frame
     * @param r -> resampling factor
     * @param output -> resampled audio
     */
    static void changeTempoFrame(const vector<double>& channel, int frameStart, int frameSize, double r, vector<double> &out);
    /**
     * @brief resample a single channel of audio
     * @param channel -> singular channel of audio samples
     * @param r -> resampling factor
     * @param out -> resampled audio
     */
    static void changeTempoChannel(const vector<double>& channel, double r, vector<double> &out);

    
public:

/**
     * @brief resample audio samples based on r
     * @param samples -> audio samples separated by channel
     * @param r -> resampling factor
     * 
     * @returns Modified audio
     */

    static vector<vector<double>> changeTempo(const vector<vector<double>>& samples, double r);

    /**
     * @brief resample audio samples based on r
     * @param samples -> singular channel of audio
     * @param r -> resampling factor
     * 
     * @returns Modified audio
     * 
     */
    static vector<double> changeTempo(const vector<double>& samples, double r);


};

#endif