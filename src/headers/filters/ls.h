#ifndef LS_H
#define LS_H

#include "biquad.h"
class LowShelf : public Biquad
{
    private: 
        double f0, fs, s;
        void setCoefficients();
    public:
        LowShelf(double gain, double cutoffFreq, int sampleRate, double slope);
};
#endif