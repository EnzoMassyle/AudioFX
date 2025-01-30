#ifndef AUTOTUNE_H
#define AUTOTUNE_H
#include <iostream>
#include <map>
#include <vector>
#include <sndfile.h>
#include <thread>
#include <filehandler.h>
#include <utils.h>
#include <params.h>
#include <fft.h>
#include <random>
#include <semaphore.h>
#include <future>
using namespace std;
class Autotune
{
private:
    inline static vector<double> scaleNotes;
    static map<char, array<int, 7>> intervals;
    static map<string, double> rootNotes;


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
    void tuneChannel(vector<double> channel, vector<double>&out);

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
    int sampleRate;

    /**
     * @param intensity -> Determines how strong to apply the autotune effect
     * @param note -> The musical note to use as the root note
     * @param scale -> Category of semitones (major or minor)
     */
    Autotune(double intensity, string note, char scale);

    /**
     * @param fn -> Audio file name
     *
     * Load file and analyze samples, Perform an overlap-add method where audio is broken up into slices. The signal is split up
     * into overlapping frames, where each one is individually processed and summed together
     */
    void process(const char *);

    /**
     * Fill note table depending on the musical scale used
     */
    void fillNoteTable();
};

#endif
