#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <cmath>
#include "params.h"
using namespace std;
class Filter
{
public:
    virtual ~Filter() {};
    virtual void process(vector<vector<double>>&) = 0;

};
#endif