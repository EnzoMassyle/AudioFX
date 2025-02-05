#include <../../headers/filters/hp.h>

HighPass::HighPass(double alpha)
{
    this->alpha = alpha;
}

void HighPass::process(vector<vector<double>>& samples)
{
    for (int chan = 0; chan < samples.size(); chan++) 
    {
        vector<double> copy = samples[chan];
        if (samples[chan].size() > 0)
        {
            this->prev = samples[chan][0];
        }
        for (int i = 1; i < samples[chan].size(); i++)
        {
            samples[chan][i] = (this->alpha) * (this->prev + copy[i] - copy[i-1]);
            this->prev = samples[chan][i];
        }
    }
}