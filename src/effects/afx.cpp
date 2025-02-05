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
    reverb.setdry(0.9);
    reverb.setwet(0.25);
    reverb.setroomsize(0.9);
    reverb.setwidth(1.5);
    reverb.setdamp(0.8);
    Utils::gain(samples, 0.1);

    // Allocate buffers
    vector<double> inLeft(numSamples);
    vector<double> inRight(numSamples);
    vector<double> outLeft(numSamples);
    vector<double> outRight(numSamples);

    // Fill input buffers
    inLeft = samples[0];
    inRight = (numChannels > 1) ? samples[1] : inLeft;
    
    // Apply reverb
    reverb.processreplace(inLeft.data(), inRight.data(), outLeft.data(), outRight.data(), numSamples, 1);

    // Store processed output
    samples[0] = outLeft;
    if(numChannels > 1) {
        samples[1] = outRight;
    }

    LowPass lp = LowPass(0.35);
    lp.process(samples);
    // Utils::gain(samples, 5);
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
