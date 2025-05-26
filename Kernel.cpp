#include "Kernel.h"

Kernel::Kernel(const std::vector<std::vector<float>>& d) : data(d), height(d.size()), width(d[0].size()) {
    if (width % 2 == 0 || height % 2 == 0) {
        throw std::invalid_argument("Kernel dimensions should be odd");
    }

}

unsigned int Kernel::getWidth() const {
    return width;
}

unsigned int Kernel::getHeight() const {
    return height;
}

float Kernel::at(unsigned int x, unsigned int y) const {
    return data[y][x];
}

Kernel& Kernel::operator*=(float scalar) {
    return *this;
}