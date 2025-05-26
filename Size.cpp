#include "Size.h"

Size::Size(unsigned int width, unsigned int height) {
    this->width=width;
    this->height=height;
}

unsigned int Size::getWidth() {
    return width;
}

unsigned int Size::getHeight() {
    return height;
}