/*
* Drawing.h
 *
 * This header defines a set of drawing utilities for manipulating grayscale images,
 * such as drawing circles, lines, and rectangles using basic geometry.
 */

#ifndef DRAWING_H
#define DRAWING_H
#include "Image.h"
#include "Point.h"
/**
 * Draws a filled circle on the image.
 *
 * @param img Reference to the image where the circle will be drawn.
 * @param center The center point of the circle.
 * @param radius The radius of the circle.
 * @param color Grayscale value (0–255) used to fill the circle.
 */
void drawCircle(Image &img, Point center, int radius, unsigned char color);

/**
 * Draws a straight line between two points on the image using Bresenham's algorithm.
 *
 * @param img Reference to the image where the line will be drawn.
 * @param p1 The starting point of the line.
 * @param p2 The ending point of the line.
 * @param color Grayscale value (0–255) used for the line.
 */
void drawLine(Image &img, Point p1, Point p2, unsigned char color);

/**
 * Draws a filled rectangle on the image based on a Rectangle object.
 *
 * @param img Reference to the image where the rectangle will be drawn.
 * @param r The rectangle object specifying top-left corner and size.
 * @param color Grayscale value (0–255) used to fill the rectangle.
 */
void drawRectangle(Image &img, Rectangle r, unsigned char color);

/**
 * Draws a filled rectangle on the image based on top-left and bottom-right points.
 *
 * @param img Reference to the image where the rectangle will be drawn.
 * @param tl Top-left corner of the rectangle.
 * @param br Bottom-right corner of the rectangle.
 * @param color Grayscale value (0–255) used to fill the rectangle.
 */
void drawRectangle(Image &img, Point tl, Point br, unsigned char color);

#endif //DRAWING_H
