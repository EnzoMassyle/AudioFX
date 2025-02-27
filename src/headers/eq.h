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
class EQ {
    // Filter bands
    private:
        int sampleRate;
        double gains[NUM_GAIN_FILTERS];
        Filter** filters = nullptr;
        void addFilters();
    public: 
        EQ(int sr);
        EQ(int sr, double* g, int lenG);
        ~EQ();

        void applyEQ(vector<vector<double>>& samples);

        void setLowPass(double cutoffFreq);
        void setHighPass(double cutoffFreq);
        void setLowShelf(double gain);
        void setHighShelf(double gain);
        void setBell1(double gain);
        void setBell2(double gain);
        void setBell3(double gain);
        void setBell4(double gain);
};

#endif 