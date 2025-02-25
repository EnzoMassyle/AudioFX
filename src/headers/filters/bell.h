#ifndef BP_H
#define BP_H

#include "filter.h"
class BellFilter : public Filter
{
    private:
        double g;
        double wc;
        double a0, a1, a2, b0, b1, b2;

    public:
        BellFilter(double gain, double cutoffFreq, double sampleRate, double qFactor);
        void process(vector<vector<double>>& samples) override;
};
#endif