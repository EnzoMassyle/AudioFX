#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <cmath>
#include "../params.h"
using namespace std;

/**
 * @class Filter
 * 
 * @brief Base class for a digital filter
 */
class Filter
{
public:
    /**
     * @brief apply digital filter to v
     * @param v -> signal separated by channel
     * 
     */
    virtual void process(vector<vector<double>>& v) = 0;

};
#endif