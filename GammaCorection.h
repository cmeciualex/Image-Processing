/*
* GammaCorection.h
 *
 * This header defines the GammaCorection class, which performs gamma correction
 * on grayscale images by transforming each pixel with a power-law function.
 */

#ifndef GAMMACORECTION_H
#define GAMMACORECTION_H
#include "ImageProcessing.h"
#include <cmath>
/**
 * GammaCorection applies gamma correction to enhance or compress image brightness.
 */
class GammaCorection : public ImageProcessing {
private:
    float gamma; ///< The gamma value used for correction (power factor).
public:
    /**
     * Constructor for GammaCorection.
     * @param gama Gamma correction factor (default is 1.0, which applies no change).
     */
    GammaCorection(float gama = 1.0);

    /**
     * Applies gamma correction to the source image and stores the result in dst.
     * @param src Input source image.
     * @param dst Output image after applying gamma correction (must be the same size as src).
     */
    void process(const Image &src, Image &dst) override;
};


#endif //GAMMACORECTION_H
