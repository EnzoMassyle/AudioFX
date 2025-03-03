#ifndef EQ_H
#define EQ_H

#include <vector>
#include <cassert>
#include "filters/filter.h"
#include "filters/bell.h"
#include "filters/hp.h"
#include "filters/lp.h"
#include "filters/hs.h"
#include "filters/ls.h"
#include "params.h"
class EQ
{
private:
    int sampleRate;
    double gains[NUM_GAIN_FILTERS];
    Biquad **filters = nullptr;
    void addFilters();

public:

    /**
     * @param sr -> sample rate
     * 
     * Initialize all filters for EQ
     */
    EQ(int sr);

    /**
     * @param sr -> samples rate
     * @param g -> array of gains for each filter that is not a pass filter
     * @param lenG -> length of array g
     * 
     * Initialize filters for EQ giving then the corresponding gains in g
     */
    EQ(int sr, double g[], int lenG);

    /**
     * Free memory
     */
    ~EQ();

    /**
     * @param samples -> audio samples separated by channel
     * 
     * Apply filters to samples in a cascading fashion
     */
    void applyEQ(vector<vector<double>> &samples);

    /* Setters */
    void setHighPass(double cutoffFreq, double q = 0.707) { this->filters[0]->setCoefficients(cutoffFreq, q); }
    void setLowShelf(double gain, double slope = 1.0) { this->filters[1]->setCoefficients(gain, slope); }
    void setBell1(double gain, double bw = 0.6) { this->filters[2]->setCoefficients(gain, bw); }
    void setBell2(double gain, double bw = 0.3) {this->filters[3]->setCoefficients(gain, bw);}
    void setBell3(double gain, double bw = 0.4) {this->filters[4]->setCoefficients(gain, bw);}
    void setBell4(double gain, double bw = 0.2) {this->filters[5]->setCoefficients(gain, bw);}
    void setHighShelf(double gain, double slope = 1.0) { this->filters[6]->setCoefficients(gain, slope); }
    void setLowPass(double cutoffFreq, double q = 0.707){this->filters[7]->setCoefficients(cutoffFreq, q);}

};

#endif