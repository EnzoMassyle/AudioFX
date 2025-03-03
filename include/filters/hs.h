#ifndef HS_H
#define HS_H

#include "biquad.h"
class HighShelf : public Biquad
{
    private: 
        double f0;
    public:
        HighShelf(double gain, double cutoffFreq, double sampleRate, double slope);
        void setCoefficients(double gain, double slope) override;
};
#endif