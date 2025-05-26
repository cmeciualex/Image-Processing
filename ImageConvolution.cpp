#include "ImageConvolution.h"
#include <algorithm>

ImageConvolution::ImageConvolution(const Kernel& k, ScaleFunc func) : kernel(k), scaleFunc(func) {}


void ImageConvolution::process(const Image& src, Image& dst) {
    if (src.getWidth() != dst.getWidth() || src.getHeight() != dst.getHeight()) {
        throw std::runtime_error("Source and destination images must have the same dimensions");
    }

    int kCenterX = kernel.getWidth() / 2;
    int kCenterY = kernel.getHeight() / 2;

    for (unsigned int y = 0; y < src.getHeight(); y++) {
        for (unsigned int x = 0; x < src.getWidth(); x++) {
            float sum = 0.0f;

            for (unsigned int u = 0; u < kernel.getWidth(); u++) {
                for (unsigned int v = 0; v < kernel.getHeight(); v++) {
                    int ix = static_cast<int>(x) - static_cast<int>(u) + kCenterX;
                    int iy = static_cast<int>(y) - static_cast<int>(v) + kCenterY;

                    if (ix >= 0 && ix < static_cast<int>(src.getWidth()) &&
                        iy >= 0 && iy < static_cast<int>(src.getHeight())) {
                        sum += kernel.at(u, v) * src.at(ix, iy);
                        }
                }
            }
            dst.at(x, y) = scaleFunc(sum);
        }
    }
}
