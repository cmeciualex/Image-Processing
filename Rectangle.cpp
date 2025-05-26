#include "Rectangle.h"

Rectangle::Rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Rectangle::Rectangle(const Point &point1, const Point &point2) {
    this->x = point1.getX();
    this->y = point1.getY();
    this->width = point2.getX() - point1.getX();
    this->height = point2.getY() - point1.getY();
}

unsigned int Rectangle::getHeight() const {
    return this->height;
}

unsigned int Rectangle::getWidth() const {
    return this->width;
}

unsigned int Rectangle::getY() const {
    return this->y;
}

unsigned int Rectangle::getX() const {
    return this->x;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) {
    os<<rectangle.x<<" "<<rectangle.y<<" "<<rectangle.width<<" "<<rectangle.height;
    return os;
}

std::istream& operator>>(std::istream& is, Rectangle& rectangle) {
    is>>rectangle.x>>rectangle.y>>rectangle.width>>rectangle.height;
    return is;
}

Rectangle Rectangle::operator+(const Rectangle& other) const{
    unsigned int newX = this->x + other.x;
    unsigned int newY = this->y + other.y;
    unsigned int newWidth = this->width + other.width;
    unsigned int newHeight = this->height + other.height;

    return Rectangle(newX,newY,newWidth,newHeight);
}

Rectangle Rectangle::operator-(const Rectangle& other) const{
    unsigned int newX = this->x - other.x;
    unsigned int newY = this->y - other.y;
    unsigned int newWidth = this->width - other.width;
    unsigned int newHeight = this->height - other.height;
    return Rectangle(newX,newY,newWidth,newHeight);
}

Rectangle Rectangle::operator&(const Rectangle& other) const {///intersectia
    unsigned int interX = std::max(this->x, other.x);
    unsigned int interY = std::max(this->y, other.y);

    unsigned int thisRight = this->x + this->width;
    unsigned int otherRight = other.x + other.width;
    unsigned int interRight = std::min(thisRight, otherRight);

    unsigned int thisBottom = this->y + this->height;
    unsigned int otherBottom = other.y + other.height;
    unsigned int interBottom = std::min(thisBottom, otherBottom);

    if (interRight <= interX || interBottom <= interY) {
        return Rectangle(0, 0, 0, 0);
    }

    unsigned int interWidth = interRight - interX;
    unsigned int interHeight = interBottom - interY;

    return Rectangle(interX, interY, interWidth, interHeight);
}

Rectangle Rectangle::operator|(const Rectangle& other) const {///reuniunea
    unsigned int uniX = std::min(this->x, other.x);
    unsigned int uniY = std::min(this->y, other.y);

    unsigned int thisRight = this->x + this->width;
    unsigned int otherRight = other.x + other.width;
    unsigned int uniRight = std::max(thisRight, otherRight);

    unsigned int thisBottom = this->y + this->height;
    unsigned int otherBottom = other.y + other.height;
    unsigned int uniBottom = std::max(thisBottom, otherBottom);

    unsigned int uniWidth = uniRight - uniX;
    unsigned int uniHeight = uniBottom - uniY;

    return Rectangle(uniX, uniY, uniWidth, uniHeight);
}
