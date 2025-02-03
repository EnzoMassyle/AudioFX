#ifndef LP_H
#define LP_H

#include "filter.h"
class LowPass : public Filter
{
    private:
        double alpha;

    public:
        LowPass(double alpha);
        void process(vector<vector<double>>& samples) override;
};
#endif