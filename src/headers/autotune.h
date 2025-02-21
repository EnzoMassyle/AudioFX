#ifndef AUTOTUNE_H
#define AUTOTUNE_H
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <utils.h>
#include <params.h>
#include <fft.h>
#include <random>
using namespace std;
class Autotune
{
private:
    vector<double> scaleNotes;
    static map<char, array<int, 7>> intervals;
    static map<string, double> rootNotes;
    int sampleRate;


    /**
     * @param slice -> Chunk of an audio sample
     * @param start -> start of output
     * @param out -> vector to store output 
     * 
     * Analyze frequencies of the audio slice and tune it to the nearest correct note
     */
    void tuneSlice(vector<double> slice, int start, vector<double>& out);


    /**
     * @param channel -> a single channel of audio
     * @param out -> vector to store output
     * 
     * Perform autotune algorithm to a singular channel of audio
     */
    void tuneChannel(const vector<double>& channel, vector<double>&out);

    /**
     * @param f -> frequency
     *
     * For a given frequency, find the closest note for the given scale and calculate the shifting factor
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
     * @param samples -> Audio samples separated by channel
     * @param sampleRate -> sample rate
     * Use granular synthesis approach to tune each audio grain to the nearest correct pitch on the provided musical scale
     */
    vector<vector<double>> process(const vector<vector<double>>& samples, int sampleRate);

    /**
     * Fill note table depending on the musical scale used
     */
    void fillNoteTable();
};

#endif
