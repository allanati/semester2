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

    virtual double getArea() const  // чтобы можно было переопределить производным классом
    {
        std::cout << "Area of the shape: ";
        return 0;
    }
    virtual ~Shape()
    {
        std::cout << "Base destructor called" << std::endl;
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

    ~Circle() {
        std::cout << "Derived (circle) destructor called" << std::endl;
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
    
    ~Triangle()
    {
        std::cout << "Derived (triangle) destructor called" << std::endl;
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

    ~Rectangle()
    {
        std::cout << "Derived (rectangle) destructor called" << std::endl;
    }
};


int main()
{
    Shape* shapes[3] = {};
    shapes[0] = new Circle("yellow", 0, 0, 5);
    shapes[1] = new Triangle("green", 0, 0, 30, 40, 50);
    shapes[2] = new Rectangle("blue", 0, 0, 5, 3);

    for (int i = 0; i < 3; i++)
    {
        std::cout << shapes[i]->getArea() << std::endl;
    }

    for (int i = 0; i < 3; i++)
    {
        delete shapes[i];
    }

    return 0;
}