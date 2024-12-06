#ifndef AUTOTUNE_H
#define AUTOTUNE_H
#include <iostream>
#include<map>
#include<vector>
#include<sndfile.h>
#include "../SoundTouch/include/SoundTouch.h"
#include "../FFT/kiss_fft.h"
#include "../AudioFile/AudioFile.h"


using namespace soundtouch;
using namespace std;
class  Autotune {
    private:
        static double noteTbl [128];
        static map<string, int> noteOffsets;
        static int majorSemitones[7];
        static vector<double> scaleNotes;
        static map<char, array<int, 7>> intervals;
        static map<string, double> rootNotes;

        int chunkSize;
        SoundTouch st;

        vector<double> tuneSlice(vector<double> slice, int sampleRate, int size);
        vector<double> generateWindow(int);
        static void processSample();
        double findShiftingFactor(double);

        
    public: 
        double intensity;
        string note;
        char scale; // Major (M) or minor (m)
        Autotune(double intensity, string note, char scale);
        void process(const char*);
        void fillNoteTable();

};

#endif
