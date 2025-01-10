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
    // Autotune *obj = new Autotune(1,  "C", 'M');
    // obj->fillNoteTable();
    // obj->process(fn);

    //change second parameter to affect playback speed   x > 1 Makes audio slower, x < 1 makes audio faster
    // TimeShift::changeSpeed(fn, 1);

    // change second parameter to affect pitch x > 1 makes pitch higher x < 1 makes pitch lower
    // PitchShift::changePitch(fn, 1);

    // Reverb::apply(fn);
}
