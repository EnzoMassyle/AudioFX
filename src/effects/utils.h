#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

using namespace std;
class Utils
{
public:
    /**
     * @param size -> length of window
     *
     * Generate Hamming window
     */
    static vector<double> generateWindow(int size)
    {
        vector<double> window(size);
        for (int i = 0; i < size; i++)
        {
            window[i] = 0.5 * (1 - cos((2 * M_PI * i) / (size - 1)));
        }
        return window;
    }

    /**
     * @param samples Audio samples separated by channel
     * 
     * Apply normalization factor to all audio samples
     */
    static void normalize(vector<vector<double>>& samples) {
        // Calculate maximum peak
        double peak = 0.0;
        for (int chan = 0; chan < samples.size(); chan++) {
            for (int i = 0; i < samples[chan].size(); i++) {
                peak = fmax(peak, abs(samples[chan][i]));
            }
        }
        // apply normalization
        if (peak > 0.0) {
            double normalizationFactor = 1.0 / peak;
            for (int chan = 0; chan < samples.size(); chan++) {
                for (int i = 0; i < samples[chan].size(); i++) {
                    samples[chan][i] *= normalizationFactor;
                }
            }
        }
    }
};

#endif