#ifndef LP_H
#define LP_H

#include "biquad.h"
#include <cassert>
class LowPass : public Biquad
{
    private:
        double f0, fs;
        void setCoefficients();
    public:
        LowPass(double cutoffFreq, int sampleRate, double q);
};
#endif