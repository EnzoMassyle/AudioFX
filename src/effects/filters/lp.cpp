#include <../../headers/filters/lp.h>

LowPass::LowPass(double alpha)
{
    this->prev = 0.0;
    this->alpha = alpha;

}

void LowPass::process(vector<vector<double>>& samples)
{
    for (int chan = 0; chan < samples.size(); chan++) 
    {
        for (int i = 0; i < samples[chan].size(); i++)
        {
            samples[chan][i] = (this->alpha) * samples[chan][i] + (1-this->alpha) * this->prev;
            this->prev = samples[chan][i];
        }
    }
}