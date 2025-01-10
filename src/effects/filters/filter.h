#ifndef FILTER_H
#define FILTER_H

#include <vector>
using namespace std;
class Filter
{
public:
    virtual ~Filter() {};
    virtual vector<double> apply() const = 0;
};
#endif