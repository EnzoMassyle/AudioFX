#include "filters/hp.h"
HighPass::HighPass(double cutoffFreq, int sampleRate, double q)
{
    this->fs = sampleRate;
    this->setCoefficients(cutoffFreq, q);
    
}

void HighPass::setCoefficients(double f0, double q)
{
    assert(q > 0);
    double wc = (f0 * 2 *  PI) / this->fs;
    double alpha = sin(wc) / (2 * q);
    double beta = cos(wc); 

    this->a0 = 1 + alpha;
    this->a1 = (-2*beta) / this->a0;
    this->a2 = (1 - alpha) / this->a0;
    this->b0 = ((1 + beta) / 2) / this->a0;
    this->b1 = (-1 - beta) / this->a0;
    this->b2 = ((1 + beta) / 2) / this->a0;
}
