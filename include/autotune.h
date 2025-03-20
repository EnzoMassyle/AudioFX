#ifndef AUTOTUNE_H
#define AUTOTUNE_H
#include <map>
#include <vector>
#include <thread>
#include "utils.h"
#include "params.h"
#include "fft.h"
#include "tempo.h"
using namespace std;


/**
 * @class Autotune
 * @brief Autotune music effect
 * 
 */
class Autotune
{
private:
    vector<double> scaleNotes;
    static map<char, vector<int>> intervals;
    static map<string, double> rootNotes;
    int sampleRate;


    /**
     * @brief Analyze frequencies of the audio slice and tune it to the nearest correct note
     * @param slice -> Chunk of an audio sample
     * @param start -> start of output
     * @param out -> vector to store output 
     * 
     */
    void tuneSlice(vector<double> slice, int start, vector<double>& out);


    /**
     * @brief Perform autotune algorithm to a singular channel of audio
     * @param channel -> a single channel of audio
     * @param out -> vector to store output
     * 
     */
    void tuneChannel(const vector<double>& channel, vector<double>&out);

    /**
     * @brief For a given frequency, find the closest note for the given scale and calculate the shifting factor
     * @param f -> frequency
     *
     * @returns shifting factor
     */
    double findShiftingFactor(double f);


public:
    double intensity;
    string note;
    char scale; // Major (M) or minor (m)

    /**
     * @param intensity -> Determines how strong to apply the autotune effect
     * @param note -> The musical note to use as the root note
     * @param scale -> Category of semitones (major or minor)
     */
    Autotune(double intensity, string note, char scale);

    /**
     * @brief Use overlapping window approach to tune each audio frame to the nearest correct pitch on the provided musical scale
     * @param samples -> Audio samples separated by channel
     * @param sampleRate -> sample rate
     * 
     * @returns Modified audio
     **/
    vector<vector<double>> process(const vector<vector<double>>& samples, int sampleRate);

    /**
     * @brief  note table depending on the musical scale used
     */
    void fillNoteTable();
};

#endif
