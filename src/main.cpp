#include <iostream>
#include "afx.h"   
#include <chrono>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Please provide one file to process! " << endl;
        return 0;
    }
    cout << "asset dir: " << string(ASSET) << endl;
    auto start = std::chrono::high_resolution_clock::now();
    // char parentFolder[128] = "../samples/";
    // char *fn = strcat(parentFolder, argv[1]);

    FileHandler fh = FileHandler();
    vector<vector<double>> samples = fh.open(argv[1]);

    AFX afx = AFX();

    /* Perform sound transformations here */
    // samples = afx.layer(samples, -0.5, 0.5);
    // samples = afx.layer(samples, 0.5, 0.5);
    // samples = afx.layer(samples, 1, 0.15);
    // samples = afx.layer(samples, -1, 0.15);
    samples = afx.convReverb(samples, "AIRY");
    //hello 
    // samples = afx.pitchShift(samples, 2);

    // EQ eq = afx.createEQ();
    // eq.setBell2(1.3);
    // eq.setHighPass(100);
    // eq.setBell3(1.2);
    // eq.setHighShelf(1.2);
    // eq.applyEQ(samples);

    // Utils::normalize(samples);

    

    auto end = std::chrono::high_resolution_clock::now(); // End timing

    std::chrono::duration<double> elapsed = end - start; // Compute elapsed time

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    fh.write(samples);

}
