#include <cassert>
#include <iostream>
#include <stdexcept>
#include "Image.h"
#include "Tests.h"
#include "Point.h"
#include "GammaCorection.h"
#include "ImageConvolution.h"
#include "Kernel.h"
#include <cmath>

#include "BrightnessContrast.h"
#include "Drawing.h"
#include "IdentityKernel.h"
#include "MeanBlurKernel.h"

auto clampScale = [](float val) -> unsigned char {
    int mapped = static_cast<int>((val + 1020.0f) * 255.0f / 2040.0f);
    if (mapped < 0) mapped = 0;
    if (mapped > 255) mapped = 255;
    return static_cast<unsigned char>(mapped);
};
void Tests:: testConstructorAndSize() {
    Image img1;
    assert(img1.getWidth() == 0 && img1.getHeight() == 0);
    assert(img1.isEmpty());

    Image img2(5, 7);
    assert(img2.getWidth() == 5);
    assert(img2.getHeight() == 7);
    assert(!img2.isEmpty());

}

void Tests::testCopyConstructorAndAssignment() {
    Image img1(3, 3);

    Image img2 = img1;
    for (unsigned int i = 0; i < img2.getHeight(); ++i)
        for (unsigned int j = 0; j < img2.getWidth(); ++j)
            assert(img2.at(i, j) == img1.at(i, j));
    Image img3;
    img3 = img1;
    for (unsigned int i = 0; i < img3.getHeight(); ++i)
        for (unsigned int j = 0; j < img3.getWidth(); ++j)
            assert(img3.at(j, i) == img1.at(j, i));
}

void Tests::testAdditionOperator() {
    Image img1(2, 2);
    img1.at(0, 0) = 10;
    img1.at(1, 0) = 20;
    img1.at(0, 1) = 30;
    img1.at(1, 1) = 40;

    Image img2(2, 2);
    img2.at(0, 0) = 5;
    img2.at(1, 0) = 15;
    img2.at(0, 1) = 25;
    img2.at(1, 1) = 35;

    Image imgSum = img1 + img2;
    assert(imgSum.at(0, 0) == 15);
    assert(imgSum.at(1, 0) == 35);
    assert(imgSum.at(0, 1) == 55);
    assert(imgSum.at(1, 1) == 75);

    img1.at(0, 0) = 250;
    img2.at(0, 0) = 10;
    imgSum = img1 + img2;
    assert(imgSum.at(0, 0) == 255);

    Image img3(1, 1);
    try {
        Image imgErr = img1 + img3;
        assert(false);
    } catch (const std::runtime_error &) {
    }
}

void Tests::testSubtractionOperator() {
    Image img1(2, 2);
    img1.at(0, 0) = 50;
    img1.at(1, 0) = 60;
    img1.at(0, 1) = 70;
    img1.at(1, 1) = 80;

    Image img2(2, 2);
    img2.at(0, 0) = 30;
    img2.at(1, 0) = 60;
    img2.at(0, 1) = 90;
    img2.at(1, 1) = 40;

    Image imgDiff = img1 - img2;
    assert(imgDiff.at(0, 0) == 20);
    assert(imgDiff.at(1, 0) == 0);
    assert(imgDiff.at(0, 1) == 20);
    assert(imgDiff.at(1, 1) == 40);

}

void Tests::testScalarMultiplicationAndAddition() {
    Image img(2, 2);
    img.at(0, 0) = 10;
    img.at(1, 0) = 20;
    img.at(0, 1) = 30;
    img.at(1, 1) = 40;

    Image imgMul = img * 5;
    assert(imgMul.at(0, 0) == 50);
    assert(imgMul.at(1, 0) == 100);
    assert(imgMul.at(0, 1) == 150);
    assert(imgMul.at(1, 1) == 200);

    img.at(0, 0) = 60;
    Image imgMulClamp = img * 5;
    assert(imgMulClamp.at(0, 0) == 255);

    Image imgAdd = img + 10;
    assert(imgAdd.at(0, 0) == 70);
    assert(imgAdd.at(1, 1) == 50);

    img.at(0, 0) = 250;
    Image imgAddClamp = img + 10;
    assert(imgAddClamp.at(0, 0) == 255);

}

void Tests::testGetROI() {
    Image img(5, 5);
    for (unsigned int i = 0; i < 5; ++i)
        for (unsigned int j = 0; j < 5; ++j)
            img.at(j, i) = (i * 5 + j);

    Image roi;
    Rectangle rect(1, 1, 3, 3);
    bool ok = img.getROI(roi, rect);
    assert(ok);
    assert(roi.getWidth() == 3 && roi.getHeight() == 3);
    assert(roi.at(0, 0) == img.at(1, 1));
    assert(roi.at(2, 2) == img.at(3, 3));

    Rectangle rectBad(4, 4, 3, 3);
    ok = img.getROI(roi, rectBad);
    assert(!ok);

}

void Tests::testLoadSave() {
    Image img(2, 2);
    img.at(0, 0) = 10;
    img.at(1, 0) = 20;
    img.at(0, 1) = 30;
    img.at(1, 1) = 40;

    const std::string filename = "test.pgm";
    bool saved = img.save(filename);
    assert(saved);

    Image imgLoaded;
    bool loaded = imgLoaded.load(filename);
    assert(loaded);
    assert(imgLoaded.getWidth() == img.getWidth());
    assert(imgLoaded.getHeight() == img.getHeight());
    for (unsigned int i = 0; i < imgLoaded.getHeight(); ++i)
        for (unsigned int j = 0; j < imgLoaded.getWidth(); ++j)
            assert(imgLoaded.at(j, i) == img.at(j, i));

}

void Tests::imageTest() {
    testConstructorAndSize();
    testCopyConstructorAndAssignment();
    testAdditionOperator();
    testSubtractionOperator();
    testScalarMultiplicationAndAddition();
    testGetROI();
    testLoadSave();
}

void Tests::GammaCorrectionTest() {
    Image src(2, 2);
    src.at(0, 0) = 0;
    src.at(1, 0) = 64;
    src.at(0, 1) = 128;
    src.at(1, 1) = 255;

    Image dst(2, 2);

    float gammaValue = 2.0f;
    GammaCorection gc(gammaValue);

    gc.process(src, dst);


    auto expected = [&](unsigned char input) -> unsigned char {
        float normalized = input / 255.0f;
        float corrected = std::pow(normalized, gammaValue);
        int val = static_cast<int>(corrected * 255.0f + 0.5f);
        if (val > 255) val = 255;
        if (val < 0) val = 0;
        return static_cast<unsigned char>(val);
    };

    assert(dst.at(0, 0) == expected(0));
    assert(dst.at(1, 0) == expected(64));
    assert(dst.at(0, 1) == expected(128));
    assert(dst.at(1, 1) == expected(255));

    std::cout << "testGammaCorrection passed\n";
}

void Tests::testBrightnessContrast() {
    Image src(2, 2);
    src.at(0, 0) = 0;
    src.at(1, 0) = 100;
    src.at(0, 1) = 150;
    src.at(1, 1) = 255;

    Image dst(2, 2);

    float alpha = 1.5f;
    float beta = -20;
    BrightnessContrast bc(alpha, beta);

    bc.process(src, dst);

    auto expected = [&](unsigned char input) -> unsigned char {
        int val = static_cast<int>(alpha * input + beta);
        if (val > 255) val = 255;
        if (val < 0) val = 0;
        return static_cast<unsigned char>(val);
    };

    auto approxEqual = [](unsigned char a, unsigned char b, int tolerance = 1) {
        return std::abs(static_cast<int>(a) - static_cast<int>(b)) <= tolerance;
    };

    assert(approxEqual(dst.at(0, 0), expected(0)));
    assert(approxEqual(dst.at(1, 0), expected(100)));
    assert(approxEqual(dst.at(0, 1), expected(150)));
    assert(approxEqual(dst.at(1, 1), expected(255)));

    std::cout << "testBrightnessContrast passed\n";
}

void Tests::test_constructor_and_getters() {
    Point p(10, 20);
    assert(p.getX() == 10);
    assert(p.getY() == 20);
}

void Tests::test_output_operator() {
    Point p(5, 15);
    std::ostringstream out;
    out << p;
    assert(out.str() == "(5, 15)");
}

void Tests::test_input_operator() {
    Point p(0, 0);
    std::istringstream in("7 9");
    in >> p;
    assert(p.getX() == 7);
    assert(p.getY() == 9);
}

void Tests::PointTests() {
    test_constructor_and_getters();
    test_output_operator();
    test_input_operator();
    std::cout<<"testPoint passed\n";
}

void Tests::test_rectangle_constructor_with_coordinates() {
    Rectangle rect(10, 20, 30, 40);
    assert(rect.getX() == 10);
    assert(rect.getY() == 20);
    assert(rect.getWidth() == 30);
    assert(rect.getHeight() == 40);
}

void Tests::test_rectangle_constructor_with_two_points() {
    Point topLeft(5, 10);
    Point bottomRight(15, 30);
    Rectangle rect(topLeft, bottomRight);
    assert(rect.getX() == 5);
    assert(rect.getY() == 10);
    assert(rect.getWidth() == 10);
    assert(rect.getHeight() == 20);
}

void Tests::test_rectangle_output_stream_operator_prints_correct_format() {
    Rectangle rect(1, 2, 3, 4);
    std::ostringstream out;
    out << rect;
    assert(out.str() == "1 2 3 4");
}

void Tests::test_rectangle_input_stream_operator_reads_correct_values() {
    Rectangle rect(0, 0, 0, 0);
    std::istringstream in("11 12 13 14");
    in >> rect;
    assert(rect.getX() == 11);
    assert(rect.getY() == 12);
    assert(rect.getWidth() == 13);
    assert(rect.getHeight() == 14);
}

void Tests::test_rectangle_addition_operator_combines_correctly() {
    Rectangle rect1(1, 2, 3, 4);
    Rectangle rect2(5, 6, 7, 8);
    Rectangle result = rect1 + rect2;
    assert(result.getX() == 6);
    assert(result.getY() == 8);
    assert(result.getWidth() == 10);
    assert(result.getHeight() == 12);
}

void Tests::test_rectangle_subtraction_operator_computes_difference() {
    Rectangle rect1(10, 20, 30, 40);
    Rectangle rect2(1, 2, 3, 4);
    Rectangle result = rect1 - rect2;
    assert(result.getX() == 9);
    assert(result.getY() == 18);
    assert(result.getWidth() == 27);
    assert(result.getHeight() == 36);
}

void Tests::test_rectangle_intersection_operator_returns_common_area() {
    Rectangle rect1(10, 10, 20, 20);
    Rectangle rect2(15, 15, 30, 30);
    Rectangle intersection = rect1 & rect2;
    assert(intersection.getX() == 15);
    assert(intersection.getY() == 15);
    assert(intersection.getWidth() == 15);
    assert(intersection.getHeight() == 15);
}

void Tests::test_rectangle_intersection_operator_returns_empty_rectangle_when_no_overlap() {
    Rectangle rect1(0, 0, 10, 10);
    Rectangle rect2(20, 20, 5, 5);
    Rectangle intersection = rect1 & rect2;
    assert(intersection.getWidth() == 0);
    assert(intersection.getHeight() == 0);
}

void Tests::test_rectangle_union_operator_returns_minimal_covering_rectangle() {
    Rectangle rect1(5, 5, 10, 10);
    Rectangle rect2(15, 15, 10, 10);
    Rectangle unionRect = rect1 | rect2;
    assert(unionRect.getX() == 5);
    assert(unionRect.getY() == 5);
    assert(unionRect.getWidth() == 20);
    assert(unionRect.getHeight() == 20);
}

void Tests::RectangleTests() {
    test_rectangle_constructor_with_coordinates();
    test_rectangle_constructor_with_two_points();
    test_rectangle_output_stream_operator_prints_correct_format();
    test_rectangle_input_stream_operator_reads_correct_values();
    test_rectangle_addition_operator_combines_correctly();
    test_rectangle_subtraction_operator_computes_difference();
    test_rectangle_intersection_operator_returns_common_area();
    std::cout<<"rectangleTests passed\n";
}

void Tests::test_drawing_draw_circle_colors_inside_radius() {
    Image img(100, 100);
    Point center(50, 50);
    int radius = 10;
    unsigned char color = 255;

    drawCircle(img, center, radius, color);

    assert(img.at(50, 50) == color);

    assert(img.at(60, 50) == color);
    assert(img.at(70, 50) == 0);
}

void Tests::test_drawing_draw_rectangle_fills_correct_area() {
    Image img(100, 100);
    Rectangle r(10, 10, 20, 20);
    unsigned char color = 100;

    drawRectangle(img, r, color);

    assert(img.at(10, 10) == color);
    assert(img.at(15, 15) == color);
    assert(img.at(30, 30) == 0);
}

void Tests::test_drawing_draw_line_diagonal_up_colors_correct_pixels() {
    Image img(20, 20);
    Point start(5, 5);
    Point end(15, 15);
    unsigned char color = 200;

    drawLine(img, start, end, color);

    assert(img.at(5, 5) == color);
    assert(img.at(10, 10) == color);
    assert(img.at(15, 15) == color);
}

void Tests::test_drawing_draw_line_vertical_colors_correct_pixels() {
    Image img(10, 20);
    Point top(5, 2);
    Point bottom(5, 10);
    unsigned char color = 150;

    drawLine(img, top, bottom, color);

    for (int y = 2; y <= 10; ++y) {
        assert(img.at(5, y) == color);
    }
}

void Tests::test_drawing_draw_line_horizontal_colors_correct_pixels() {
    Image img(20, 10);
    Point left(2, 5);
    Point right(10, 5);
    unsigned char color = 77;

    drawLine(img, left, right, color);

    for (int x = 2; x <= 10; ++x) {
        assert(img.at(x, 5) == color);
    }
}

void Tests::DrawingTests() {
    test_drawing_draw_line_vertical_colors_correct_pixels();
    test_drawing_draw_line_horizontal_colors_correct_pixels();
    test_drawing_draw_line_vertical_colors_correct_pixels();
    test_drawing_draw_line_horizontal_colors_correct_pixels();
    test_drawing_draw_line_vertical_colors_correct_pixels();
    std::cout<<"drawingTests passed\n";
}

void Tests::test_KernelConstructor_WithOddDimensions_ShouldSucceed() {
    std::vector<std::vector<float>> kernelData = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    Kernel k(kernelData);
    assert(k.getWidth() == 3);
    assert(k.getHeight() == 3);
}

void Tests::test_KernelConstructor_WithEvenDimensions_ShouldThrow() {
    bool exceptionThrown = false;
    try {
        std::vector<std::vector<float>> invalidData = {
            {1, 2},
            {3, 4}
        };
        Kernel k(invalidData);
    } catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void Tests::test_KernelGetters_ReturnCorrectDimensions() {
    std::vector<std::vector<float>> data = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    Kernel k(data);
    assert(k.getWidth() == 3);
    assert(k.getHeight() == 3);
}

void Tests::test_KernelAt_ReturnsCorrectElement() {
    std::vector<std::vector<float>> data = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}
    };
    Kernel k(data);
    assert(k.at(0, 0) == 10);
    assert(k.at(2, 1) == 60);
    assert(k.at(1, 2) == 80);
}

void Tests::KernelTests() {
    test_KernelGetters_ReturnCorrectDimensions();
    test_KernelAt_ReturnsCorrectElement();
    test_KernelConstructor_WithOddDimensions_ShouldSucceed();
    test_KernelConstructor_WithEvenDimensions_ShouldThrow();
    std::cout<<"KernelTests passed\n";
}

void Tests::test_ImageConvolution_ProcessThrowsOnDimensionMismatch() {
    IdentityKernel kernel;
    ImageConvolution conv(kernel, clampScale);

    Image src(5, 5);
    Image dst(4, 5);  // Different width
    bool exceptionThrown = false;
    try {
        conv.process(src, dst);
    } catch (const std::runtime_error& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void Tests::test_ImageConvolution_ProcessMeanBlurKernel_SmoothsImage() {
    MeanBlurKernel kernel;
    kernel *= 1.0f;

    ImageConvolution conv(kernel, clampScale);

    Image src(4,3);
    Image dst;
    unsigned char pattern[3][4] = {
        {0, 0, 0,1},
        {0, 255, 0,1},
        {0, 0, 0,1},
    };
    unsigned char result[3][4]={
        {131,131,131,127},
        {131,131,131,127},
        {131,131,131,127},
    };
    for (unsigned int x = 0; x < 3; ++x)
        for (unsigned int y = 0; y < 4; ++y)
            src.at(y, x) = pattern[x][y];
    dst=src;
    conv.process(src, dst);
    for (unsigned int x=0;x<3;x++)
        for (unsigned int y=0;y<4;y++) {
            assert(dst.at(y, x) == result[x][y]);
        }

}



void Tests::ConvolutionTests() {
    test_ImageConvolution_ProcessThrowsOnDimensionMismatch();
    test_ImageConvolution_ProcessMeanBlurKernel_SmoothsImage();
    std::cout<<"ConvolutionTests passed\n";
}

void Tests:: runAll() {
    imageTest();
    testBrightnessContrast();
    GammaCorrectionTest();
    PointTests();
    RectangleTests();
    DrawingTests();
    KernelTests();
    ConvolutionTests();
    std::cout << "All tests passed\n";
}


