#ifndef BIQUAD_H
#define BIQUAD_H

#include "filter.h"


class Biquad : public Filter
{
    protected: 
        double a0, a1, a2, b0, b1, b2;
        void setCoefficients();
    public:
        void process(vector<vector<double>>& samples) override;
};




#endif