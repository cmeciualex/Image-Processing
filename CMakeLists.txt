cmake_minimum_required(VERSION 3.28.3)
project(ExtraCredit3)

set(CMAKE_CXX_STANDARD 20)

add_executable(ExtraCredit3 main.cpp
        Image.cpp
        Image.h
        Point.cpp
        Point.h
        Size.cpp
        Size.h
        Rectangle.cpp
        Rectangle.h
        ImageProcessing.h
        BrightnessContrast.cpp
        BrightnessContrast.h
        GammaCorection.cpp
        GammaCorection.h
        ImageConvolution.cpp
        ImageConvolution.h
        Kernel.cpp
        Kernel.h
        IdentityKernel.cpp
        IdentityKernel.h
        MeanBlurKernel.cpp
        MeanBlurKernel.h
        GaussianBlurKernel.cpp
        GaussianBlurKernel.h
        HorizontalSobelKernel.cpp
        HorizontalSobelKernel.h
        VerticalSobelKernel.cpp
        VerticalSobelKernel.h
        Drawing.cpp
        Drawing.h
        Tests.cpp
        Tests.h
)
