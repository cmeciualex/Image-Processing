#include "VerticalSobelKernel.h"

VerticalSobelKernel::VerticalSobelKernel() : Kernel({
    {-1.0, 0.0, 1.0},
    {-2.0, 0.0, 2.0},
    {-1.0, 0.0, 1.0}
}) {}

Kernel& VerticalSobelKernel::operator*=(float scalar) {
    for (auto& row : data)
        for (auto& val : row)
            val *= scalar;
    return *this;
}



