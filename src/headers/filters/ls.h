#ifndef LS_H
#define LS_H

#include "biquad.h"
class LowShelf : public Biquad
{
    private: 
        double f0, s;
    public:
        LowShelf(double gain, double cutoffFreq, int sampleRate, double slope);
        void setCoefficients(double) override;
};
#endif