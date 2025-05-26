/*
 * Image.h
 *
 * This header defines the Image class, which represents a 2D grayscale image.
 * It provides functionalities for loading, saving, modifying, and accessing image pixels,
 * along with scalar and image arithmetic operations, ROI extraction, and memory management.
 */
#ifndef IMAGE_H
#define IMAGE_H
#include <fstream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "Point.h"
#include "Size.h"
#include "Rectangle.h"

class Image {
private:
    /**
     * A 2D dynamic array to store pixel values of the image.
     * Each element is an unsigned char representing a pixel intensity (0-255).
     */
    unsigned char **m_data;
    /**
     * The width of the image in pixels.
     */
    unsigned int m_width;
    /**
     * The height of the image in pixels.
     */
    unsigned int m_height;

public:
    /**
     * Default constructor. Creates an empty image.
     */
    Image();

    /**
     * Constructs an image with the given width and height.
     * @param width Width of the image.
     * @param height Height of the image.
     */
    Image(unsigned int width, unsigned int height);

    /**
     * Copy constructor.
     * @param other The image to copy.
     */
    Image(const Image &other);

    /**
     * Destructor. Releases allocated memory.
     */
    ~Image();

    /**
     * Loads an image from a file.
     * @param imagePath Path to the image file.
     * @return true if successful, false otherwise.
     */
    bool load(const std::string &imagePath);

    /**
     * Saves the image to a file.
     * @param imagePath Path to the destination file.
     * @return true if successful, false otherwise.
     */
    bool save(const std::string &imagePath);

    /**
     * Assignment operator.
     * @param other Image to assign from.
     * @return Reference to the assigned image.
     */
    Image &operator=(const Image &other);

    /**
     * Adds two images pixel by pixel.
     * @param other The image to add.
     * @return The resulting image.
     */
    Image operator+(const Image &other);

    /**
     * Subtracts another image from this image pixel by pixel.
     * @param other The image to subtract.
     * @return The resulting image.
     */
    Image operator-(const Image &other);

    /**
     * Multiplies all pixel values by a scalar.
     * @param scalar Scalar value to multiply with.
     * @return The resulting image.
     */
    Image operator*(unsigned int scalar) const;

    /**
     * Adds a scalar value to all pixel values.
     * @param scalar Scalar value to add.
     * @return The resulting image.
     */
    Image operator+(unsigned int scalar) const;

    /**
     * Subtracts a scalar value from all pixel values.
     * @param scalar Scalar value to subtract.
     * @return The resulting image.
     */
    Image operator-(unsigned int scalar) const;

    /**
    * Returns the width of the image.
    */
    unsigned int getWidth() const;

    /**
     * Returns the height of the image.
     */
    unsigned int getHeight() const;

    /**
     * Extracts a region of interest (ROI) from the image.
     * @param roiImg Output image for the ROI.
     * @param roiRect Rectangle specifying the ROI.
     * @return true if successful, false otherwise.
     */
    bool getROI(Image &roiImg, Rectangle roiRect);

    /**
     * Extracts a region of interest (ROI) using coordinates and size.
     * @param roiImg Output image for the ROI.
     * @param x Top-left x-coordinate.
     * @param y Top-left y-coordinate.
     * @param width Width of the ROI.
     * @param height Height of the ROI.
     * @return true if successful, false otherwise.
     */
    bool getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height); ///ok
    /**
     * Checks if the image is empty.
     */
    bool isEmpty();

    /**
     * Returns the size of the image as a Size object.
     */
    Size getSize();

    /**
     * Accesses a pixel at given coordinates.
     * @param x x-coordinate.
     * @param y y-coordinate.
     * @return Reference to the pixel value.
     */
    unsigned char &at(unsigned int x, unsigned int y) const;

    /**
     * Accesses a pixel at a given point.
     * @param pt A Point object containing x and y coordinates.
     * @return Reference to the pixel value.
     */
    unsigned char &at(Point pt);

    /**
     * Returns a pointer to the beginning of a row.
     * @param y Row index.
     * @return Pointer to the row.
     */
    unsigned char *row(int y);

    /**
     * Releases the memory used by the image.
     */
    void release();

    /**
     * Overloaded stream output operator for printing image info.
     */
    friend std::ostream &operator<<(std::ostream &os, const Image &image);

    /**
     * Creates an image filled with zeros (black).
     * @param width Image width.
     * @param height Image height.
     * @return New image filled with zeros.
     */
    static Image zeros(unsigned int width, unsigned int height);

    /**
     * Creates an image filled with ones (white).
     * @param width Image width.
     * @param height Image height.
     * @return New image filled with ones.
     */
    static Image ones(unsigned int width, unsigned int height);
};


#endif //IMAGE_H
