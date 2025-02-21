#include <iostream>
#include "headers/afx.h"   
#include "headers/filehandler.h"
#include <chrono>
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
    samples = afx.pitchShift(samples, 5);
    // samples = afx.reverse(samples);
    // samples = afx.timeStretch(samples, 0.8);
    // samples = afx.autotune(samples, 1.0, "C", 'M', fh.getSampleRate());
    // samples = afx.artificialReverb(samples);
    // samples = afx.changeTempo(samples, 1.3);
    // samples = afx.convReverb(samples, "CHURCH");
    // samples = afx.demix(samples, 1);
    
    auto end = std::chrono::high_resolution_clock::now(); // End timing

    std::chrono::duration<double> elapsed = end - start; // Compute elapsed time

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    fh.write(samples);

}
