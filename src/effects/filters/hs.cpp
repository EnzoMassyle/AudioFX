#include <../headers/filters/hs.h>
HighShelf::HighShelf(double gain, double cutoffFreq, double sampleRate, double slope)
{
    assert(slope > 0);
    double a = pow(10, gain / 40.0);
    double wc = (cutoffFreq * 2 *  M_PI) / sampleRate;
    double alpha = (sin(wc) * sqrt((a + (1/a)) * ((1 / slope) - 1) + 2)) / 2;
    double beta = cos(wc); 
    double gamma = sqrt(a);


    this->a0 = (a + 1) - (a - 1) * beta + 2 * gamma * alpha;
    this->a1 = (2 * ((a-1) - (a+1)*beta)) / this->a0;
    this->a2 = ((a + 1) - (a-1) * beta - 2 * gamma * alpha) / this->a0;

    this->b0 = (a * ((a+1) + (a-1) * beta + 2 * gamma * alpha)) / this->a0;
    this->b1 = (-2 * a *((a-1) + (a+1)*beta)) / this->a0;
    this->b2 = (a * ((a + 1) + (a-1) * beta - 2 * gamma * alpha)) / this->a0;
}