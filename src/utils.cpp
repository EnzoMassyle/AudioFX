#include <headers/utils.h>
#include <cmath>

void Utils::applyWindow(vector<double> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        v[i] *= 0.5 * (1 - cos((2 * M_PI * i) / (v.size() - 1)));
    }
}

void Utils::normalize(vector<vector<double>> &v)
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

void Utils::gain(vector<vector<double>> &v, double g)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            v[i][j] *= g;
        }
    }
}

void Utils::convolve(vector<double> &v1, vector<double> v2)
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

    vector<complex<double>> z = handler.fft(v1);
    vector<complex<double>> w = handler.fft(v2);

    for (int i = 0; i < N; i++)
    {
        // Multiply two complex numbers: (a + bi) * (c + di) = (ac−bd) + (ad+bc)i
        double tempR = (z[i].real() * w[i].real()) - (z[i].imag() * w[i].imag());
        double tempI = (z[i].real() * w[i].imag()) + (z[i].imag() * w[i].real());
        z[i] = complex<double>(tempR, tempI);
    }
    v1 = handler.ifft(z);
}

int Utils::nextPowerOfTwo(int n)
{
    int p = 0;
    while ((int)pow(2, p) / n == 0)
    {
        p++;
    }
    return pow(2, p);
}