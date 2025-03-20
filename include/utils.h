#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>
#include "fft.h"
#include "params.h"

using namespace std;


/**
 * @class Utils
 * @brief helper functions
 * 
 */
class Utils
{
public:
    /**
     * @brief Apply hamming window to v
     * @param v -> vector
     *
     */
    static void applyWindow(vector<double> &v);


    /**
     * @brief Generate hamming window of size s
     * @param s -> length of window
     * 
     */
    static vector<double> generateWindow(int s);


    /**
     * @brief sinc(x) = sin(pi * x) / (pi * x)
     * @param x -> x
     * 
     */
    static double sinc(double x);

    /**
     * @brief Apply normalization factor, result is stored in v
     * @param v -> vector
     *
     */
    static void normalize(vector<vector<double>> &v);


    /**
     * @brief Apply normalization factor, result is stored in v
     * @param v -> vector
     *
     */
    static void normalize(vector<double> &v);
    /**
     * @brief Apply gain to vector, result is stored in v
     * @param v -> vector
     * @param g -> gain
     * 
     */
    static void gain(vector<vector<double>> &v, double g);

    /**
     * @brief Convolve v1 and v2 using FFT. Result is stored in v1.
     * @param v1 -> vector one
     * @param v2 -> vector two
     *
     */
    static void  convolve(vector<double>& v1, const vector<double>& v2);

    /**
     * @brief Get the next power of 2 that is >= n
     * @param n -> number
     * 
     */
    static int nextPowerOfTwo(int n);


    /**
     * @brief Perform scalar multiplication on each complex value
     * @param v -> vector of complex numbers
     * @param k -> scalar
     * 
     */
    static vector<complex<double>> scaleComplex(const vector<complex<double>>& v, double k);

    /**
     * @brief Perform element wise addition on complex numbers This method assumes u.size() == v.size() 
     * @param u -> complex vector
     * @param v -> complex vector 
     * 
     */
    static vector<complex<double>> addComplex(const vector<complex<double>>& u, const vector<complex<double>>& v);


};

#endif