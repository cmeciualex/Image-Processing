#pragma once
#include "Kernel.h"

class MeanBlurKernel : public Kernel {
public:
    MeanBlurKernel();
    Kernel& operator*=(float scalar) override;
};
