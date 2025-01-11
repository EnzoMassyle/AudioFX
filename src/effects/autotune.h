#ifndef AUTOTUNE_H
#define AUTOTUNE_H
#include <iostream>
#include <map>
#include <vector>
#include <sndfile.h>
#include "filehandler.h"
#include "utils.h"
#include "fft.h"
using namespace std;
class Autotune
{
private:
    inline static vector<double> scaleNotes;
    static map<char, array<int, 7>> intervals;
    static map<string, double> rootNotes;

    int chunkSize;

    vector<double> tuneSlice(vector<double> slice, int sampleRate);
    double findShiftingFactor(double);

public:
    Autotune(double intensity, string note, char scale);

    double intensity;
    string note;
    char scale; // Major (M) or minor (m)

    void process(const char *);
    void fillNoteTable();
};

#endif
