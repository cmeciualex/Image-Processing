#ifndef TESTS_H
#define TESTS_H
#include <cassert>
#include "Image.h"


class Tests {
public:
    static void testConstructor();
    static void testCopyConstructorAndAssignment();
    static void testConstructorAndSize();
    static void testScalarMultiplicationAndAddition();
    static void testAdditionOperator();
    static void testGetROI();
    static void testSubtractionOperator();
    static void testLoadSave();
    static void imageTest();
    static void ConvolutionTest();
    static void GammaCorrectionTest();
    static void testBrightnessContrast();
    static void test_constructor_and_getters();
    static void test_output_operator();
    static void test_input_operator();
    static void PointTests();
    static void test_rectangle_constructor_with_coordinates();
    static void test_rectangle_constructor_with_two_points();
    static void test_rectangle_output_stream_operator_prints_correct_format();
    static void test_rectangle_input_stream_operator_reads_correct_values();
    static void test_rectangle_addition_operator_combines_correctly();
    static void test_rectangle_subtraction_operator_computes_difference();
    static void test_rectangle_intersection_operator_returns_common_area();
    static void test_rectangle_intersection_operator_returns_empty_rectangle_when_no_overlap();
    static void test_rectangle_union_operator_returns_minimal_covering_rectangle();
    static void RectangleTests();
    static void test_drawing_draw_circle_colors_inside_radius();
    static void test_drawing_draw_rectangle_fills_correct_area();
    static void test_drawing_draw_line_diagonal_up_colors_correct_pixels();
    static void test_drawing_draw_line_vertical_colors_correct_pixels();
    static void test_drawing_draw_line_horizontal_colors_correct_pixels();
    static void DrawingTests();
    static void test_KernelConstructor_WithOddDimensions_ShouldSucceed();
    static void test_KernelConstructor_WithEvenDimensions_ShouldThrow();
    static void test_KernelGetters_ReturnCorrectDimensions();
    static void test_KernelAt_ReturnsCorrectElement();
    static void KernelTests();
    static void test_ImageConvolution_ProcessThrowsOnDimensionMismatch();
    static void test_ImageConvolution_ProcessMeanBlurKernel_SmoothsImage();
    static void ConvolutionTests();
    static void runAll();
};


#endif //TESTS_H
