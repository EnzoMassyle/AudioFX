#include "autotune.h"

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

/**
 * @param intensity -> Determines how strong to apply the autotune effect
 * @param note -> The musical note to use as the root note
 * @param scale -> Category of semitones (major or minor)
 */
Autotune::Autotune(double intensity, string note, char scale)
{
    this->intensity = intensity;
    this->note = note;
    this->scale = scale;
}

/**
 * Fill note table depending on the musical scale used
 */
void Autotune::fillNoteTable()
{
    double f0 = rootNotes[this->note];
    double n0 = 69;

    array<int, 7> semitones = intervals[this->scale];
    for (int octave = 0; octave < 8; octave++)
    {
        double freq = f0 * pow(2, (12 * (octave - 4)) / 12.0);
        scaleNotes.push_back(freq);
        for (int n : semitones)
        {
            double freq = f0 * pow(2, (n + 12 * (octave - 4)) / 12.0);
            scaleNotes.push_back(freq);
        }
    }
}

/**
 * @param fn -> Audio file name
 *
 * Load file and analyze samples, Perform an overlap-add method where audio is broken up into slices. The signal is split up
 * into overlapping frames, where each one is individually processed and summed together
 */
void Autotune::process(const char *fn)
{
    SF_INFO info;
    vector<vector<double>> samples = FileHandler::open(fn, info);
    cout << "Processing..." << endl;
    vector<double> window = Utils::generateWindow(CHUNK_SIZE);
    vector<vector<double>> output(info.channels, vector<double>(samples[0].size(), 0.0));

    int step = CHUNK_SIZE / NUM_OVERLAP;
    // Process audio file in chunks. Will need to process each channel separately
    for (int chan = 0; chan < info.channels; chan++)
    {
        for (int start = 0, end = CHUNK_SIZE; end < samples[chan].size(); start += step, end += step)
        {
            vector<double> audioSlice(samples[chan].begin() + start, samples[chan].begin() + end);
            for (int i = 0; i < window.size(); i++)
            {
                audioSlice[i] *= window[i];
            }
            vector<double> shiftedSlice = tuneSlice(audioSlice, info.samplerate);
            for (int i = start, j = 0; j < shiftedSlice.size() && i < end && i < samples[chan].size(); i++, j++)
            {
                output[chan][i] += shiftedSlice[j];
            }
        }
    }
    Utils::normalize(output);
    FileHandler::write(output, info);
}

/**
 * @param slice -> Chunk of an audio sample
 *
 * Analyze frequencies of the audio slice and tune it to the nearest correct note
 */
vector<double> Autotune::tuneSlice(vector<double> slice, int sampleRate)
{
    int N = Utils::nextPowerOfTwo(CHUNK_SIZE);
    FFT handler = FFT(N);
    cpx shiftedOut[N];
    for (int i = 0; i < N; i++)
    {
        shiftedOut[i].r = 0;
        shiftedOut[i].i = 0;
    }
    cpx *out = handler.fft(slice);

    // Find dominating frequency
    double maxMag = 0;
    int dominatingBin = 0;
    for (int i = 0; i < N; i++)
    {
        double magnitude = sqrt((out[i].r * out[i].r) + (out[i].i * out[i].i));
        if (magnitude > maxMag)
        {
            maxMag = magnitude;
            dominatingBin = i;
        }
    }
    double dominatingFrequency = (dominatingBin * sampleRate) / N;
    double shiftFactor = findShiftingFactor(dominatingFrequency);
    if (shiftFactor == 0)
    {
        return slice;
    }
    // Apply shifting factor
    for (int i = 0; i < N; i++)
    {
        int newBin = (int)i * shiftFactor;
        if (newBin < N / 2)
        {
            shiftedOut[newBin].r += out[i].r;
            shiftedOut[newBin].i += out[i].i;
        }
    }
    return handler.ifft(shiftedOut);
}

/**
 * @param f -> frequency
 *
 * For a given frequency, find the closest note for the given scale and calculate the shifting factor
 */
double Autotune::findShiftingFactor(double f)
{
    if (f == 0)
    {
        return 0.0;
    }
    double closestNote = scaleNotes[0];
    double smallestDif = fabs(closestNote - f);

    for (int i = 0; i < scaleNotes.size(); i++)
    {
        double dif = fabs(scaleNotes[i] - f);
        if (dif < smallestDif)
        {
            closestNote = scaleNotes[i];
            smallestDif = dif;
        }
    }
    return pow(closestNote / f, this->intensity);
}