#ifndef LP_H
#define LP_H

#include "biquad.h"

/**
 * @class LowPass
 * 
 * @brief Represents a low pass filter which is a type of biquad filter
 */
class LowPass : public Biquad
{
    public:
        /**
         * @brief Establish filter parameters
         * @param cutoffFreq -> cutoff frequency
         * @param sampleRate -> sample rate for audio being processed through filter
         * @param q -> Quality factor
         */
        LowPass(double cutoffFreq, int sampleRate, double q);

        /**
         * @brief Set cutoff frequency and/or quality factor.
         * 
         * @param f0 -> cutoff frequency
         * @param q -> Quality Factor
         */
        void setCoefficients(double f0, double q) override;
};
#endif