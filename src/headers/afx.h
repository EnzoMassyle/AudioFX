#include <freeverb/Components/revmodel.hpp>
#include <filters/lp.h>
#include <filters/median.h>
#include <filehandler.h>
#include <utils.h>
#include <convreverb.h>
#include <timestretch.h>
#include <autotune.h>
#include <tempo.h>
#include <vector>

using namespace std;
class AFX
{
public:
    vector<vector<double>> convReverb(vector<vector<double>> samples, string room = "CHURCH") { return Reverb::convReverb(samples, room);};
    vector<vector<double>> pitchShift(vector<vector<double>> samples, double pitchFactor);
    vector<vector<double>> pitchShift(vector<vector<double>> samples, int semitones) {return pitchShift(samples, pow(2, (semitones / 12.0)));};
    vector<vector<double>> timeStretch(vector<vector<double>> samples, double stretchFactor) { return TimeStretch::changeSpeed(samples, stretchFactor); };
    vector<vector<double>> changeTempo(vector<vector<double>> samples, double r) {return Tempo::changeTempo(samples, r);};
    vector<vector<double>> artificialReverb(vector<vector<double>> samples);
    vector<vector<double>> reverse(vector<vector<double>> samples);
    vector<vector<double>> autotune(vector<vector<double>> samples, double intensity, string note, char scale, int sampleRate);
    vector<vector<double>> demix(vector<vector<double>> samples, bool vocals);
};