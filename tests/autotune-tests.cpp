#include <gtest/gtest.h>
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

/* Coverage for processing audio */
TEST(AutoTuneTests, Process) {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");
    AFX afx = AFX();
    vector<vector<double>> empty;
    ASSERT_NO_THROW(afx.autotune(af.samples, 1.0, "F", 'm', af.info.samplerate));
    ASSERT_ANY_THROW(afx.autotune(empty, 1.0, "F", 'm', 0));
}