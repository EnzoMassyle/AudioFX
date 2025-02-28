#ifndef EQ_H
#define EQ_H

#include <iostream>
#include <vector>
#include "filters/filter.h"
#include <filters/bell.h>
#include <filters/hp.h>
#include <filters/lp.h>
#include <filters/hs.h>
#include <filters/ls.h>
#include <cassert>

#include <params.h>
class EQ
{
    // Filter bands
private:
    int sampleRate;
    double gains[NUM_GAIN_FILTERS];
    Biquad **filters = nullptr;
    void addFilters();

public:
    EQ(int sr);
    EQ(int sr, double *g, int lenG);
    ~EQ();

    void applyEQ(vector<vector<double>> &samples);

    /* Setters */
    void setHighPass(double cutoffFreq) { this->filters[0]->setCoefficients(cutoffFreq); }
    void setLowShelf(double gain) { this->filters[1]->setCoefficients(gain); }
    void setBell1(double gain) { this->filters[2]->setCoefficients(gain); }
    void setBell2(double gain) {this->filters[3]->setCoefficients(gain);}
    void setBell3(double gain) {this->filters[4]->setCoefficients(gain);}
    void setBell4(double gain) {this->filters[5]->setCoefficients(gain);}
    void setHighShelf(double gain) { this->filters[6]->setCoefficients(gain); }
    void setLowPass(double cutoffFreq){this->filters[7]->setCoefficients(cutoffFreq);}

    /* Preset setters */
    void bassBoost();
    void trebelBoost();
    void vocalBoost();
    void louder();
    void speech();
    void lofi();
    void telephone();
};

#endif