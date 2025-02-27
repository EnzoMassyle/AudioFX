
#include "../../headers/filters/biquad.h"


void Biquad::process(vector<vector<double>>& samples)
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