#include "Image.h"
#include "BrightnessContrast.h"
#include <iostream>
#include "Drawing.h"
#include "GammaCorection.h"
#include "GaussianBlurKernel.h"
#include "HorizontalSobelKernel.h"
#include "IdentityKernel.h"
#include "ImageConvolution.h"
#include "MeanBlurKernel.h"
#include "Tests.h"
#include "VerticalSobelKernel.h"

auto scaleFunction = [](float val) -> unsigned char {
    int mapped = static_cast<int>((val + 1020.0f) * 255.0f / 2040.0f);
    if (mapped < 0) mapped = 0;
    if (mapped > 255) mapped = 255;
    return static_cast<unsigned char>(mapped);
};

int main() {
    Image src;
    Image dst;
    if (!src.load("input1.pgm")) {
        std::cout << "File load failed\n";
        return 1;
    }
    dst=src;
    BrightnessContrast processor(2,55);
    GammaCorection core(2);
    MeanBlurKernel kernelBlur;
    kernelBlur*=1.0f;
    GaussianKernel kernelGaussian;
    kernelGaussian*=1.0f;
    VerticalSobelKernel verticalSobel;
    IdentityKernel identityKernel;
    HorizontalSobelKernel horizontalKernel;

    ImageConvolution convolution(horizontalKernel,scaleFunction);
    ImageConvolution convolution2(verticalSobel,scaleFunction);
    //convolution2.process(src,dst);
    //convolution.process(dst,dst);
    //processor.process(dst,dst);
    drawCircle(dst, Point(200, 200), 578, 1);
    drawRectangle(dst,Rectangle(1,2,200,200),100);
    drawLine(dst,Point(15,18),Point(200,201),0);
    core.process(src,dst);
    dst.save("output4.pgm");
    Tests::runAll();
    return 0;
}

