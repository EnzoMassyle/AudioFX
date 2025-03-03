#ifndef BIQUAD_H
#define BIQUAD_H

#include "filter.h"
#include <cassert>
class Biquad : public Filter
{
    protected: 
        // Biquad filter coefficients
        double a0, a1, a2, b0, b1, b2;

        double fs;
    public:
        void process(vector<vector<double>>& samples) override;
        virtual void setCoefficients(double, double) = 0;
};




#endif