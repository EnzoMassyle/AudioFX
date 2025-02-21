#ifndef TEMPO_H
#define TEMPO_H

#include <vector>
#include <utils.h>
#include <thread>
#include <cassert>
class Tempo
{
private:
    static void changeTempoSlice(const vector<double>& channel, int sliceStart, int hopSize, double r, vector<double> &out);
    static void changeTempoChannel(const vector<double>& channel, double r, vector<double> &out);
public:
    static vector<vector<double>> changeTempo(const vector<vector<double>>& samples, double r);
};

#endif