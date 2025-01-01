#include <iostream>
#include "effects/autotune.h"

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
    Autotune *obj = new Autotune(0.2, "C", 'M');
    obj->fillNoteTable();
    obj->process(fn);
}
