#ifndef FILTER_H
#define FILTER_H

#include <vector>
using namespace std;
class Filter
{
protected: 
    double prev;
public:
    virtual ~Filter() {};
    virtual void process(vector<vector<double>>& samples) = 0;

};
#endif