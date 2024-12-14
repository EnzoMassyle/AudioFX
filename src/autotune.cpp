#include "autotune.h"

double Autotune::noteTbl [128];
vector<double> Autotune::scaleNotes;
const int SAMPLE_LEN = 512;
map<char, array<int, 7>> Autotune::intervals = {
    {'M', {2, 4, 5, 7, 9, 11, 12}},
    {'m', {2, 3, 5, 7, 8, 10, 12}}
};

map<string, double> Autotune::rootNotes = {
    {"C", 261.63}, 
    {"C#", 277.18}, 
    {"D", 293.66}, 
    {"D#", 311.13}, 
    {"E", 329.63}, 
    {"F", 349.23}, 
    {"F#", 369.99}, 
    {"G", 392.00}, 
    {"G#", 415.30 }, 
    {"A", 440.00}, 
    {"A#", 466.16}, 
    {"B", 493.88}, 
};


Autotune::Autotune(double intensity, string note, char scale) {
    this->intensity = intensity;
    this->note = note;
    this->scale = scale;
    this->chunkSize = 8192;
}

/**
 * Fill note table depending on the musical scale used
 */
void Autotune::fillNoteTable() {
    double f0 = rootNotes[this->note];
    double n0 = 69;
    // Calculate frequencies of each MIDI note
    for (int midiNote = 0; midiNote < 128; midiNote++) {
        double freq = f0 * pow(2, (midiNote - n0) / 12);
        noteTbl[midiNote] = freq;
    }
    array<int, 7> semitones = intervals[this->scale];
    for (int octave = 0; octave < 8; octave++) {
        double freq = f0 * pow(2, (12 * (octave - 4)) / 12.0);
        scaleNotes.push_back(freq);
        for (int n : semitones) {
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
void Autotune::process(const char* fn) {

    const char* inFileName = fn;
    const char* outFileName = "out.wav";
    // Prepare to read wav file
    SNDFILE* inFile;
    SNDFILE* outFile;

    SF_INFO info;
    memset(&info, 0, sizeof(info));
    try {
        if (!(inFile = sf_open(inFileName, SFM_READ, &info))) {
            throw inFileName;
        }
        if (!(outFile = sf_open(outFileName, SFM_WRITE, &info))) {
            throw outFileName;
        }
    } catch (string& fn) {
         cout << fn << " not found" << endl; 
    }

    // Put samples into a vector
    int bufferLen = SAMPLE_LEN * info.channels;
    double* buffer = (double*) malloc(bufferLen * sizeof(double));
    vector<double> samples;
    int readcount;

    while ((readcount = (int) sf_read_double(inFile, buffer, bufferLen))) {
        samples.insert(samples.end(), buffer, buffer + bufferLen);
    }

    cout << "Successfully read " << inFileName <<  endl;
    cout << "Processing..." << endl;
    int numSamples =  samples.size();
    int numChannels = info.channels;
    int paddedSize = ((numSamples + chunkSize - 1) / chunkSize) * chunkSize; // Round up to the nearest multiple of chunk size
    samples.resize(paddedSize, 0); // Pad with zeros
    vector<double> window = generateWindow(chunkSize / numChannels);
    vector<double> output(samples.size(), 0.0);

    int s = chunkSize * numChannels;
    int step = chunkSize / 6;

    for (int start = 0, end = chunkSize; end < numSamples; start += step, end += step) {
        for (int chan = 0; chan < info.channels; chan++) {
            vector<double> audioSlice;
            for (int k = start + chan; k < end; k += numChannels) {
                audioSlice.push_back(samples[k]);
            }
            for (int i = 0; i < window.size(); i++) {
                audioSlice[i] *=  window[i];
            }
            vector<double> shiftedSlice = tuneSlice(audioSlice, info.samplerate, s);
            for (int i = start + chan, j = 0; j < shiftedSlice.size() && i < end && i < samples.size(); i+= numChannels, j++) {
                output[i] += shiftedSlice[j] * window[j];
            }
        }
    }
    cout << "Saving..." << endl;
    for (int i = 0; i < output.size(); i += bufferLen) {
        int size = min((int)output.size() - i, bufferLen);
        copy(output.begin() + i, output.begin() + i + size, buffer);
        sf_write_double(outFile, buffer, bufferLen);
    }
    cout << "Done!" << endl;

    free(buffer);
}


/**
 * @param slice -> Chunk of an audio sample
 * 
 * Analyze frequencies of the audio slice and tune it to the nearest correct note
 */
vector<double> Autotune::tuneSlice(vector<double> slice, int sampleRate, int size) {
    int fftSize = size;//this->chunkSize;
    kiss_fft_cfg cfg = kiss_fft_alloc(fftSize, 0, nullptr, nullptr);
    kiss_fft_cfg inv = kiss_fft_alloc(fftSize, 1, nullptr, nullptr);
    kiss_fft_cpx* in = (kiss_fft_cpx*) malloc(sizeof(kiss_fft_cpx) * fftSize);
    kiss_fft_cpx* out = (kiss_fft_cpx*) malloc(sizeof(kiss_fft_cpx) * fftSize);
    kiss_fft_cpx* shiftedOut = (kiss_fft_cpx*) malloc(sizeof(kiss_fft_cpx) * fftSize);


    for (int i = 0; i < fftSize; i++) {
        in[i].r = slice[i];
        in[i].i = 0;
        shiftedOut[i].r = 0;
        shiftedOut[i].i = 0;
    }
    kiss_fft(cfg, in, out);
    // Find dominating frequency
    double maxMag = 0;
    int dominatingBin = 0;
    for (int i = 0; i < fftSize; i++) {
        double magnitude = sqrt((out[i].r * out[i].r) + (out[i].i * out[i].i));
        if (magnitude > maxMag) {
            maxMag = magnitude;
            dominatingBin = i;
        }
    }
    double dominatingFrequency = (dominatingBin * sampleRate) / fftSize;
    double shiftFactor = findShiftingFactor(dominatingFrequency);
    if (shiftFactor == 0) {
        free(in);
        free(out);
        free(shiftedOut);
        kiss_fft_free(cfg);
        kiss_fft_free(inv);
        return slice;
    }
    // Apply shifting factor
    for (int i = 0; i < fftSize; i++) {
        int newBin = (int) i * shiftFactor;
        if (newBin < fftSize / 2) {
            shiftedOut[newBin].r += out[i].r;
            shiftedOut[newBin].i += out[i].i;
        }
    }
    // Apply filter
    kiss_fft(inv, shiftedOut, in);
    vector<double> output(fftSize);
    for (int i = 0; i < fftSize; i++) {
        output[i] = in[i].r / fftSize;
    }
    free(in);
    free(out);
    free(shiftedOut);
    kiss_fft_free(cfg);
    kiss_fft_free(inv);
    return output;
}

/**
 * @param f -> frequency
 * 
 * For a given frequency, find the closest note for the given scale and calculate the shifting factor
 */
double Autotune::findShiftingFactor(double f) {
    if (f == 0) {
        return 0.0;
    }   
    double closestNote = scaleNotes[0];
    double smallestDif = fabs(closestNote - f);

    for (int i = 0; i < scaleNotes.size(); i++) {
        double dif = fabs(scaleNotes[i] - f);
        if (dif < smallestDif) {
            closestNote = scaleNotes[i];
            smallestDif = dif;
        }
    }
    return pow(closestNote / f, this->intensity);
}

/**
 * @param size -> length of window
 *
 * Generate Hamming window
 */
vector<double> Autotune::generateWindow(int size) {
    vector<double> window(size);
    for (int i = 0; i < size; i++) {
        window[i] = 0.5 * (1 - cos((2 * M_PI * i) / (size - 1)));
    }
    return window;
}

