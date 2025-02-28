#ifndef LP_H
#define LP_H

#include "biquad.h"
#include <cassert>
class LowPass : public Biquad
{
    private:
        double q;
    public:
        LowPass(double cutoffFreq, int sampleRate, double q);
        void setCoefficients(double f0) override;
};
#endif