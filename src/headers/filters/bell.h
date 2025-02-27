#ifndef BP_H
#define BP_H

#include "biquad.h"
class BellFilter : public Biquad
{
    private: 
        double f0, fs, bw;
        void setCoefficients();

    public:
        BellFilter(double gain, double cutoffFreq, double sampleRate, double qFactor);
};
#endif