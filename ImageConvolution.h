/*
* ImageConvolution.h
 *
 * This header defines the ImageConvolution class, which performs convolution
 * of an image with a specified kernel and applies a scaling function to the result.
 */
#ifndef IMAGECONVOLUTION_H
#define IMAGECONVOLUTION_H

#include "ImageProcessing.h"
#include "Kernel.h"
#include <stdexcept>

/**
 * ScaleFunc is a function pointer type for scaling a float convolution result
 * into an unsigned char pixel value.
 * @param float value - the raw convolution sum.
 * @return unsigned char - the scaled pixel value.
 */
using ScaleFunc = unsigned char(*)(float);
/**
 * ImageConvolution performs convolution on grayscale images using a kernel and a scaling function.
 */
class ImageConvolution : public ImageProcessing {
private:
    Kernel kernel; ///< Convolution kernel.
    ScaleFunc scaleFunc; ///< Function to scale the convolution output to pixel value.

public:
    /**
     * Constructor for ImageConvolution.
     * @param k Convolution kernel.
     * @param func Scaling function to map float result to unsigned char.
     */
    ImageConvolution(const Kernel &k, ScaleFunc func);

    /**
     * Example helper scaling function that clamps a float value to [0,255].
     * @param value The float value to clamp.
     * @return The clamped unsigned char pixel value.
     */
    unsigned char clampScale(float value);

    /**
     * Applies convolution on the source image using the kernel and writes to dst image.
     * @param src Input source image.
     * @param dst Output image to store the convolved result (must have same dimensions as src).
     * @throws std::runtime_error if src and dst sizes differ.
     */
    void process(const Image &src, Image &dst) override;
};

#endif // IMAGECONVOLUTION_H
