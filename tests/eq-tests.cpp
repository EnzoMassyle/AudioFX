#include<gtest/gtest.h>
#include "../include/fxaudio.h"



TEST(EQTests, UseEQ) {
    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");
    double badArray[5] = {1,1,1,1,1};
    /* Call with improper array size */
    ASSERT_ANY_THROW(EQ(af.info.samplerate, badArray, 5));
    EQ eq = EQ(af.info.samplerate);

    /* High pass */
    ASSERT_ANY_THROW(eq.setHighPass(0, 0)); // try with invalid quality factor
    ASSERT_NO_THROW(eq.setHighPass(0, 1));

    /* Low pass */
    ASSERT_ANY_THROW(eq.setLowPass(20000, 0)); // try with invalid quality factor
    ASSERT_NO_THROW(eq.setLowPass(20000, 1));
    
    /* Low Shelf */
    ASSERT_ANY_THROW(eq.setLowShelf(1.0, 0)); // try with invalid slope
    ASSERT_NO_THROW(eq.setLowShelf(1.0, 1));

    /* High Shelf */
    ASSERT_ANY_THROW(eq.setHighShelf(1.0, 0)); // try with invalid slope
    ASSERT_NO_THROW(eq.setHighShelf(1.0, 1));
    
    /* Bell  only need to test 1 it should cover all */
    ASSERT_NO_THROW(eq.setBell1(1.0, 0)); // try with invalid slope
    ASSERT_NO_THROW(eq.setBell1(1.0, 1));





}