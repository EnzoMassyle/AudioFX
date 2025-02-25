#ifndef LS_H
#define LS_H

#include "filter.h"
class LowShelf : public Filter
{
    private:
        double g;
        double wc;
        double a0, a1, a2, b0, b1, b2;
    

    public:
        LowShelf(double gain, double cutoffFreq, double sampleRate);
        void process(vector<vector<double>>& samples) override;
};
#endif