#include "HorizontalSobelKernel.h"

HorizontalSobelKernel::HorizontalSobelKernel() : Kernel({
    {1, 2, 1},
    {0, 0, 0},
    {-1, -2, -1}
}) {
}
Kernel& HorizontalSobelKernel::operator*=(float scalar) {
    for (auto& row : data)
        for (auto& val : row)
            val *= scalar;
    return *this;
}