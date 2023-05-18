#include <iostream>
/*
1.	Базовый конструктор																		
2.	Конструктор копирования																	
3.	Оператор присваивания копированием														
4.	Деструктор																				
5.	Операторы += и +, *= и *																
6.	Оператор ++ префиксный и постфиксный (увеличение действительной части числа на 1)		
7.	Операторы ввода и вывода																
*/

class Complex
{
private:

	long long m_re = 0;	// действительная часть
	long long m_im = 0;	// мнимая часть

public:

	friend std::ostream& operator << (std::ostream& out, const Complex& c);
	friend std::istream& operator >> (std::istream& in, Complex& c);

	Complex() : m_re(0), m_im(0) { }		// default constructor

	Complex(long long r, long long i) : m_re(r), m_im(i) { }

	Complex(long long r) : m_re(r), m_im(0) { }

	~Complex() { }		// default destructor

	Complex(const Complex& other) : Complex(other.m_re, other.m_im) {}		// copy constructor

	Complex& operator = (const Complex& other)		// copy assignment operator
	{
		Complex temp = other;
		std::swap(this->m_re, temp.m_re);
		std::swap(this->m_im, temp.m_im);
		return *this;
	}

	Complex& operator += (const Complex& other)
	{
		long long real = this->m_re + other.m_re;
		long long imag = this->m_im + other.m_im;
		Complex temp(real, imag);
		std::swap(this->m_re, temp.m_re);
		std::swap(this->m_im, temp.m_im);
		return *this;
	}

	Complex operator + (const Complex& other) const
	{
		Complex temp = *this;
		temp += other;
		return temp;

	}

	Complex& operator *= (const Complex& other)		// (2 + 2i)*(5 + 6i) = 10 - 12 + 12i + 10i = -2 + 22i
	{
		long long real = this->m_re * other.m_re - this->m_im * other.m_im;
		long long imag = this->m_im * other.m_re + this->m_re * other.m_im;
		Complex tmp(real, imag);
		std::swap(this->m_re, tmp.m_re);
		std::swap(this->m_im, tmp.m_im);
		return *this;
	}

	Complex operator * (const Complex& other) const
	{
		Complex temp = *this;
		temp *= other;
		return temp;
	}

	Complex& operator ++ ()		// префикс, сначала прибавляем к значению m_re 1, затем возвращаем ссылку на объект
	{
		this->m_re++;
		return *this;
	}

	Complex operator ++ (int)	// постфикс, сначала присваиваем новому объекту значение m_re, затем прибавляем 1
	{
		Complex temp = *this;
		++this->m_re;
		return temp;
	}
};

std::ostream& operator << (std::ostream& out, const Complex& c)
{
	if (c.m_im < 0)
	{
		out << c.m_re << " - " << c.m_im * (-1) << "i";
	}
	else
	{
		out << c.m_re << " + " << c.m_im << "i";
	}
	return out;
}

std::istream& operator >> (std::istream& in, Complex& c)
{
	in >> c.m_re;
	in >> c.m_im;
	return in;
}

int main()
{
	Complex c1(1, 2);
	Complex c2(3, 4);
	Complex c3 = c1 + c2;
	std::cout << "c3: " << c3 << std::endl;
	c1 *= c2;
	std::cout << "c: " << c1 << std::endl;
	Complex plusC = ++c1;
	std::cout << "++c: " << plusC << std::endl;
	Complex Cplus = c1++;
	std::cout << "c++: " << Cplus << std::endl;
}