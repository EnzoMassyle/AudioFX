#include <../headers/afx.h>

vector<vector<double>> AFX::artificialReverb(vector<vector<double>>& samples)
{
    int numChannels = samples.size();
    if (samples.empty() || samples[0].empty())
    {
        throw runtime_error("Invalid input: Empty sample buffer.");
    }

    int numSamples = samples[0].size();
    revmodel reverb;
    reverb.setdry(0.9);
    reverb.setwet(0.5);
    reverb.setroomsize(0.5);
    reverb.setwidth(0.1);
    reverb.setdamp(0.8);
    // Utils::gain(samples, 0.1);

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

    MedianF filter = MedianF();
    filter.process(samples);
    Utils::normalize(samples);

    return samples;
}

vector<vector<double>> AFX::autotune(const vector<vector<double>>& samples, double intensity, string note, char scale, int sampleRate)
{
    Autotune autotune = Autotune(intensity, note, scale);
    autotune.fillNoteTable();
    return autotune.process(samples, sampleRate);
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

vector<vector<double>> AFX::pitchShift(vector<vector<double>> samples, int semitones)
{
    double pitchFactor = 1 / pow(2, (semitones / 12.0));
    samples = Tempo::changeTempo(samples, 1.0 / pitchFactor); // First resample to change pitch
    return TimeStretch::changeSpeed(samples, pitchFactor);
}

vector<vector<double>> AFX::demix(const vector<vector<double>>& samples, bool vocals)
{
    const char* command = "spleeter separate -p spleeter:5stems -o output ../samples/circles.mp3";
    int result = system(command);
    if (result == 0) {
    std::cout << "Command executed successfully" << std::endl;
    } else {
        std::cerr << "Command failed with exit code: " << result << std::endl;
    }
    return samples;
}


vector<vector<double>> AFX::harmony(vector<vector<double>> samples)
{
    int numChannels = samples.size();
    int channelLength = samples[0].size();
    vector<vector<vector<double>>> shiftedSamples(2);
    vector<vector<double>> out(numChannels, vector<double>(channelLength, 0.0));

    // shiftedSamples[0] = AFX::pitchShift(samples, -12);s
    shiftedSamples[0] = AFX::pitchShift(samples, 1);
    shiftedSamples[1] = AFX::pitchShift(samples, 2);

    for (int i = 0; i < shiftedSamples.size(); i++)
    {
        for (int chan = 0; chan < numChannels; chan++)
        {
            for (int k = 0; k < channelLength && k < out[chan].size(); k++)
            {
                out[chan][k] += shiftedSamples[i][chan][k];
                // cout << out[chan][k] << endl;
            }
        }
    }

    Utils::normalize(out);

    return out;

}
