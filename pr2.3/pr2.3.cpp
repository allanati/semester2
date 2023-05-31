/*
Реализуйте класс KinematicSolver.
Предусмотрите возможность задания длин звеньев L1 и L2,
получения углов alpha и beta, функцию Solve(x,y),
которая будет рассчитывать углы по заданным координатам.
*/


#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>


// число пи это обратный косинус от -1
const double PI = acos(-1);

class KinematicSolver {
private:
    double m_alpha; 
    double m_beta;  
    double m_L1; // длина звена L1
    double m_L2; // длина звена L2

public:
    KinematicSolver(double L1, double L2) : m_L1(L1), m_L2(L2), m_alpha(0.0), m_beta(0.0) {}

    // вычисление углов alpha и beta
    void Solve(double x, double y) {
        // проведём отрезок B, соединяющий начало координат O с заданной точкой (x, y). По теореме Пифагора длина отрезка B:
        double B = sqrt(x * x + y * y);

        // сторона треугольника меньше суммы двух других его сторон, иначе - неверные координаты
        if (!(B < m_L1 + m_L2 && x > 0 && y > 0)) {
            return;
        }

        // обозначим Q1 угол между осью OX и отрезком B, а Q2 угол между отрезком B и звеном L1
        // обозначим Q2 угол между отрезком B и звеном L1

        // найдем Q1 через обратный тангенс y/x
        double Q1 = std::atan(y / x);

        // найдем Q2 при помощи теоремы косинусов
        double Q2 = std::acos((m_L1 * m_L1 - m_L2 * m_L2 + B * B) / (2.0 * B * m_L1));

        m_alpha = Q1 - Q2;

        // найдём beta при помощи теоремы косинусов
        m_beta = PI - std::acos(
            (m_L1 * m_L1 + m_L2 * m_L2 - B * B) /
            (2 * m_L1 * m_L2));
    }

    double L1() {
        return m_L1;
    }

    double L2() {
        return m_L2;
    }

    // возвращает угол alpha в радианах
    double alpha() const {
        return m_alpha;
    }

    // возвращает угол beta в радианах
    double beta() const {
        return m_beta;
    }
};

// класс, который хранит координаты точки и имеет статический метод для поворота
class Point {
private:
    float m_x;
    float m_y;

public:
    Point(float x, float y) : m_x(x), m_y(y) { }

    float x() const {
        return m_x;
    }

    float y() const {
        return m_y;
    }

    static Point rotate(float cx, float cy, float angle, Point p) {
        float s = sin(angle);
        float c = cos(angle);

        p.m_x -= cx;
        p.m_y -= cy;

        float xnew = p.m_x * c - p.m_y * s;
        float ynew = p.m_x * s + p.m_y * c;

        p.m_x = xnew + cx;
        p.m_y = ynew + cy;

        return p;
    }
};

// класс, который содержит информацию о звене и имеет методы для изменения поворота, позиции и рисования в окне
class Link {
private:
    sf::RectangleShape m_rectangleShape;
public:
    // конструктор принимает длину, позицию и поворот в градусах
    Link(float length, Point position, float initialRotation) {
        m_rectangleShape.setSize(sf::Vector2f(length, 10));
        m_rectangleShape.setOrigin(0, 0.5);
        m_rectangleShape.setPosition(position.x(), position.y());
        m_rectangleShape.setFillColor(sf::Color::Black);
        m_rectangleShape.rotate(initialRotation);
    }

    void move(Point position) {
        m_rectangleShape.setPosition(position.x() - 5, position.y() + 5);
    }

    void rotate(float angle) {
        m_rectangleShape.setRotation(angle);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_rectangleShape);
    }
};

// класс, содержащий информацию о шарнире между L1 и L2
class Joint {
private:
    sf::CircleShape m_circle;

public:
    Joint() {
        m_circle.setRadius(15);
        m_circle.setFillColor(sf::Color::Black);
        m_circle.setPointCount(100);
    }

    void move(Point position) {
        float radius = m_circle.getRadius();
        m_circle.setPosition(position.x() - radius, position.y() - radius);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_circle);
    }
};

// перевод радиан в градусы
double radiansToDegrees(double radians) {
    return radians * (180.0 / PI);
}


int main() {
  
    KinematicSolver kinematicSolver(350, 350);

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Inverse Kinematics", sf::Style::Close);
    Window.setFramerateLimit(60);

    Link L1(kinematicSolver.L1(), Point(0.0, 600.0), 0.0);
    Link L2(kinematicSolver.L2(), Point(kinematicSolver.L1(), 600.0), 0.0);

    Joint joint;

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        sf::Event event;
        while (Window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Window.close();
            }
        }

        if (!Window.isOpen()) {
            break;
        }

        Window.clear(sf::Color::White);

        // двигаемся к локальной позиции курсора в окне, получаем координаты курсора
        sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(Window);

        // вычитаем из высоты окна позицию по y, потому что у нас координаты растут снизу вверх
        mouseLocalPosition.y = 600.0 - mouseLocalPosition.y;

        kinematicSolver.Solve(mouseLocalPosition.x, mouseLocalPosition.y);

        // умножаем на -1 чтобы поворот был против часовой стрелки
        float alpha = kinematicSolver.alpha() * -1;
        float beta = kinematicSolver.beta() * -1;

        // вращаем L1
        L1.rotate(radiansToDegrees(alpha));

        // вычисляем новую позицию и поворот L2 
        Point L2_position = Point::rotate(0, 600.0, alpha, Point(kinematicSolver.L1(), 600.0));
        L2.move(L2_position);
        L2.rotate(radiansToDegrees(alpha + beta));

        L1.draw(Window);
        L2.draw(Window);

        joint.move(L2_position);
        joint.draw(Window);

        Window.display();
    }
}