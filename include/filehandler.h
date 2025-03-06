#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <sndfile.h>
#include <vector>
#include <cstring>
#include <map>
#include "params.h"

using namespace std;

class AudioFile
{
    public:
        vector<vector<double>> samples;
        SF_INFO info;
        SNDFILE* file;
        AudioFile(vector<vector<double>> samples, SF_INFO info, SNDFILE* f);

        /* Close file */
        ~AudioFile();
};
class FileHandler
{
private:
    double *buffer;
    map<const char*, SNDFILE*> files;

public:
    FileHandler();
    ~FileHandler();
    /**
     * @param fn -> file path to an audio sample
     * @param info -> metadata of audio file
     *
     * Attempt to open audio file. If successful, fill vector with audio samples
     */
    AudioFile open(const char *fn);

    /**
     * @param output -> vector filled with audio samples
     *
     * Write data from output to an output file
     */
    void write(AudioFile af, const char *writeName = "out.wav");

};
#endif