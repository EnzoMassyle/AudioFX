#ifndef TEMPO_H
#define TEMPO_H

#include <vector>
#include <utils.h>
#include <thread>
#include <cassert>
class Tempo
{
private:
    /**
     * @param channel -> singular channel of audio samples
     * @param frameStart -> starting index for frame
     * @param frameSize -> size of frame
     * @param r -> resampling factor
     * @param output -> resampled audio
     * 
     * Resample a single frame of audio from channel starting at frameStart and is frameSize in length 
     */
    static void changeTempoFrame(const vector<double>& channel, int frameStart, int frameSize, double r, vector<double> &out);

    /**
     * @param channel -> singular channel of audio samples
     * @param r -> resampling factor
     * @param out -> resampled audio
     * 
     * resample a single channel of audio
     */
    static void changeTempoChannel(const vector<double>& channel, double r, vector<double> &out);
public:
    /**
     * @param samples -> vector of audio samples separated by channel
     * @param r -> resampling factor
     * 
     * resample audio samples based on r
     */
    static vector<vector<double>> changeTempo(const vector<vector<double>>& samples, double r);
};

#endif