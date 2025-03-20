#ifndef BP_H
#define BP_H

#include "biquad.h"

/**
 * @class BellFilter
 * 
 * @brief Represents a bell/peaking filter which is a type of biquad filter
 */
class BellFilter : public Biquad
{
    private: 
        double f0; //cutoff freq

    public:
        /**
         * @brief Establish filter parameters
         * @param gain -> gain for filter
         * @param cutoffFreq -> cutoff frequency
         * @param sampleRate -> sample rate for audio being processed through filter
         * @param bandwidth -> bandwidth
         */
        BellFilter(double gain, double cutoffFreq, double sampleRate, double bandwidth);

        /**
         * @brief Set gain and/or bandwidth the cutoff frequency stays fixed
         * 
         * @param gain -> gain
         * @param bw -> bandwidth
         */
        void setCoefficients(double gain, double bw) override;
};
#endif