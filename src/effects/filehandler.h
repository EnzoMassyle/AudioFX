#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <sndfile.h>
#include <vector>
#include <iostream>

using namespace std;
class FileHandler
{
private:
    inline static SNDFILE *inFile;
    inline static SNDFILE *outFile;
    inline static double *buffer;
    inline static const int bufferLen = 512;

public:
    /**
     * @param fn -> file path to an audio sample
     * @param info -> metadata of audio file
     *
     * Attempt to open audio file. If successful, fill vector with audio samples
     */
    static vector<double> open(const char *fn, SF_INFO &info)
    {
        const char *inFileName = fn;
        const char *outFileName = "out.wav";
        memset(&info, 0, sizeof(info));
        try
        {
            if (!(inFile = sf_open(inFileName, SFM_READ, &info)))
            {
                throw inFileName;
            }
            if (!(outFile = sf_open(outFileName, SFM_WRITE, &info)))
            {
                throw outFileName;
            }
        }
        catch (string &fn)
        {
            cout << fn << " not found" << endl;
        }
        buffer = (double *)malloc(bufferLen * sizeof(double));
        vector<double> samples;
        int readcount;

        while ((readcount = (int)sf_read_double(inFile, buffer, bufferLen)))
        {
            samples.insert(samples.end(), buffer, buffer + bufferLen);
        }
        cout << "Successfully read " << inFileName << endl;
        return samples;
    }

    /**
     * @param output -> vector filled with audio samples
     *
     * Write data from output to an output file
     */
    static void write(vector<double> output)
    {
        cout << "Saving..." << endl;
        for (int i = 0; i < output.size(); i += bufferLen)
        {
            int size = min((int)output.size() - i, bufferLen);
            copy(output.begin() + i, output.begin() + i + size, buffer);
            sf_write_double(outFile, buffer, bufferLen);
        }
        cout << "Done!" << endl;
        free(buffer);
        sf_close(inFile);
        sf_close(outFile);
    }
};
#endif