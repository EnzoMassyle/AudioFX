#ifndef MEDIAN_H
#define MEDIAN_H

#include "filter.h"
#include <algorithm>
class MedianF : public Filter
{
    public:
        void process(vector<vector<double>>& samples) override;
};
#endif