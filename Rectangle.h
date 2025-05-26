#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Point.h"

/**
 * The Rectangle class represents a rectangle defined by the coordinates of its
 * top-left corner (x, y) and its dimensions (width and height).
 */
class Rectangle {
private:
    unsigned int x; ///< The x-coordinate of the top-left corner.
    unsigned int y; ///< The y-coordinate of the top-left corner.
    unsigned int width; ///< The width of the rectangle.
    unsigned int height; ///< The height of the rectangle.

public:
    /**
     * Default and parameterized constructor.
     * @param x The x-coordinate of the top-left corner (default is 0).
     * @param y The y-coordinate of the top-left corner (default is 0).
     * @param width The width of the rectangle (default is 0).
     * @param height The height of the rectangle (default is 0).
     */
    Rectangle(unsigned int x = 0, unsigned int y = 0, unsigned int width = 0, unsigned int height = 0);

    /**
     * Constructor that creates a rectangle from two points (opposite corners).
     * @param point1 The first point.
     * @param point2 The second point.
     */
    Rectangle(const Point &point1, const Point &point2);

    /**
     * Gets the x-coordinate of the top-left corner.
     * @return The x-coordinate.
     */
    unsigned int getX() const;

    /**
     * Gets the y-coordinate of the top-left corner.
     * @return The y-coordinate.
     */
    unsigned int getY() const;

    /**
     * Gets the width of the rectangle.
     * @return The width.
     */
    unsigned int getWidth() const;

    /**
     * Gets the height of the rectangle.
     * @return The height.
     */
    unsigned int getHeight() const;

    /**
     * Output stream operator for printing the rectangle.
     * @param os Output stream.
     * @param rectangle The rectangle to print.
     * @return Reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle);

    /**
     * Input stream operator for reading the rectangle.
     * @param is Input stream.
     * @param rectangle Rectangle to store the read data.
     * @return Reference to the input stream.
     */
    friend std::istream &operator>>(std::istream &is, Rectangle &rectangle);

    /**
     * Addition operator that combines two rectangles.
     * @param other The other rectangle to add.
     * @return A new rectangle resulting from the combination of the two.
     */
    Rectangle operator+(const Rectangle &other) const;

    /**
     * Subtraction operator that removes the overlapping part with another rectangle.
     * @param other The rectangle to subtract.
     * @return A new rectangle resulting from the subtraction.
     */
    Rectangle operator -(const Rectangle &other) const;

    /**
     * Intersection operator between two rectangles.
     * @param other The rectangle to intersect with.
     * @return The rectangle representing the intersection area.
     */
    Rectangle operator&(const Rectangle &other) const;

    /**
     * Union operator between two rectangles.
     * @param other The rectangle to unite with.
     * @return The rectangle representing the union area.
     */
    Rectangle operator|(const Rectangle &other) const;
};


#endif //RECTANGLE_H
