#ifndef BP_H
#define BP_H

#include "biquad.h"

class BellFilter : public Biquad
{
    private: 
        double f0;

    public:
        BellFilter(double gain, double cutoffFreq, double sampleRate, double qFactor);
        void setCoefficients(double gain, double bw) override;
};
#endif