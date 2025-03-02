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
     * @param v -> vector
     *
     * Apply hamming window to v
     */
    static void applyWindow(vector<double> &v);


    /**
     * @param s -> length of window
     * 
     * Generate hamming window of size s
     */
    static vector<double> generateWindow(int s);


    /**
     * @param x -> x
     * 
     * sinc(x) = sin(pi * x) / (pi * x)
     */
    static double sinc(double x);

    /**
     * @param v -> vector
     *
     * Apply normalization factor, result is stored in v
     */
    static void normalize(vector<vector<double>> &v);


    /**
     * @param v -> vector
     *
     * Apply normalization factor, result is stored in v
     */
    static void normalize(vector<double> &v);
    /**
     * @param v -> vector
     * @param g -> gain
     * 
     * Apply gain to vector, result is stored in v
     */
    static void gain(vector<vector<double>> &v, double g);

    /**
     * @param v1 -> vector one
     * @param v2 -> vector two
     *
     * Convolve v1 and v2 using FFT. Result is stored in v1.
     */
    static void  convolve(vector<double>& v1, const vector<double>& v2);

    /**
     * @param n -> number
     * 
     * Get the next power of 2 that is >= n
     */
    static int nextPowerOfTwo(int n);


    /**
     * @param v -> vector of complex numbers
     * @param k -> scalar
     * 
     * Perform scalar multiplication on each complex value
     */
    static vector<complex<double>> scaleComplex(const vector<complex<double>>& v, double k);

    /**
     * @param u -> complex vector
     * @param v -> complex vector 
     * 
     * Perform element wise addition on complex numbers This method assumes u.size() == v.size() 
     */
    static vector<complex<double>> addComplex(const vector<complex<double>>& u, const vector<complex<double>>& v);


};

#endif