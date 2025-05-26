#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include "Image.h"


class ImageProcessing {
public:
    virtual void process(const Image& src, Image& dst) = 0;
    virtual ~ImageProcessing() = default;
};



#endif //IMAGEPROCESSING_H
