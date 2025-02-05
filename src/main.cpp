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
    // samples = afx.pitchShift(samples, 0.9);
    // samples = afx.timeStretch(samples, 1.15);

    // samples = afx.artificialReverb(samples);
    samples = afx.changeTempo(samples, 0.9);
    samples = afx.convReverb(samples, "CAVE");

    
    auto end = std::chrono::high_resolution_clock::now(); // End timing

    std::chrono::duration<double> elapsed = end - start; // Compute elapsed time

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";


    fh.write(samples);

}
