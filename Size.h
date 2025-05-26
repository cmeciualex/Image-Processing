#ifndef SIZE_H
#define SIZE_H


/**
 * Class Size represents the dimensions of a 2D object with width and height.
 */
class Size {
private:
    unsigned int width; ///< Width dimension.
    unsigned int height; ///< Height dimension.
public:
    /**
     * Constructor to initialize width and height.
     * @param width Width of the object.
     * @param height Height of the object.
     */
    Size(unsigned int width, unsigned int height);

    /**
     * Gets the width.
     * @return The width value.
     */
    unsigned int getWidth();

    /**
     * Gets the height.
     * @return The height value.
     */
    unsigned int getHeight();
};


#endif //SIZE_H
