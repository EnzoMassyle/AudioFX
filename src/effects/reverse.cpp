#include <../headers/reverse.h>


void Reverse::reverse(const char *fn)
{
    SF_INFO info;
    vector<vector<double>> samples = FileHandler::open(fn, info);

    for (int chan = 0; chan < samples.size(); chan++) {
        int l = 0; 
        int r = samples[chan].size() - 1;
        while (l < r) {
            double temp = samples[chan][l];
            samples[chan][l] = samples[chan][r];
            samples[chan][r] = temp;
            l++;
            r--;
        } 
    }

    FileHandler::write(samples, info);
}