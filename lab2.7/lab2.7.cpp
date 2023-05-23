#include <iostream>

/*
Используя наследование и полиморфизм, напишите программу, которая работает с геометрическими фигурами:
1.	Треугольник
2.	Прямоугольник
3.	Круг
Программа должна хранить координаты и размеры фигуры, цвет, уметь вычислять площадь фигуры.
Продемонстрируйте, как ваша программа будет выводить на экран площади всех фигур.
*/

class Shape 
{
    private:
        std::string Color;
        double X, Y;

    public:
        Shape(const std::string& color, double x, double y) : Color(color), X(x), Y(y) {};

        virtual double getArea() const {      // чтобы можно было переопределить производным классом
            std::cout << "Area of the shape: ";
            return 0;
        }
};

class Circle : public Shape 
{
    private:
        double Radius;

    public:
        Circle(const std::string& color, double x, double y, double radius) : Shape(color, x, y), Radius(radius) {}

        double getArea() const override {
            std::cout << "Area of the circle: ";
            return acos(-1) * Radius * Radius;
        }
};

class Triangle : public Shape 
{
    private:
        double FirstSide, SecondSide, ThirdSide;

    public:
        Triangle(const std::string& color, double x, double y, double firstSide, double secondSide, double thirdSide) : 
            Shape(color, x, y), FirstSide(firstSide), SecondSide(secondSide), ThirdSide(thirdSide) {}

        double getArea() const override {
            std::cout << "Area of the triangle: ";
            double p = (FirstSide + SecondSide + ThirdSide) / 2;
            return sqrt(p * (p - FirstSide) * (p - SecondSide) * (p - ThirdSide));
        }
};

class Rectangle : public Shape 
{
private:
    double Width, Height;

public:
    Rectangle(const std::string& color, double x, double y, double width, double height) : Shape(color, x, y), Width(width), Height(height) {}
    double getArea() const override {
        std::cout << "Area of the rectangle: ";
        return Width * Height;
    }
};


int main()
{
    Circle ob1("yellow", 0, 0, 5);
    std::cout << ob1.getArea() << std::endl;

    Triangle ob2("green", 0, 0, 30, 40, 50);
    std::cout << ob2.getArea() << std::endl;

    Rectangle ob3("blue", 0, 0, 5, 3);
    std::cout << ob3.getArea() << std::endl;

    return 0;
}