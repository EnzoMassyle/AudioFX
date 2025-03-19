#include "../../include/filehandler.h"


AudioFile::AudioFile(vector<vector<double>> samples, SF_INFO info, SNDFILE* f)
{
    this->samples = samples;
    this->info = info;
    this->file = f;
    
}

AudioFile::~AudioFile()
{
    sf_close(this->file);
}

FileHandler::FileHandler()
{
    buffer = (double *)malloc(BUFFER_LEN * sizeof(double));
}

FileHandler::~FileHandler()
{
    free(buffer);
}

AudioFile FileHandler::open(const char* fn)
{
    const char *inFileName = fn;
    SF_INFO info;
    memset(&info, 0, sizeof(info));
    SNDFILE* inFile;
    try
    {
        if (!(inFile = sf_open(inFileName, SFM_READ, &info)))
        {   
            cout << inFileName << " not found" << endl;
            throw inFileName;
        }
    }
    catch (string &fn)
    {
        cout << fn << " not found" << endl;
    }
    vector<vector<double>> samples(info.channels);
    int readcount;
    while ((readcount = (int)sf_read_double(inFile, buffer, BUFFER_LEN)))
    {
        for (int chan = 0; chan < info.channels; chan++)
        {
            for (int k = chan; k < BUFFER_LEN; k += info.channels)
            {
                samples[chan].push_back(buffer[k]);
            }
        }
    }


    AudioFile af = AudioFile(samples, info, inFile);
    return af;
}

void FileHandler::write(AudioFile af, const char* writeName)
 {
    SNDFILE* outFile;
    if (!(outFile = sf_open(writeName, SFM_WRITE, &af.info)))
        {
            throw writeName;
        }
    int idx = 0;
    for (int i = 0; i < af.samples[0].size(); i++)
    {
        for (int chan = 0; chan < af.samples.size(); chan++)
        {
            buffer[idx++] = af.samples[chan][i];
            if (idx == BUFFER_LEN)
            {
                sf_write_double(outFile, buffer, BUFFER_LEN);
                idx = 0;
            }
        }
    }

    sf_close(outFile);
}
