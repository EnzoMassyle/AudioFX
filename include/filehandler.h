#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <sndfile.h>
#include <vector>
#include <cstring>
#include <map>
#include "params.h"

using namespace std;

/**
 * @class AudioFile
 * @brief Data structure after opening a file through the FileHandler class
 * 
 */
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

/** @} */  // End of AudioFile documentation group

/**
 * @class FileHandler
 * @brief Handle sound file operations
 * 
 */class FileHandler
{
private:
    double *buffer;
    map<const char*, SNDFILE*> files;

public:
    FileHandler();
    ~FileHandler();
    /**
     * @brief Attempt to open audio file. If successful, fill vector with audio samples
     * @param fn -> file path to an audio sample
     * @param info -> metadata of audio file
     */
    AudioFile open(const char *fn);

    /**
     * @brief Write data from output to an output file
     * @param output -> vector filled with audio samples
     */
    void write(AudioFile af, const char *writeName = "out.wav");

};
#endif