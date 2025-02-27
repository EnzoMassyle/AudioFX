#ifndef HS_H
#define HS_H

#include "biquad.h"
#include <cassert>
class HighShelf : public Biquad
{
    private: 
        double f0, fs, s;
        void setCoefficients();
    public:
        HighShelf(double gain, double cutoffFreq, double sampleRate, double slope);   
};
#endif