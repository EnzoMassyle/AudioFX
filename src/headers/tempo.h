#ifndef TEMPO_H
#define TEMPO_H

#include <vector>
#include <utils.h>
#include <thread>
class Tempo
{
private:
    static int sliceSize;
    static void changeTempoChannel(const vector<double>& channel, double r, vector<double> &out);
    static void changeTempoSlice(const vector<double>& channel, int sliceStart, double r, vector<double> &out);
public:
    static vector<vector<double>> changeTempo(vector<vector<double>> samples, double r);
};

#endif