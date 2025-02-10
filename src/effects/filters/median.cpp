#include <../headers/filters/median.h>


// CLEAN UP
void MedianF::process(vector<vector<double>>& samples)
{
    double window[5];
    vector<vector<double>> output(samples.size(), vector<double>(samples[0].size()));
    for (int chan = 0; chan < samples.size(); chan++)
    {
        for (int i = 0; i < samples[chan].size(); i++)
        {
            for (int j = 0, k = -3; j < 6; j++, k++)
            {
                window[j] = (i + k >= 0 && i + k < samples[chan].size()) ? samples[chan][i+k] : 0.0;
            }
            sort(begin(window), end(window));
            output[chan][i] = window[2];
        }
    }
    samples = output;
}