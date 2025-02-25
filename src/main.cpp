#include <iostream>
#include "headers/afx.h"   
#include "headers/filehandler.h"
#include <chrono>
#include <headers/filters/ls.h>
#include <headers/filters/hs.h>
#include <headers/filters/bell.h>
#include <headers/filters/lp.h>
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cout << "Please provide one file to process! " << endl;
        return 0;
    }
    auto start = std::chrono::high_resolution_clock::now();
    char parentFolder[128] = "../samples/";
    char *fn = strcat(parentFolder, argv[1]);

    FileHandler fh = FileHandler();
    vector<vector<double>> samples = fh.open(fn);


    AFX afx = AFX();
    samples = afx.changeTempo(samples, 0.9);
    samples = afx.convReverb(samples);
    // samples = afx.pitchShift(samples, 5);
    // samples = afx.reverse(samples);
    // samples = afx.timeStretch(samples, 0.8);
    // samples = afx.autotune(samples, 1.0, "C", 'M', fh.getSampleRate());
    // samples = afx.artificialReverb(samples);
    // samples = afx.changeTempo(samples, 1.3);
    // samples = afx.convReverb(samples, "CHURCH");
    // samples = afx.demix(samples, 1);
    // samples = afx.layer(samples, 0.2, 0.5);
    // samples = afx.layer(samples, -0.2, 0.5);
    // samples = afx.layer(samples, -12, 0.1);
    LowShelf ls = LowShelf(1.2, 100, fh.getSampleRate());
    LowPass lp = LowPass(0.9);
    
    ls.process(samples);
    lp.process(samples);
    // HighShelf hs = HighShelf(3.0 ,5000, fh.getSampleRate());
    // hs.process(samples);
    // vector<vector<double>> impulse;
    // impulse.push_back(vector<double>{1,2,3,4});
    // BellFilter bell = BellFilter(2.0, 10000, fh.getSampleRate(), 1.0);
    // BellFilter bell2 = BellFilter(2.0, 50, fh.getSampleRate(), 1.0);
    // bell.process(samples);
    // bell2.process(samples);

    // for (int i = 0; i < impulse[0].size(); i++)
    // {
    //     cout << impulse[0][i] << " ";
    // }
    
    auto end = std::chrono::high_resolution_clock::now(); // End timing

    std::chrono::duration<double> elapsed = end - start; // Compute elapsed time

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    fh.write(samples);

}
