#include "../../headers/filters/lp.h"
#include<iostream>
LowPass::LowPass(double cutoffFreq, int sampleRate, double q)
{
    assert(q > 0);

    double wc = (cutoffFreq * 2 *  M_PI) / sampleRate;
    double alpha = sin(wc) / (2 * q);
    double beta = cos(wc); 

    this->a0 = 1 + alpha;
    this->a1 = (-2*beta) / this->a0;
    this->a2 = (1 - alpha) / this->a0;
    this->b0 = ((1 - beta) / 2) / this->a0;
    this->b1 = (1 - beta) / this->a0;
    this->b2 = ((1 - beta) / 2) / this->a0;
}