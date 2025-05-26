#ifndef HORIZONTALSOBELKERNEL_H
#define HORIZONTALSOBELKERNEL_H
#include "Kernel.h"


class HorizontalSobelKernel :public Kernel{
public:
    HorizontalSobelKernel();
    Kernel& operator*=(float scalar) override;
};



#endif //HORIZONTALSOBELKERNEL_H
