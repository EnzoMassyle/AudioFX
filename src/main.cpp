#include <iostream>
#include "headers/autotune.h"
#include "headers/timestretch.h"
#include "headers/pitchshift.h"
#include "headers/reverb.h"
#include "headers/reverse.h"    
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Please provide one file to process! " << endl;
        return 0;
    }
    char parentFolder[128] = "../samples/";
    char *fn = strcat(parentFolder, argv[1]);
    // Perform Autotune in C Major Scale
    // Autotune *obj = new Autotune(1.0,  "A", 'm');
    // obj->fillNoteTable();
    // obj->process(fn);
    // delete obj;

    // change second parameter to affect playback speed   x > 1 Makes audio slower, x < 1 makes audio faster
    //  TimeStretch::changeSpeed(fn, 1.15);

    // change second parameter to affect pitch x > 1 makes pitch higher x < 1 makes pitch lower
    // PitchShift::changePitch(fn, 0.9);
    // Reverb::convReverb(fn, "AIRY");

    /* Reverse */
    // Reverse::reverse(fn);

}
