#include "Drawing.h"
#include <cmath>

void drawCircle(Image &img, Point center, int radius, unsigned char color) {
    int x_center = center.getX();
    int y_center = center.getY();
    for (int i = 0; i < img.getHeight(); i++) {
        for (int j = 0; j < img.getWidth(); j++) {
            int dx = j - x_center;
            int dy = i - y_center;
            if (dx * dx + dy * dy <= radius * radius) {
                img.at(j, i) = color;
            }
        }
    }
}

void drawRectangle(Image &img, Rectangle r, unsigned char color) {
    unsigned int leftX = r.getX();
    unsigned int leftY = r.getY();
    img.at(leftX, leftY) = color;
    for (unsigned int i = leftX; i < r.getWidth(); i++)
        for (unsigned int j = leftY; j < r.getHeight(); j++) {
            img.at(i, j) = color;
        }
}

void drawLine(Image &img, Point p1, Point p2, unsigned char color) {
    unsigned int p1X = p1.getX();
    unsigned int p1Y = p1.getY();
    unsigned int p2X = p2.getX();
    unsigned int p2Y = p2.getY();

    int dx = abs((int) (p2X - p1X));
    int dy = abs((int) (p2Y - p1Y));

    int directionX;
    if (p1X < p2X) {
        directionX = 1;
    } else {
        directionX = -1;
    }

    int directionY;
    if (p1Y < p2Y) {
        directionY = 1;
    } else {
        directionY = -1;
    }

    int error = dx - dy;

    while (true) {
        img.at(p1X, p1Y) = color;

        if (p1X == p2X && p1Y == p2Y) {
            break;
        }

        int error2 = 2 * error;

        if (error2 > -dy) {
            error -= dy;
            p1X += directionX;
        }

        if (error2 < dx) {
            error += dx;
            p1Y += directionY;
        }
    }
}
