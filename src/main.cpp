#include <iostream>
#include "../include/fxaudio.h"   
#include <chrono>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Please provide one file to process! " << endl;
        return 0;
    }
    auto start = std::chrono::high_resolution_clock::now();
    // char parentFolder[128] = "../samples/";
    // char *fn = strcat(parentFolder, argv[1]);

    FileHandler fh = FileHandler();
    AudioFile af = fh.open(argv[1]);
    AudioFile ir = fh.open("../assets/ir/church.wav");
    AFX afx = AFX();

    /* Perform sound transformations here */
    // samples = afx.layer(samples, -0.5, 0.5);
    // samples = afx.layer(samples, 0.5, 0.5);
    // samples = afx.layer(samples, 1, 0.15);
    // af.samples = afx.layer(af.samples, -1, 0.15);
    //hello 
    // af.samples = afx.pitchShift(af.samples, 10);
    af.samples = afx.autotune(af.samples, 1.0, "F", 'm', af.info.samplerate);
    // af.samples = afx.convReverb(af.samples, ir.samples);
    // af.samples = afx.changeTempo(af.samples, 0.877);
    // EQ eq = afx.createEQ();
    // eq.setBell2(1.3);
    // eq.setBell3(1.2);
    // eq.setLowPass(17500);
    // eq.setHighShelf(1.2);



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
    fh.write(af);

}
