#ifndef AUTOTUNE_H
#define AUTOTUNE_H
#include <iostream>
#include<map>
#include<vector>
#include "../SoundTouch/include/SoundTouch.h"
#include "../FFT/kiss_fft.h"
#include "../AudioFile/AudioFile.h"

using namespace soundtouch;
using namespace std;
class  Autotune {
    private:
        static map<int, vector<double>> noteTbl;
        SoundTouch st;
        AudioFile<double> af;
        vector<double> findNearestNote(vector<double>);
        vector<double> generateWindow(int);
        static void processSample();
        double findShiftingFactor(double);
        
    public: 
        int intensity;
        Autotune(int);
        void process(const string&);
        static void fillNoteTable() {
            // Fill out note table:
            double f0 = 440.0;
            double n0 = 69;
            // Calculate frequencies of each MIDI note
            for (int midiNote = 0; midiNote < 127; midiNote++) {
                int octave = midiNote / 12;
                double freq = f0 * pow(2, (midiNote - n0) / 12);
                noteTbl[octave].push_back(freq);
            }
            int x = 3;
        }
};

#endif
