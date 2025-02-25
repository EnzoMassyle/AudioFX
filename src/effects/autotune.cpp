#include <../headers/autotune.h>
#include <afx.h>
map<char, array<int, 7>> Autotune::intervals = {
    {'M', {2, 4, 5, 7, 9, 11, 12}},
    {'m', {2, 3, 5, 7, 8, 10, 12}}};

map<string, double> Autotune::rootNotes = {
    {"C", 261.63},
    {"C#", 277.18},
    {"D", 293.66},
    {"D#", 311.13},
    {"E", 329.63},
    {"F", 349.23},
    {"F#", 369.99},
    {"G", 392.00},
    {"G#", 415.30},
    {"A", 440.00},
    {"A#", 466.16},
    {"B", 493.88},
};

Autotune::Autotune(double intensity, string note, char scale)
{
    this->intensity = intensity;
    this->note = note;
    this->scale = scale;
}

void Autotune::fillNoteTable()
{
    double f0 = rootNotes[this->note];
    double n0 = 69;

    array<int, 7> semitones = intervals[this->scale];
    for (int octave = 0; octave < 8; octave++)
    {
        double freq = f0 * pow(2, (12 * (octave - 4)) / 12.0);
        this->scaleNotes.push_back(freq);
        for (int n : semitones)
        {
            double freq = f0 * pow(2, (n + 12 * (octave - 4)) / 12.0);
            this->scaleNotes.push_back(freq);
        }
    }
}

vector<vector<double>> Autotune::process(const vector<vector<double>>& samples, int sampleRate)
{
    this->sampleRate = sampleRate;
    int numChannels = samples.size();
    cout << "Processing..." << endl;
    vector<vector<double>> output(samples.size(), vector<double>(samples[0].size(), 0.0));

    vector<thread> threads;
    // Process audio file in chunks. Will need to process each channel separately
    for (int chan = 0; chan < numChannels; chan++)
    {
        threads.emplace_back([this, samples, &output, chan]()
                             { this->tuneChannel(samples[chan], output[chan]); });
    }

    for (thread &t : threads)
    {
        t.join();
    }

    Utils::normalize(output);
    return output;
}
void Autotune::tuneChannel(const vector<double>& channel, vector<double> &out)
{
    // random_device device;
    // mt19937 gen(device());
    // uniform_int_distribution grainStart(-AT_OFFSET,AT_OFFSET);
    // uniform_int_distribution grainSize(AT_CHUNK_SZ,AT_CHUNK_SZ + 3000);
    // int step = AT_CHUNK_SZ / AT_OVERLAP;

    int frameSize = 5000;
    int hopSize = 1000;
    vector<thread> threads;

    for (int start = 0; start < channel.size(); start += hopSize)
    {
        int end = min(start + frameSize, (int)channel.size());
        vector<double> audioSlice(channel.begin() + start, channel.begin() + end);
        Utils::applyWindow(audioSlice);
        threads.emplace_back(
            [this, start, audioSlice, &out]()
            {
                this->tuneSlice(audioSlice, start, ref(out));
            });
    }

    for (thread &t : threads)
    {
        t.join();
    }
}

void Autotune::tuneSlice(vector<double> slice, int start, vector<double> &out)
{
    int N = Utils::nextPowerOfTwo(AT_CHUNK_SZ);
    FFT handler = FFT(N);
    vector<complex<double>> shiftedOut(N, 0.0);
    for (int i = 0; i < N; i++)
    {
        shiftedOut[i] = 0.0;
    }
    int originalSize = slice.size();
    vector<complex<double>> sliceFreq = handler.fft(slice);

    // Find dominating frequency
    double maxMag = 0;
    int dominatingBin = 0;
    for (int i = 0; i < N / 2; i++)
    {
        double magnitude = abs(sliceFreq[i]);
        if (magnitude > maxMag)
        {
            maxMag = magnitude;
            dominatingBin = i;
        }
    }
    double dominatingFrequency = (dominatingBin * this->sampleRate) / N;
    double shiftFactor = findShiftingFactor(dominatingFrequency);
    if (shiftFactor == 0)
    {
        slice = handler.ifft(sliceFreq);
        slice.resize(originalSize);
        Utils::applyWindow(slice);
        for (int i = 0; i < slice.size(); i++)
        {
            out[i + start] += slice[i];
        }
        return;
    }

    
    // cout << shiftFactor << endl;
    // Apply shifting factor. if the new bin is a fraction, properly distribute energy to lower and upper bin
    // vector<vector<double>> temp;

    // temp.push_back(handler.ifft(sliceFreq));
    // temp[0].resize(originalSize);
    // AFX afx = AFX();
    // temp = afx.pitchShift(temp, 1);
    // // AFX
    // // temp = Tempo::changeTempo(temp, shiftFactor);
    // // temp = TimeStretch::changeSpeed(temp, shiftFactor);
    // // cout << "hi" << temp[0].size() << endl;;
    // // temp[0].resize(originalSize);
    // // 
    // // temp = Tempo::changeTempo(temp, 1 / shiftFactor);
    // // temp = TimeStretch::changeSpeed(temp, 1 / shiftFactor);

    for (int i = 0; i < N; i++)
    {
        double newBin = (i * shiftFactor);
        int lower = floor(newBin);
        int upper = ceil(newBin);
        double frac = newBin - lower;
        if (lower >= 0 && lower < N / 2)
        {
            shiftedOut[lower] += sliceFreq[i] * (1.0 - frac);
        }
        if (upper >= 0 && upper < N / 2)
        {
            shiftedOut[upper] += sliceFreq[i] * frac;
        }
    }

    slice = handler.ifft(shiftedOut);
    slice.resize(originalSize);
    // temp[0].resize(originalSize);
    Utils::applyWindow(slice);
    for (int i = 0; i < slice.size(); i++)
    {
        // cout << temp[0][i] << endl;
        // if (i + start > out.size())
        // {
        //     cout << "." << endl;
        // }
        out[i + start] += slice[i];
    }
}

double Autotune::findShiftingFactor(double f)
{
    if (f == 0)
    {
        return 0.0;
    }
    double closestNote = this->scaleNotes[0];
    double smallestDif = fabs(closestNote - f);

    for (int i = 0; i < this->scaleNotes.size(); i++)
    {
        double dif = fabs(this->scaleNotes[i] - f);
        if (dif < smallestDif)
        {
            closestNote = this->scaleNotes[i];
            smallestDif = dif;
        }
    }
    return pow(closestNote / f, this->intensity);
}