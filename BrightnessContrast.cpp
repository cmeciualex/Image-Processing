#include "BrightnessContrast.h"
BrightnessContrast::BrightnessContrast(float alpha,float beta) {
    this->alpha=alpha;
    this->beta=beta;
}

void BrightnessContrast::process(const Image& src, Image& dst) {
    if (src.getHeight()!=dst.getHeight()||src.getWidth()!=dst.getWidth()) {
        throw std::runtime_error("Images size are different");
    }
    for (unsigned int i=0;i<src.getHeight();i++) {
        for (unsigned int j=0;j<src.getWidth();j++) {
            int val = static_cast<int>(this->alpha * src.at(j, i) + this->beta);///conversie la int
            if (val > 255) val = 255;
            else if (val < 0) val = 0;
            dst.at(j, i) = static_cast<unsigned char>(val);
        }
    }
}