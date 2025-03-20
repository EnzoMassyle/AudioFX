#ifndef BIQUAD_H
#define BIQUAD_H

#include "filter.h"

/**
 * @class Biquad
 * 
 * @brief Represents a Biquad filter which is a type of filter
 */
class Biquad : public Filter
{
    protected: 
        // Biquad filter coefficients
        double a0, a1, a2, b0, b1, b2;

        double fs;
    public:
        /**
         * @brief apply biquad filter to v
         * @param v -> signal separated by channel
         * 
         */
        void process(vector<vector<double>>& samples) override;

        /**
         * @brief sets the parameters of the filter. What is being set depends on the type of filter
         */
        virtual void setCoefficients(double, double) = 0;
};




#endif