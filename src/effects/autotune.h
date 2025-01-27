#ifndef AUTOTUNE_H
#define AUTOTUNE_H
#include <iostream>
#include <map>
#include <vector>
#include <sndfile.h>
#include <thread>
#include "filehandler.h"
#include "utils.h"
#include "params.h"
#include "fft.h"
using namespace std;
class Autotune
{
private:
    inline static vector<double> scaleNotes;
    static map<char, array<int, 7>> intervals;
    static map<string, double> rootNotes;

    void tuneSlice(vector<double> slice, int start, int sampleRate, vector<double>& out);
    double findShiftingFactor(double);
    void test();

public:
    Autotune(double intensity, string note, char scale);
    double intensity;
    string note;
    char scale; // Major (M) or minor (m)

    void process(const char *);
    void fillNoteTable();
};

#endif
