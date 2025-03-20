#ifndef HS_H
#define HS_H

#include "biquad.h"


/**
 * @class HighShelf
 * 
 * @brief Represents a high shelf filter which is a type of biquad filter
 */
class HighShelf : public Biquad
{
    private: 
        double f0; // cutoff frequency
    public:
        /**
         * @brief Establish filter parameters
         * @param gain -> gain
         * @param cutoffFreq -> cutoff frequency
         * @param sampleRate -> sample rate for audio being processed through filter
         * @param slope -> slope
         */
        HighShelf(double gain, double cutoffFreq, double sampleRate, double slope);


        /**
         * @brief Set gain and/or slope the cutoff frequency stays fixed
         * 
         * @param gain -> gain
         * @param slope -> slope
         */
        void setCoefficients(double gain, double slope) override;
};
#endif