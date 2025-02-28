#include <../headers/filters/hs.h>


#include <../headers/filters/bell.h>
#include <iostream>
BellFilter::BellFilter(double gain, double cutoffFreq, double sampleRate, double bandwidth)
{
    this->f0 = cutoffFreq;
    this->fs = sampleRate;
    this->bw = bandwidth;

    this->setCoefficients(gain);
}

void BellFilter::setCoefficients(double gain)
{
    double a = pow(10, gain / 40.0);
    double wc = (this->f0 * 2 * M_PI) / this->fs;
    double alpha = sin(wc) * (this->bw / 2.0);

    this->a0 = 1 + (alpha / a);
    this->a1 = (-2 * cos(wc)) / this->a0;
    this->a2 = (1 - (alpha / a)) / this->a0;

    this->b0 = (1 + (alpha * a)) / this->a0;
    this->b1 = (-2 * cos(wc)) / this->a0;
    this->b2 = (1 - (alpha * a)) / this->a0;
}