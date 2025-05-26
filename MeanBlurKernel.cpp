#include "MeanBlurKernel.h"

MeanBlurKernel::MeanBlurKernel() : Kernel({
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0}
}) {}

Kernel& MeanBlurKernel::operator*=(float scalar) {
    float scaleFactor = scalar / 9.0f;
    for (auto& row : data)
        for (auto& val : row)
            val *= scaleFactor;
    return *this;
}

