#include "Point.h"

Point::Point(unsigned int x, unsigned int y) {
    this->x = x;
    this->y=y;
}

unsigned int Point::getX() const {
    return this->x;
}

unsigned int Point::getY() const {
    return this->y;
}


std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& point) {
    is >> point.x >> point.y;
    return is;
}
