#ifndef HP_H
#define HP_H

#include "biquad.h"
#include <cassert>
class HighPass : public Biquad
{
    private: 
        double q;
    public:
        HighPass(double cutoffFreq, int sampleRate, double qualityFactor);
        void setCoefficients(double f0) override;
};
#endif