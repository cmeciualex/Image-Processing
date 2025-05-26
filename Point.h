/*
* Point.h
 *
 * This header defines the Point class, which represents a 2D point
 * with unsigned integer coordinates (x, y).
 */
#ifndef POINT_H
#define POINT_H

#include <iostream>
/**
 * Point represents a coordinate in 2D space with unsigned integer values.
 */
class Point {
private:
    unsigned int x; ///< The x-coordinate of the point.
    unsigned int y; ///< The y-coordinate of the point.

public:
    /**
    * Constructor for Point.
    * @param x The x-coordinate (default 0).
    * @param y The y-coordinate (default 0).
    */
    Point(unsigned int x = 0, unsigned int y = 0);

    /**
     * Gets the x-coordinate of the point.
     * @return x-coordinate.
     */
    unsigned int getX() const;

    /**
     * Gets the y-coordinate of the point.
     * @return y-coordinate.
     */
    unsigned int getY() const;

    /**
    * Stream insertion operator to output the point in the format (x, y).
    * @param os Output stream.
    * @param point Point to output.
    * @return Reference to the output stream.
    */

    friend std::ostream &operator<<(std::ostream &os, const Point &point);

    /**
     * Stream extraction operator to input the point coordinates.
     * @param is Input stream.
     * @param point Point to store input values.
     * @return Reference to the input stream.
     */
    friend std::istream &operator>>(std::istream &is, Point &point);
};

#endif // POINT_H
