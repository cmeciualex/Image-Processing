#pragma once
#include "Kernel.h"

class VerticalSobelKernel : public Kernel {
public:
    VerticalSobelKernel();

    Kernel& operator*=(float scalar) override;
};
