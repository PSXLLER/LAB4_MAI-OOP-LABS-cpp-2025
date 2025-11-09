#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include "point.hpp"
#include "triangle.hpp"
#include "hexagon.hpp"
#include "octagon.hpp"
#include "array.hpp"
#include "polygon_utils.hpp"

// =======================================================
// 🔹 Polygon utils
// =======================================================
TEST(PolygonUtilsTest, SquareAreaAndCenter) {
    Point<int> pts[] = {{0,0},{2,0},{2,2},{0,2}};
    EXPECT_NEAR(polygon_area(pts,4), 4.0, 1e-6);
    auto c = polygon_center(pts,4);
    EXPECT_NEAR(c.x, 1.0, 1e-6);
    EXPECT_NEAR(c.y, 1.0, 1e-6);
}

TEST(PolygonUtilsTest, TriangleAreaAndCenter) {
    Point<double> pts[] = {{0,0},{4,0},{0,3}};
    EXPECT_NEAR(polygon_area(pts,3), 6.0, 1e-6);
    auto c = polygon_center(pts,3);
    EXPECT_NEAR(c.x, 4.0/3.0, 1e-6);
    EXPECT_NEAR(c.y, 1.0, 1e-6);
}

// =======================================================
// 🔹 Triangle
// =======================================================
TEST(TriangleTest, AreaAndCenter) {
    Triangle<double> t({0,0},{4,0},{0,3});
    EXPECT_NEAR(t.area(), 6.0, 1e-6);
    auto c = t.center();
    EXPECT_NEAR(c.x, 4.0/3.0, 1e-6);
    EXPECT_NEAR(c.y, 1.0, 1e-6);
}

TEST(TriangleTest, EqualityOperator) {
    Triangle<int> t1({0,0},{1,0},{0,1});
    Triangle<int> t2({0,0},{1,0},{0,1});
    Triangle<int> t3({1,1},{2,2},{3,3});
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

// =======================================================
// 🔹 Hexagon
// =======================================================
TEST(HexagonTest, AreaPositiveAndCenter) {
    std::array<Point<double>,6> pts = {{{0,0},{2,0},{3,2},{2,4},{0,4},{-1,2}}};
    Hexagon<double> h(pts);
    EXPECT_GT(h.area(), 0.0);
    auto c = h.center();
    EXPECT_NEAR(c.x, 1.0, 0.5);
    EXPECT_NEAR(c.y, 2.0, 0.5);
}

TEST(HexagonTest, EqualityOperator) {
    std::array<Point<int>,6> pts = {{{0,0},{1,0},{2,1},{2,2},{1,3},{0,2}}};
    Hexagon<int> h1(pts);
    Hexagon<int> h2(pts);
    EXPECT_TRUE(h1 == h2);
}

TEST(HexagonTest, InvalidConstructorThrows) {
    EXPECT_THROW((Hexagon<int>({Point<int>(0,0), Point<int>(1,1)})), std::invalid_argument);
}

// =======================================================
// 🔹 Octagon
// =======================================================
TEST(OctagonTest, AreaPositiveAndCenter) {
    std::array<Point<double>,8> pts = {{{0,0},{2,0},{3,1},{3,3},{2,4},{0,4},{-1,3},{-1,1}}};
    Octagon<double> o(pts);
    EXPECT_GT(o.area(), 0.0);
    auto c = o.center();
    EXPECT_NEAR(c.x, 1.0, 0.5);
    EXPECT_NEAR(c.y, 2.0, 0.5);
}

TEST(OctagonTest, EqualityOperator) {
    std::array<Point<int>,8> pts = {{{0,0},{2,0},{3,1},{3,3},{2,4},{0,4},{-1,3},{-1,1}}};
    Octagon<int> o1(pts);
    Octagon<int> o2(pts);
    EXPECT_TRUE(o1 == o2);
}

TEST(OctagonTest, InvalidConstructorThrows) {
    EXPECT_THROW((Octagon<int>({Point<int>(0,0), Point<int>(1,1), Point<int>(2,2)})), std::invalid_argument);
}

// =======================================================
// 🔹 DummyFigure (для тестов Array)
// =======================================================
class DummyFigure : public Figure<double> {
public:
    double a, cx, cy;
    DummyFigure(double _a, double _cx, double _cy)
        : a(_a), cx(_cx), cy(_cy) {}
    double area() const override { return a; }
    Point<double> center() const override { return {cx, cy}; }
};

// =======================================================
// 🔹 Array tests
// =======================================================
TEST(ArrayTest, DefaultConstructor) {
    Array<Figure<double>> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
}

TEST(ArrayTest, ConstructorWithCapacity) {
    Array<Figure<double>> arr(5);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 5);
}

TEST(ArrayTest, PushBackIncreasesSize) {
    Array<Figure<double>> arr;
    arr.push_back(std::make_shared<DummyFigure>(1.0, 1.0, 1.0));
    EXPECT_EQ(arr.size(), 1);
    EXPECT_GE(arr.capacity(), 1);
}

TEST(ArrayTest, ReallocationWorks) {
    Array<Figure<double>> arr;
    for (int i = 0; i < 10; ++i)
        arr.push_back(std::make_shared<DummyFigure>(i, i, i));
    EXPECT_EQ(arr.size(), 10);
    EXPECT_GE(arr.capacity(), 10);
}

TEST(ArrayTest, TotalAreaCalculation) {
    Array<Figure<double>> arr;
    arr.push_back(std::make_shared<DummyFigure>(2.0, 0, 0));
    arr.push_back(std::make_shared<DummyFigure>(3.0, 0, 0));
    EXPECT_NEAR(arr.total_area(), 5.0, 1e-6);
}

TEST(ArrayTest, EraseRemovesElement) {
    Array<Figure<double>> arr;
    arr.push_back(std::make_shared<DummyFigure>(1.0, 0, 0));
    arr.push_back(std::make_shared<DummyFigure>(2.0, 0, 0));
    arr.erase(0);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_NEAR(arr.total_area(), 2.0, 1e-6);
}

TEST(ArrayTest, EraseOutOfRangeThrows) {
    Array<Figure<double>> arr;
    EXPECT_THROW(arr.erase(0), std::out_of_range);
}

TEST(ArrayTest, ClearResetsArray) {
    Array<Figure<double>> arr;
    arr.push_back(std::make_shared<DummyFigure>(10.0, 0, 0));
    arr.clear();
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
}

TEST(ArrayTest, OperatorIndexValid) {
    Array<Figure<double>> arr;
    auto fig = std::make_shared<DummyFigure>(5.0, 2.0, 3.0);
    arr.push_back(fig);
    EXPECT_EQ(arr[0], fig);
}

TEST(ArrayTest, OperatorIndexOutOfRangeThrows) {
    Array<Figure<double>> arr;
    EXPECT_THROW(arr[0], std::out_of_range);
}

TEST(ArrayTest, PrintCentersOutputContainsValues) {
    Array<Figure<double>> arr;
    arr.push_back(std::make_shared<DummyFigure>(1.0, 2.5, 3.5));
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    arr.print_centers();
    std::cout.rdbuf(old_cout);
    std::string out = oss.str();
    EXPECT_NE(out.find("2.5"), std::string::npos);
    EXPECT_NE(out.find("3.5"), std::string::npos);
}
