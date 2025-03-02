#ifndef LP_H
#define LP_H

#include "biquad.h"
#include <cassert>
class LowPass : public Biquad
{
    public:
        LowPass(double cutoffFreq, int sampleRate, double q);
        void setCoefficients(double f0, double q) override;
};
#endif