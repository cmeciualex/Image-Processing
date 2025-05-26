#pragma once
#include "Kernel.h"

class GaussianKernel : public Kernel {
public:
    GaussianKernel();
    Kernel& operator*=(float scalar) override;
};
