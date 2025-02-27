#include <../headers/filters/ls.h>
#include <iostream>
#include <cassert>
LowShelf::LowShelf(double gain, double cutoffFreq, int sampleRate, double slope)
{
    assert(slope > 0);
    this->f0 = cutoffFreq;
    this->fs = sampleRate;
    this->s = slope;

    this->setCoefficients(gain);
    
}

void LowShelf::setCoefficients(double f)
{
    double a = pow(10, f / 40.0);
    double wc = (this->f0 * 2 *  M_PI) / this->fs;
    double alpha = (sin(wc) * sqrt((a + (1/a)) * ((1 / this->s) - 1) + 2)) / 2;
    double beta = cos(wc); 
    double gamma = sqrt(a);


    this->a0 = (a + 1) + (a - 1) * beta + 2 * gamma * alpha;
    this->a1 = (-2 * ((a-1) + (a+1)*beta)) / this->a0;
    this->a2 = ((a + 1) + (a-1) * beta - 2 * gamma * alpha) / this->a0;
    this->b0 = (a * ((a+1) - (a-1) * beta + 2 * gamma * alpha)) / this->a0;
    this->b1 = (2 * a *((a-1) - (a+1)*beta)) / this->a0;
    this->b2 = (a * ((a + 1) - (a-1) * beta - 2 * gamma * alpha)) / this->a0;
}