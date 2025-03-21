#include<gtest/gtest.h>
#include "../include/fxaudio.h"

/* Coverage for autotune constructor */
TEST(AutoTuneTests, Constructor) {
    string invalidNote = "H";
    string validNote = "C";
    char invalidScale = 'B';
    char validScale ='M';
    ASSERT_ANY_THROW(Autotune(1.0, invalidNote, validScale));
    ASSERT_ANY_THROW(Autotune(1.0, validNote, invalidScale));
    ASSERT_NO_THROW(Autotune(1.0, validNote, validScale));
}

/* Coverage for processing audio methods mostly all of these below test for ensuring proper behavior on edge cases such as an empty list and faulty args*/
TEST(AutoTuneTests, Process) {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");
    AFX afx = AFX();
    vector<vector<double>> empty;
    ASSERT_NO_THROW(afx.autotune(af.samples, 1.0, "F", 'm', af.info.samplerate));
    ASSERT_ANY_THROW(afx.autotune(empty, 1.0, "F", 'm', 0));
}


TEST(PitchShiftTests, Process) {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");
    AFX afx = AFX();
    vector<vector<double>> empty;
    ASSERT_NO_THROW(afx.pitchShift(af.samples, 5));
    ASSERT_ANY_THROW(afx.pitchShift(empty,5));
}


TEST(TimeStretchTests, Process) {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");
    AFX afx = AFX();
    vector<vector<double>> empty;
    ASSERT_NO_THROW(afx.timeStretch(af.samples, 1.2));
    ASSERT_ANY_THROW(afx.timeStretch(empty,1.2));
    ASSERT_ANY_THROW(afx.timeStretch(af.samples, 0));
}

TEST(TempoTests, Process) {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");
    AFX afx = AFX();
    vector<vector<double>> empty;
    ASSERT_NO_THROW(afx.changeTempo(af.samples, 1.2));
    ASSERT_ANY_THROW(afx.changeTempo(empty,1.2));
}

TEST(LayerTests, Process) {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");
    AFX afx = AFX();
    vector<vector<double>> empty;
    ASSERT_NO_THROW(afx.layer(af.samples, 5, 1));
    ASSERT_ANY_THROW(afx.layer(empty,5, 1));
}


TEST(ConvReverbTests, Process) {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");
    AudioFile ir = fh.open("../assets/ir/church.wav");
    AFX afx = AFX();
    vector<vector<double>> empty;
    ASSERT_NO_THROW(afx.convReverb(af.samples, ir.samples));
    ASSERT_ANY_THROW(afx.convReverb(empty, ir.samples));
    ASSERT_ANY_THROW(afx.convReverb(af.samples, empty));
}


