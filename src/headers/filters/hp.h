#ifndef HP_H
#define HP_H

#include "filter.h"
class HighPass : public Filter
{
    private:
        double alpha;

    public:
        HighPass(double alpha);
        void process(vector<vector<double>>& samples) override;
};
#endif