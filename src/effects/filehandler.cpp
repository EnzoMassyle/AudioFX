#include <../headers/filehandler.h>

SNDFILE *FileHandler::inFile;
SNDFILE *FileHandler::outFile;
double *FileHandler::buffer;
vector<vector<double>> FileHandler::open(const char *fn, SF_INFO &info)
{
    const char *inFileName = fn;
    memset(&info, 0, sizeof(info));
    try
    {
        if (!(FileHandler::inFile = sf_open(inFileName, SFM_READ, &info)))
        {   
            cout << inFileName << " not found" << endl;
            throw inFileName;
        }
    }
    catch (string &fn)
    {
        cout << fn << " not found" << endl;
    }
    buffer = (double *)malloc(BUFFER_LEN * sizeof(double));
    vector<vector<double>> samples(info.channels);
    int readcount;
    while ((readcount = (int)sf_read_double(FileHandler::inFile, buffer, BUFFER_LEN)))
    {
        for (int chan = 0; chan < info.channels; chan++)
        {
            for (int k = chan; k < BUFFER_LEN; k += info.channels)
            {
                samples[chan].push_back(buffer[k]);
            }
        }
    }
    cout << "Successfully read " << inFileName << endl;
    return samples;
}

void FileHandler::write(vector<vector<double>> output, SF_INFO& info)
 {
    const char *outFileName = "out.wav";
    if (!(FileHandler::outFile = sf_open(outFileName, SFM_WRITE, &info)))
        {
            throw outFileName;
        }
    cout << "Saving..." << endl;
    int idx = 0;
    for (int i = 0; i < output[0].size(); i++)
    {
        for (int chan = 0; chan < output.size(); chan++)
        {
            buffer[idx++] = output[chan][i];
            if (idx == BUFFER_LEN)
            {
                sf_write_double(FileHandler::outFile, buffer, BUFFER_LEN);
                idx = 0;
            }
        }
    }
    cout << "Done!" << endl;
    free(buffer);
    sf_close(FileHandler::inFile);
    sf_close(FileHandler::outFile);
}