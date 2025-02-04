#include <iostream>
#include "headers/afx.h"   
#include "headers/filehandler.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Please provide one file to process! " << endl;
        return 0;
    }
    char parentFolder[128] = "../samples/";
    char *fn = strcat(parentFolder, argv[1]);

    FileHandler fh = FileHandler();
    vector<vector<double>> samples = fh.open(fn);


    AFX afx = AFX();
    // samples = afx.pitchShift(samples, 0.9);
    // samples = afx.timeStretch(samples, 1.15);

    // samples = afx.artificialReverb(samples);
    samples = afx.convReverb(samples, "CHURCH");
    samples = afx.changeTempo(samples, 0.9, fh.getSampleRate());
    


    fh.write(samples);

}
