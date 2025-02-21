#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <sndfile.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <params.h>

using namespace std;
class FileHandler
{
private:
    SNDFILE *inFile;
    SNDFILE *outFile;
    double *buffer;
    SF_INFO info;

public:
    FileHandler();
    ~FileHandler();
    /**
     * @param fn -> file path to an audio sample
     * @param info -> metadata of audio file
     *
     * Attempt to open audio file. If successful, fill vector with audio samples
     */
    vector<vector<double>> open(const char *fn);

    /**
     * @param output -> vector filled with audio samples
     *
     * Write data from output to an output file
     */
    void write(const vector<vector<double>> &output, const char *writeName = "out.wav");

    int getSampleRate() { return info.samplerate; }

    int getNumChannels() { return info.channels; }
};
#endif