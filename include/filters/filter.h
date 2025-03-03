#ifndef FILTER_H
#define FILTER_H

#include <vector>
using namespace std;
class Filter
{
public:
    virtual ~Filter() {};
    virtual void process(vector<vector<double>>&) = 0;

};
#endif