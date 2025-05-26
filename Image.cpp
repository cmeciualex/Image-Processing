#include "Image.h"

#include <iostream>

Image::Image() {
    this->m_height=this->m_width=0;
    m_data=NULL;
};

Image::Image(unsigned int width, unsigned int height) {
    this->m_width = width;
    this->m_height = height;
    m_data = new unsigned char *[this->m_height];
    for (unsigned int i = 0; i < this->m_height; ++i) {
        m_data[i] = new unsigned char[this->m_width];
    }
}

Image::Image(const Image &other) {
    this->m_width = other.m_width;
    this->m_height = other.m_height;
    m_data = new unsigned char *[this->m_height];
    for (unsigned int i = 0; i < this->m_height; i++) {
        m_data[i] = new unsigned char[this->m_width];
        for (unsigned int j = 0; j < this->m_width; j++) {
            this->m_data[i][j] = other.m_data[i][j];
        }
    }
}

Image &Image::operator=(const Image &other) {
    if (this != &other) {
        for (unsigned int i = 0; i < this->m_height; i++) {
            delete [] m_data[i];
        }
        delete [] m_data;
        this->m_width = other.m_width;
        this->m_height = other.m_height;
        m_data = new unsigned char *[this->m_height];
        for (unsigned int i = 0; i < this->m_height; i++) {
            m_data[i] = new unsigned char[this->m_width];
            for (unsigned int j = 0; j < this->m_width; j++) {
                m_data[i][j] = other.m_data[i][j];
            }
        }
    }
    return *this;
}

Image Image::operator+(const Image &other) {
    if (other.m_width != this->m_width || other.m_height != this->m_height) {
        throw std::runtime_error("Invalid dimensions");
    }
    Image result(this->m_width, this->m_height);
    for (unsigned int i = 0; i < this->m_height; i++) {
        for (unsigned int j = 0; j < this->m_width; j++) {
            int val = static_cast<int>(this->m_data[i][j]) + static_cast<int>(other.m_data[i][j]);
            result.m_data[i][j] = static_cast<unsigned char>(std::min(255, val));
        }
    }
    return result;
}


Image Image::operator-(const Image &other) {
    if (other.m_width != this->m_width || other.m_height != this->m_height) {
        throw std::runtime_error("Invalid dimensions");
    }
    Image result(this->m_width, this->m_height);
    for (unsigned int i = 0; i < this->m_height; i++) {
        for (unsigned int j = 0; j < this->m_width; j++) {
            result.m_data[i][j] = abs(this->m_data[i][j] - other.m_data[i][j]);
        }
    }
    return result;
}

Image Image::operator*(unsigned int scalar) const {
    Image result(this->m_width, this->m_height);
    for (unsigned int i = 0; i < this->m_height; i++) {
        for (unsigned int j = 0; j < this->m_width; j++) {
            int val = static_cast<int>(this->m_data[i][j]) * scalar;
            result.m_data[i][j] = static_cast<unsigned char>(std::min(255, val));
        }
    }
    return result;
}


Image Image::operator+(unsigned int scalar) const {
    Image result(this->m_width, this->m_height);
    for (unsigned int i = 0; i < this->m_height; i++) {
        for (unsigned int j = 0; j < this->m_width; j++) {
            unsigned int val = this->m_data[i][j] + scalar;
            if (val > 255) val = 255;
            result.m_data[i][j] = static_cast<unsigned char>(val);
        }
    }
    return result;
}


unsigned int Image::getHeight() const {
    return this->m_height;
}

unsigned int Image::getWidth() const {
    return this->m_width;
}

bool Image::isEmpty() {
    if (this->m_width <= 0 || this->m_height <= 0) {
        return true;
    }
    return false;
}

void Image::release() {
    if (m_data) {
        for (unsigned int i = 0; i < m_height; i++) {
            delete[] m_data[i];
        }
        delete[] m_data;
        m_data = nullptr;
        m_width = 0;
        m_height = 0;
    }
}

Image::~Image() {
    release();
}

unsigned char &Image::at(unsigned int x, unsigned int y) const {
    return this->m_data[y][x];
}

unsigned char &Image::at(Point pt) {
    return m_data[pt.getY()][pt.getX()];
}

unsigned char *Image::row(int y) {
    return m_data[y];
}

Size Image::getSize() {
    unsigned int width = this->m_width;
    unsigned int height = this->m_height;
    return Size(width, height);
}

bool Image::getROI(Image &roiImg, Rectangle roiRect) {
    unsigned int x = roiRect.getX();
    unsigned int y = roiRect.getY();
    unsigned int width = roiRect.getWidth();
    unsigned int height = roiRect.getHeight();

    if (x + width > m_width || y + height > m_height) {
        return false;
    }

    roiImg = Image(width, height);

    for (unsigned int i = 0; i < height; ++i) {
        unsigned char *srcRow = *(m_data + (y + i));
        unsigned char *dstRow = *(roiImg.m_data + i);

        for (unsigned int j = 0; j < width; ++j) {
            *(dstRow + j) = *(srcRow + x + j);
        }
    }

    return true;
}

bool Image::getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    if (x + width > this->m_width || y + height > this->m_height) {
        return false;
    }

    roiImg = Image(width, height);

    for (unsigned int i = 0; i < height; i++) {
        unsigned char *srcRow = *(m_data + (y + i));
        unsigned char *dstRow = *(roiImg.m_data + i);
        for (unsigned int j = 0; j < width; j++) {
            *(dstRow + j) = *(srcRow + (x + j));
        }
    }

    return true;
}

Image Image::zeros(unsigned int width, unsigned int height) {
    Image img(width, height);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            *(*(img.m_data + i) + j) = 0;
        }
    }
    return img;
}

Image Image::ones(unsigned int width, unsigned int height) {
    Image img(width, height);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            *(*(img.m_data + i) + j) = 1;
        }
    }
    return img;
}

bool Image::load(const std::string &imagePath) {
    std::ifstream input(imagePath, std::ios::binary);
    if (!input.is_open()) return false;

    std::string magic;
    input >> magic;
    if (magic != "P2") return false;

    auto skipComments = [&](std::istream &in) {
        in >> std::ws;
        while (in.peek() == '#') {
            std::string commentLine;
            std::getline(in, commentLine);
            in >> std::ws;
        }
    };

    skipComments(input);
    input >> this->m_width >> this->m_height;

    skipComments(input);
    int maxVal;
    input >> maxVal;
    if (maxVal != 255) return false;

    input.get();

    release();
    m_data = new unsigned char *[m_height];
    for (unsigned int i = 0; i < m_height; ++i)
        m_data[i] = new unsigned char[m_width];

    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            int pixel;
            input >> pixel;
            if (!input || pixel < 0 || pixel > 255) return false;
            m_data[i][j] = static_cast<unsigned char>(pixel);
        }
    }
    return true;
}

bool Image::save(const std::string &imagePath) {
    bool ascii = true;
    std::ofstream output(imagePath, std::ios::binary);
    if (!output.is_open()) return false;

    output << "P2\n";
    output << m_width << " " << m_height << "\n";
    output << "255\n";

    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            output << static_cast<int>(m_data[i][j]);
            if (j < m_width - 1) output << " ";
        }
        output << "\n";
    }

    return true;
}


std::ostream &operator<<(std::ostream &os, const Image &image) {
    for (unsigned int i = 0; i < image.getHeight(); i++, os << '\n') {
        for (unsigned int j = 0; j < image.getWidth(); j++) {
            os << std::setw(3) << static_cast<int>(image.m_data[i][j]) << " ";
        }
    }
    return os;
}
