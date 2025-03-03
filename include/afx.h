#include <vector>
#include "filehandler.h"
#include "utils.h"
#include "convreverb.h"
#include "timestretch.h"
#include "autotune.h"
#include "tempo.h"
#include "eq.h"



using namespace std;
class AFX
{
public:
    /**
     * @param samples -> audio samples separated by channel
     * @param sr -> sample rate
     * @param intensity -> Determines how strong to apply the autotune effect
     * @param note -> The musical note to use as the root note
     * @param scale -> Category of semitones (major or minor)
     * Pitch correct vocals to the nearest correct note on musical scale (either major 'M' or minor 'm'). This one isn't very high quality I have been struggling with this one ;/
     */
    vector<vector<double>> autotune(const vector<vector<double>>& samples, double intensity, string note, char scale, int sr);
    /**
     * @param samples -> audio samples separated by channel
     * @param stretchFactor ->  > 1 will stretch the audio. < 1 will compress the audio
     * 
     * Use phase vocoder to time stretch/compress audio samples
     */
    vector<vector<double>> timeStretch(const vector<vector<double>>& samples, double stretchFactor) { return TimeStretch::changeSpeed(samples, stretchFactor); };
    /**
     * @param samples -> audio samples separated by channel
     * @param r -> resampling rate
     * Perform sinc interpolation to resample audio samples at a different playback rate
     */
    vector<vector<double>> changeTempo(const vector<vector<double>>& samples, double r) {return Tempo::changeTempo(samples, r);};
    /**
     * @param samples -> audio samples separated by channel
     * @param room -> room name of impulse response
     * 
     * Apply convolution based reverb to audio samples based on an impulse response. They can be found in samples/ir
     */
    vector<vector<double>> convReverb(vector<vector<double>>& samples, string room = "CHURCH") {return Reverb::convReverb(samples, room);};
    /**
     * @param samples -> audio samples separated by channel
     * 
     * Reverse audio samples resulting in audio played backwards
     */
    vector<vector<double>> reverse(vector<vector<double>>& samples);
    /**
     * @param samples -> audio samples separated by channel
     * @param semitones -> number of semitones to shift by
     * 
     * Shift pitch using a phase vocoder
     */
    vector<vector<double>> pitchShift(vector<vector<double>>& samples, double semitones);

    /**
     * @param samples -> audio samples separated by channel
     * @param semitones -> number of semitones to shift by
     * @param g -> gain to apply to layered audio
     * 
     * take input samples, shift the pitch and scale amplitudes. Layer on top of existing audio
     */
    vector<vector<double>> layer(vector<vector<double>> samples, double semitones, double g);

    /**
     * @param sampleRate -> sample rate of audio samples default is 44.1kHz
     * 
     * create a parametric equalizer with 8 Biquad filters
     */
    EQ createEQ(int sampleRate = 44100) {return EQ(sampleRate);}
};