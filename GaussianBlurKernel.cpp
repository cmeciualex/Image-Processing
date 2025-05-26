#include "GaussianBlurKernel.h"

GaussianKernel::GaussianKernel() : Kernel({
    {1.0, 2.0, 1.0},
    {2.0, 4.0, 2.0},
    {1.0, 2.0, 1.0}
}) {}

Kernel& GaussianKernel::operator*=(float scalar) {
    float scaleFactor = scalar / 16.0f;
    for (auto& row : data)
        for (auto& val : row)
            val *= scaleFactor;
    return *this;
}
