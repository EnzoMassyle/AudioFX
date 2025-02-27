#ifndef HP_H
#define HP_H

#include "biquad.h"
#include <cassert>
class HighPass : public Biquad
{
    private: 
        double f0, fs;
        void setCoefficients();
    public:
        HighPass(double cutoffFreq, int sampleRate, double q);
};
#endif