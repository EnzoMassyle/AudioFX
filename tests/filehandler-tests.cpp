#include<gtest/gtest.h>
#include "../include/filehandler.h"
/**
 * Open file Located at ../assets/Diner.wav which is a path that exists
 */
TEST(FileHandlerTests, OpenValidFile) {

    FileHandler fh = FileHandler();
    AudioFile af = fh.open("../assets/DinerShort.wav");

    /* Correct amount of audio channels*/
    ASSERT_EQ(af.info.channels, af.samples.size());

    /* Each channel should have a non-empty amount of samples */
    for (int chan = 0; chan < af.samples.size(); chan++) {
        ASSERT_FALSE(af.samples[chan].empty());
    }
}

/**
 * Ensure exception is thrown when invalid file path given
 */
TEST(FileHandlerTests, OpenInvalidFile) {
    FileHandler fh = FileHandler();

    ASSERT_ANY_THROW(fh.open("invalid.wav"));
}


