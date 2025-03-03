#include "afx.h"

vector<vector<double>> AFX::autotune(const vector<vector<double>>& samples, double intensity, string note, char scale, int sr)
{
    Autotune autotune = Autotune(intensity, note, scale);
    autotune.fillNoteTable();
    return autotune.process(samples, sr);
};

vector<vector<double>> AFX::reverse(vector<vector<double>>& samples)
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

vector<vector<double>> AFX::pitchShift(vector<vector<double>>& samples, double semitones)
{
    double pitchFactor = 1 / pow(2, (semitones / 12.0));
    samples = TimeStretch::changeSpeed(samples, pitchFactor); // First resample to change pitch
    return Tempo::changeTempo(samples, 1 / pitchFactor);
}


vector<vector<double>> AFX::layer(vector<vector<double>> samples, double semitones, double g)
{
    AFX afx = AFX();
    vector<vector<double>> out = samples;
    samples = afx.pitchShift(samples, semitones);
    Utils::gain(samples, g);
    for (int chan = 0; chan < samples.size(); chan++)
    {
        for (int i = 0; i < samples[0].size() && i < out[chan].size(); i++)
        {
            out[chan][i] += samples[chan][i];
        }
    }
    Utils::normalize(out);

    return out;
}
