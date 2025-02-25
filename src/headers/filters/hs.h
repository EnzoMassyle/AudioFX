#ifndef HS_H
#define HS_H

#include "filter.h"
class HighShelf : public Filter
{
    private:
        double g;
        double wc;
        double a0, a1, a2, b0, b1, b2;
    

    public:
        HighShelf(double gain, double cutoffFreq, double sampleRate);
        void process(vector<vector<double>>& samples) override;
};
#endif