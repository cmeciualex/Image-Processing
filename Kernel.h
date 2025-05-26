/*
* Kernel.h
 *
 * This header defines the Kernel class, representing a 2D convolution kernel
 * with odd dimensions and float values.
 */
#ifndef KERNEL_H
#define KERNEL_H
/**
 * Kernel represents a 2D convolution kernel with float elements.
 * The kernel dimensions (width and height) must be odd numbers.
 */
#include <vector>
#include <stdexcept>
class Kernel {
protected:
    std::vector<std::vector<float> > data; ///< 2D vector storing kernel values.
    unsigned int width; ///< Kernel width (number of columns).
    unsigned int height; ///< Kernel height (number of rows).

public:
    /**
     * Constructs a Kernel from a 2D vector of floats.
     * @param d 2D vector representing kernel data.
     * @throws std::invalid_argument if width or height is even.
     */
    Kernel(const std::vector<std::vector<float> > &d);

    /**
     * Returns the kernel width (number of columns).
     * @return Kernel width.
     */
    unsigned int getWidth() const;

    /**
     * Returns the kernel height (number of rows).
     * @return Kernel height.
     */
    unsigned int getHeight() const;

    /**
     * Returns the kernel value at position (x, y).
     * @param x Horizontal index (column).
     * @param y Vertical index (row).
     * @return Kernel element at (x, y).
     */
    float at(unsigned int x, unsigned int y) const;

    /**
     * Multiplies all kernel elements by a scalar (in-place).
     * Can be overridden in derived classes.
     * @param scalar The factor to multiply each element by.
     * @return Reference to the updated Kernel object.
     */
    virtual Kernel &operator*=(float scalar);
};

#endif // KERNEL_H
