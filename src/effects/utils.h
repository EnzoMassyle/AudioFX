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
     * @param v1 -> vector one
     * @param v2 -> vector two
     * 
     * Convolve v1 and v2 using FFT
     */
    static vector<double> convolve(vector<double> v1, vector<double> v2)
    {
        int N = max(nextPowerOfTwo(v1.size()), nextPowerOfTwo(v2.size()));
        vector<double> output(N, 0.0);
        kiss_fft_cfg cfg = kiss_fft_alloc(N, 0, nullptr, nullptr);
        kiss_fft_cfg inv = kiss_fft_alloc(N, 1, nullptr, nullptr);

        if (!cfg || !inv)
        {
            kiss_fft_free(cfg);
            kiss_fft_free(inv);
            throw "allocation failed";
        }

        kiss_fft_cpx *in = (kiss_fft_cpx *)malloc(sizeof(kiss_fft_cpx) * N);
        kiss_fft_cpx *out = (kiss_fft_cpx *)malloc(sizeof(kiss_fft_cpx) * N);
        for (int i = 0; i < N; i++)
        {
            in[i].r = i < v1.size() ? v1[i] : 0.0;
            in[i].i = 0;
        }

        kiss_fft_cpx *inIr = (kiss_fft_cpx *)malloc(sizeof(kiss_fft_cpx) * N);
        kiss_fft_cpx *outIr = (kiss_fft_cpx *)malloc(sizeof(kiss_fft_cpx) * N);
        for (int i = 0; i < N; i++)
        {
            inIr[i].r = i < v2.size() ? v2[i] : 0.0;
            inIr[i].i = 0;
        }

        kiss_fft(cfg, in, out);
        kiss_fft(cfg, inIr, outIr);
        for (int i = 0; i < N; i++)
        {
            double temp1 = (out[i].r * outIr[i].r) - (out[i].i * outIr[i].i);
            double temp2 = (out[i].r * outIr[i].i) + (out[i].i * outIr[i].r);
            out[i].r = temp1;
            out[i].i = temp2;
        }

        kiss_fft(inv, out, in);
        for (int i = 0; i < N; i++)
        {
            output[i] = in[i].r / N;
        }
        free(in);
        free(out);
        free(inIr);
        free(outIr);
        kiss_fft_free(cfg);
        kiss_fft_free(inv);

        return output;
    }

    static int nextPowerOfTwo(int n)
    {
        int power = 0;
        while ((int)pow(2, power) / n == 0)
        {
            power++;
        }

        return pow(2, power);
    }
};

#endif