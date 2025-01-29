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
    static SNDFILE *inFile;
    static SNDFILE *outFile;
    static double *buffer;

public:
    /**
     * @param fn -> file path to an audio sample
     * @param info -> metadata of audio file
     *
     * Attempt to open audio file. If successful, fill vector with audio samples
     */
    static vector<vector<double>> open(const char *fn, SF_INFO &info);


    /**
     * @param output -> vector filled with audio samples
     *
     * Write data from output to an output file
     */
    static void write(vector<vector<double>> output, SF_INFO& info);
};
#endif