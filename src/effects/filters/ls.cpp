#include <../headers/filters/ls.h>
#include <iostream>
LowShelf::LowShelf(double gain, double cutoffFreq, double sampleRate)
{
    this->g = gain;
    this->wc = (cutoffFreq * 2* M_PI) / sampleRate;
    double alpha = tan(wc / 2);
    double beta = sqrt(this->g);

    this-> a0 = alpha + beta;
    this-> a1 = alpha - beta / this->a0;
    this->b0 = (this->g * (alpha + beta)) / this->a0;
    this->b1 = (this->g * (alpha - beta)) / this->a0; 
}

void LowShelf::process(vector<vector<double>>& samples)
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