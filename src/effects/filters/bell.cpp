#include <../headers/filters/hs.h>


#include <../headers/filters/bell.h>
#include <iostream>
BellFilter::BellFilter(double gain, double cutoffFreq, double sampleRate, double bandwidth)
{
    this->g = gain;
    this->wc = (cutoffFreq * 2* M_PI) / sampleRate;
    double alpha = tan(bandwidth / 2);
    double beta = sqrt(this->g);
    double gamma = cos(wc);

    this->a0 = beta + alpha;
    this->a1 = (2 * beta * gamma) / this->a0; 
    this->a2 = beta - alpha;

    this->b0 = (beta + this->g * alpha) / this->a0; 
    this->b1 = (2 * beta * gamma) / this->a0; 
    this->b2 = (beta  - this->g * alpha)/ this->a0;
}

void BellFilter::process(vector<vector<double>>& samples)
{
    for (int chan = 0; chan < samples.size(); chan++)
    {
        double prevX[2] = {samples[chan][0], samples[chan][1]};
        double prevY [2] = {0.0, 0.0};
        for(int i = 2; i < samples[chan].size(); i++)
        {
            double temp = samples[chan][i];
            samples[chan][i] = (this->b0 * samples[chan][i]) + (b1 * prevX[1]) + (b2 * prevX[0]) - (a1 * prevY[1]) - (a2 * prevY[0]);
            prevX[0] = prevX[1];
            prevX[1] = temp;
            prevY[0] = prevY[1];
            prevY[1] = samples[chan][i];
        }
    }
}