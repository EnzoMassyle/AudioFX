#include <../headers/filters/hs.h>


#include <../headers/filters/ls.h>
#include <iostream>
HighShelf::HighShelf(double gain, double cutoffFreq, double sampleRate)
{
    this->g = gain;
    this->wc = (cutoffFreq * 2* M_PI) / sampleRate;
    double alpha = tan(wc / 2);
    double beta = sqrt(this->g);

    this-> a0 = beta * alpha + 1;
    this-> a1 = beta * alpha - 1 / this->a0;
    this->b0 = (beta * alpha + this->g) / this->a0;
    this->b1 = (beta * alpha - this->g) / this->a0; 
}

void HighShelf::process(vector<vector<double>>& samples)
{
    for (int chan = 0; chan < samples.size(); chan++)
    {
        double prevX = samples[chan][0];
        double prevY = 0.0;
        for(int i = 0; i < samples[chan].size(); i++)
        {
            double temp = samples[chan][i];
            samples[chan][i] = (this->b0 * samples[chan][i]) + (b1 * prevX) - (a1 * prevY);
            prevX = temp;
            prevY = samples[chan][i];
        }
    }
}