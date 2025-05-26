/*
* BrightnessContrast.h
 *
 * This header defines the BrightnessContrast class, which adjusts the brightness and contrast
 * of a grayscale image using a linear transformation: new_value = alpha * old_value + beta.
 */

#ifndef BRIGHTNESSCONTRAST_H
#define BRIGHTNESSCONTRAST_H
#include "Image.h"
#include "ImageProcessing.h"

/**
 * BrightnessContrast is an image processing class that modifies pixel values by applying
 * a linear transformation for contrast and brightness adjustment.
 */
class BrightnessContrast : public ImageProcessing {
private:
    float alpha; ///< Contrast scaling factor.
    float beta; ///< Brightness offset value.
public:
    /**
     * Constructor for BrightnessContrast.
     * @param alpha Contrast factor (default 1.0 = no contrast change).
     * @param beta Brightness offset (default 0.0 = no brightness change).
     */
    BrightnessContrast(float alpha = 1.0, float beta = 0.0);

    /**
     * Applies the brightness and contrast adjustment to the source image and stores the result in dst.
     * @param src Input source image.
     * @param dst Output image after transformation (must have the same size as src).
     */
    void process(const Image &src, Image &dst) override;
};


#endif //BRIGHTNESSCONTRAST_H
