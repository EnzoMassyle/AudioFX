#include <iostream>
#include "effects/autotune.h"
#include "effects/timeshift.h"
#include "effects/pitchshift.h"
#include "effects/reverb.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Please provide one file to process! " << endl;
        return 0;
    }
    char parentFolder[16] = "../samples/";
    char *fn = strcat(parentFolder, argv[1]);
    // Perform Autotune in C Major Scale
    Autotune *obj = new Autotune(1,  "A", 'm');
    obj->fillNoteTable();
    obj->process(fn);
    // TimeShift::changeSpseed(fn, 1.2);
    // PitchShift::changePitch(fn, 0.93);
    // Reverb::apply(fn, "AIRY");
}
