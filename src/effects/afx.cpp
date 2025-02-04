#include <../headers/afx.h>

vector<vector<double>> AFX::artificialReverb(vector<vector<double>> samples)
{
    int numChannels = samples.size();
    if (samples.empty() || samples[0].empty())
    {
        throw runtime_error("Invalid input: Empty sample buffer.");
    }

    int numSamples = samples[0].size();
    revmodel reverb;
    reverb.setdry(0.8);
    reverb.setwet(0.3);
    reverb.setroomsize(0.8);
    Utils::gain(samples, 0.1);

    // Allocate buffers
    vector<double> inLeft(numSamples);
    vector<double> inRight(numSamples);
    vector<double> outLeft(numSamples);
    vector<double> outRight(numSamples);

    // Fill input buffers
    for (int i = 0; i < numSamples; i++)
    {
        inLeft[i] = samples[0][i];
        inRight[i] = (numChannels > 1) ? samples[1][i] : samples[0][i];  // Ensure stereo input
    }

    // Apply reverb
    reverb.processreplace(inLeft.data(), inRight.data(), outLeft.data(), outRight.data(), numSamples, 1);


    // Store processed output
    for (int i = 0; i < numSamples; i++)
    {
        samples[0][i] = outLeft[i];
        if (numChannels > 1)
        {
            samples[1][i] = outRight[i];
        }
    }
    LowPass lp = LowPass(0.5);
    lp.process(samples);
    // Utils::gain(samples, 10000);
    Utils::normalize(samples);
    return samples;
}

vector<vector<double>> AFX::autotune(vector<vector<double>> samples, double intensity, string note, char scale, int sampleRate)
{
    Autotune autotune = Autotune(intensity, note, scale);
    autotune.fillNoteTable();
    return autotune.process(samples, sampleRate);
};

vector<vector<double>> AFX::reverse(vector<vector<double>> samples)
{
    for (int chan = 0; chan < samples.size(); chan++)
    {
        int l = 0;
        int r = samples[chan].size() - 1;
        while (l < r)
        {
            double temp = samples[chan][l];
            samples[chan][l] = samples[chan][r];
            samples[chan][r] = temp;
            l++;
            r--;
        }
    }

    return samples;
}