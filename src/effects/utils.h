#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <future>
#include "fft.h"
#include "params.h"
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
    static void gain(vector<vector<double>> &v, double g)
    {
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
     * Convolve v1 and v2 using FFT. Result is stored in v1.
     */
    static void convolve(vector<double> &v1, vector<double> v2)
    {
        int N;
        if (v1.size() > v2.size())
        {
            N = nextPowerOfTwo(v1.size());
        }
        else
        {
            N = nextPowerOfTwo(v2.size());
        }
        FFT handler = FFT(N);

        cpx *z = handler.fft(v1);
        cpx *w = handler.fft(v2);

        for (int i = 0; i < N; i++)
        {
            // Multiply two complex numbers: (a + bi) * (c + di) = (ac−bd) + (ad+bc)i
            double temp1 = (z[i].r * w[i].r) - (z[i].i * w[i].i);
            double temp2 = (z[i].r * w[i].i) + (z[i].i * w[i].r);
            z[i].r = temp1;
            z[i].i = temp2;
        }
        v1 = handler.ifft(z);
    }
    /**
     * @param n -> number
     * Return the next power of 2 that is >= n. If n is already a power of 2, n is returned
     */
    static int nextPowerOfTwo(int n)
    {
        int p = 0;
        while ((int)pow(2, p) / n == 0)
        {
            p++;
        }
        return pow(2, p);
    }
};

#endif