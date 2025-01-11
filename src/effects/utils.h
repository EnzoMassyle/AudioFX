#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <future>
#include "fft.h"
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
     * @param v -> vector
     *
     * Apply normalization factor to all audio samples
     */
    static void normalize(vector<vector<double>> &v)
    {
        // Calculate maximum peak
        double peak = 0.0;
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v[i].size(); j++)
            {
                peak = fmax(peak, abs(v[i][j]));
            }
        }
        // apply normalization
        if (peak > 0.0)
        {
            double normalizationFactor = 1.0 / peak;
            for (int i = 0; i < v.size(); i++)
            {
                for (int j = 0; j < v[i].size(); j++)
                {
                    v[i][j] *= normalizationFactor;
                }
            }
        }
    }
    /**
     * @param v -> vector
     * @param g -> gain
     */
    static void gain(vector<vector<double>> &v, double g) {
        for (int i = 0; i < v.size(); i++)
            {
                for (int j = 0; j < v[i].size(); j++)
                {
                    v[i][j] *= g;
                }
            }
    }
    /**
     * @param v1 -> vector one
     * @param v2 -> vector two
     * 
     * Convolve v1 and v2 using FFT
     */
    static vector<double> convolve(vector<double> v1, vector<double> v2, promise<vector<double>>&& p)
    {
        int N;
        if (v1.size() > v2.size()) {
            N = nextPowerOfTwo(v1.size());
        } else {
            N = nextPowerOfTwo(v2.size());
        }
        FFT handler = FFT(N);
        
        cpx* out = handler.fft(v1);
        cpx* outIr = handler.fft(v2);

        for (int i = 0; i < N; i++)
        {
            // Multiply two complex numbers: (a + bi) * (c + di) = (ac−bd) + (ad+bc)i
            double temp1 = (out[i].r * outIr[i].r) - (out[i].i * outIr[i].i);
            double temp2 = (out[i].r * outIr[i].i) + (out[i].i * outIr[i].r);
            out[i].r = temp1;
            out[i].i = temp2;
        }
        vector<double> output = handler.ifft(out);
        p.set_value(output);
        return output;
    }
    /**
     * @param 
     */
    static int nextPowerOfTwo(int n)
    {
        int p = 0;
        while ((int) pow(2, p) / n == 0)
        {
            p++;
        }
        return pow(2, p);
    }
};

#endif