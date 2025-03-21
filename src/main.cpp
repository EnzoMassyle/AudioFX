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
    af.samples = afx.autotune(af.samples, 1.0, "F", 'm', af.info.samplerate);

    

    auto end = std::chrono::high_resolution_clock::now(); // End timing

    std::chrono::duration<double> elapsed = end - start; // Compute elapsed time

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
    fh.write(af);

}
