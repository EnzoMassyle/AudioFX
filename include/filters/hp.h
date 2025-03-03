#ifndef HP_H
#define HP_H

#include "biquad.h"
class HighPass : public Biquad
{
    public:
        HighPass(double cutoffFreq, int sampleRate, double qualityFactor);
        void setCoefficients(double f0, double q) override;
};
#endif