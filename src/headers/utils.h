#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include "fft.h"
#include "params.h"
#include <cmath>

using namespace std;

class Utils
{
public:
    /**
     * @param size -> length of window
     *
     * Apply hamming window to v
     */
    static void applyWindow(vector<double> &v);

    /**
     * @param v -> vector
     *
     * Apply normalization factor to all audio samples
     */
    static void normalize(vector<vector<double>> &v);

    /**
     * @param v -> vector
     *
     * Modify v to have entries in reverse order for each row
     */
    static void reverse(vector<vector<double>>& v);

    /**
     * @param v -> vector
     * @param g -> gain
     */
    static void gain(vector<vector<double>> &v, double g);

    /**
     * @param v1 -> vector one
     * @param v2 -> vector two
     *
     * Convolve v1 and v2 using FFT. Result is stored in v1.
     */
    static void convolve(vector<double> &v1, vector<double> v2);

    /**
     * @param n -> number
     * Return the next power of 2 that is >= n. If n is already a power of 2, n is returned
     */
    static int nextPowerOfTwo(int n);
};

#endif