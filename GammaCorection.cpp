#include "GammaCorection.h"

GammaCorection::GammaCorection(float gama) {
    this->gamma=gama;
}

void GammaCorection::process(const Image& src, Image& dst) {
    if (src.getHeight()!=dst.getHeight()||src.getWidth()!=dst.getWidth()) {
        throw std::runtime_error("Source and destination images must have the same dimensions");
    }
    for (unsigned int i=0;i<src.getHeight();i++)
        for (unsigned int j=0;j<src.getWidth();j++) {
            float normalized = static_cast<float>(src.at(j, i)) / 255.0;
            float corrected = pow(normalized, this->gamma);
            int val = static_cast<int>(corrected * 255.0 + 0.5);
            if (val > 255) val = 255;
            if (val < 0) val = 0;
            dst.at(j, i) = static_cast<unsigned char>(val);
        }
}
