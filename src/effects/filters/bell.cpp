#include <../headers/filters/hs.h>


#include <../headers/filters/bell.h>
#include <iostream>
BellFilter::BellFilter(double gain, double cutoffFreq, double sampleRate, double bandwidth)
{
    this->f0 = cutoffFreq;
    this->fs = sampleRate;

    this->setCoefficients(gain, bandwidth);
}

void BellFilter::setCoefficients(double gain, double bw)
{
    assert(bw > 0);
    double a = pow(10, gain / 40.0);
    double wc = (this->f0 * 2 * M_PI) / this->fs;
    double alpha = sin(wc) * (bw / 2.0);

    this->a0 = 1 + (alpha / a);
    this->a1 = (-2 * cos(wc)) / this->a0;
    this->a2 = (1 - (alpha / a)) / this->a0;

    this->b0 = (1 + (alpha * a)) / this->a0;
    this->b1 = (-2 * cos(wc)) / this->a0;
    this->b2 = (1 - (alpha * a)) / this->a0;
}