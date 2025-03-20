#ifndef HP_H
#define HP_H

#include "biquad.h"


/**
 * @class HighPass
 * 
 * @brief Represents a high pass filter which is a type of biquad filter
 */
class HighPass : public Biquad
{
    public:
        /**
         * @brief Establish filter parameters
         * @param cutoffFreq -> cutoff frequency
         * @param sampleRate -> sample rate for audio being processed through filter
         * @param q -> Quality factor
         */
        HighPass(double cutoffFreq, int sampleRate, double q);

        /**
         * @brief Set cutoff frequency and/or quality factor.
         * 
         * @param f0 -> cutoff frequency
         * @param q -> Quality Factor
         */
        void setCoefficients(double f0, double q) override;
};
#endif