#include <iostream>

/*
Реализуйте шаблонный класс для описания матриц (в частном случае, векторов). Предусмотрите 3 шаблонных параметра: тип элемента, размеры матрицы N и M (N, M <= 3)
    В составе класса должны быть:
1.	Конструктор копирования	                                                    +
2.	Оператор присваивания копированием											+
3.	Оператор ввода и вывода														+
4.	Операторы +, +=, *, *=                                                      ++++
5.	Оператор ++, который увеличивает все элементы матрицы на 1				    +
6.	Метод вычисления определителя											    +
7.	Метод или оператор для получения и изменения элемента матрицы по индексу	+
*/


template<typename T, unsigned char N, unsigned char M>

class Matrix {

private:

    T m_arr[N][M];

public:

    template <typename T, unsigned char N, unsigned char M>
    friend T at(const Matrix<T, N, M>& matrix, unsigned char n, unsigned char m);

    template <typename T, unsigned char N, unsigned char M>
    friend void setElement(Matrix<T, N, M>& matrix, unsigned char n, unsigned char m, T element);

    template <typename T, unsigned char N, unsigned char M>
    friend std::ostream& operator << (std::ostream& out, const Matrix<T, N, M>& matrix);

    template <typename T, unsigned char N, unsigned char M>
    friend std::istream& operator >> (std::istream& in, Matrix<T, N, M>& matrix);

    Matrix()
    {
        std::fill((T*)m_arr, (T*)m_arr + N * M, 0);
        std::cout << "Default constructor" << std::endl;
    }

    ~Matrix()
    {
        std::cout << "Destructor" << std::endl;
    };

    Matrix(const Matrix<T, N, M>& matrix)
    {
        std::copy(matrix.m_arr[0], matrix.m_arr[0] + N * M, m_arr[0]);
        std::cout << "Copy constructor" << std::endl;
    }

    Matrix<T, N, M>& operator = (const Matrix<T, N, M>& other)
    {
        std::copy(other.m_arr[0], other.m_arr[0] + N * M, m_arr[0]);
        std::cout << "Copy asignment operator" << std::endl;
        return *this;
    }

    double determinant()
    {
        if (N == 1 && M == 1)
        {
            return (double)m_arr[0][0];
        }
        if (N == 2 && M == 2)
        {
            return ((double)(m_arr[0][0] * m_arr[1][1]) - (double)(m_arr[1][0] * m_arr[0][1]));
        }

        if (N == 3 && M == 3)   // правило треугольника
        {
            return ((double)(m_arr[0][0] * m_arr[1][1] * m_arr[2][2]) + ((double)m_arr[0][1] * m_arr[1][2] * m_arr[2][0]) +
                ((double)m_arr[1][0] * m_arr[2][1] * m_arr[0][2]) - ((double)m_arr[0][2] * m_arr[1][1] * m_arr[2][0]) -
                ((double)m_arr[1][2] * m_arr[2][1] * m_arr[0][0]) - ((double)m_arr[1][0] * m_arr[0][1] * m_arr[2][2]));
        }

        throw std::exception();

    }

    Matrix <T, N, M> operator + (const Matrix <T, N, M>& other) {

        Matrix <T, N, M> result;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                result.m_arr[i][j] = m_arr[i][j] + other.m_arr[i][j];
            }
        }

        return result;
    }

    void operator += (const Matrix <T, N, M>& other) {

        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                m_arr[i][j] = m_arr[i][j] + other.m_arr[i][j];
            }
        }
    }

    Matrix operator * (const Matrix& other)
    {
        Matrix temp = *this;
        temp *= other;

        return temp;
    }

    Matrix <T, N, M>& operator *= (const Matrix <T, N, M>& other) {

        Matrix <T, N, M> result;

        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                for (size_t k = 0; k < N; k++) {
                    result.m_arr[i][j] += m_arr[i][k] * other.m_arr[k][j];
                }
            }
        }

        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                m_arr[i][j] = result.m_arr[i][j];
            }
        }

        return *this;
    }

    Matrix& operator ++ ()      //префикс, сначала прибавляем к значению m_re 1, затем возвращаем ссылку на объект
    {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                this->m_arr[i][j] += 1;
            }
        }
        return *this;
    }

    Matrix operator ++ (int)		//постфикс, сначала присваиваем новому объекту значение m_re, затем прибавляем 1
    {
        Matrix temp = *this;

        for (int i = 0; i < this->N; i++)
        {
            for (int j = 0; j < this->M; j++)
            {
                ++(this->m_arr[i][j]);
            }
        }

        return temp;
    }
};


template <typename T, unsigned char N, unsigned char M>
T at(const Matrix<T, N, M>& matrix, unsigned char n, unsigned char m)
{
    return matrix.m_arr[n - 1][m - 1];
}

template <typename T, unsigned char N, unsigned char M>
void setElement(Matrix<T, N, M>& matrix, unsigned char n, unsigned char m, T element) {
    matrix.m_arr[n - 1][m - 1] = element;
}

template <typename T, unsigned char N, unsigned char M>
std::ostream& operator << (std::ostream& out, const Matrix<T, N, M>& matrix)
{
    for (size_t i = 0; i < N; i++)
    {
        out << "   ( ";
        for (size_t j = 0; j < M; j++)
        {
            out << matrix.m_arr[i][j] << ' ';
        }
        out << ')' << std::endl;
    }
    return out;
}


template <typename T, unsigned char N, unsigned char M>
std::istream& operator >> (std::istream& in, Matrix<T, N, M>& matrix)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            in >> matrix.m_arr[i][j];
        }
    }
    return in;
}




int main()
{
    try {

        Matrix<int, 3, 3> a;

        std::cin >> a;
        std::cout << a;
        //std::cout << "Determinant: " << a.determinant() << std::endl;
        //std::cout << ++a << std::endl;

        Matrix<int, 3, 3> b = a;
        //std::cout << "Sum a+b: " << a + b << std::endl;
        
        //Matrix<int, 3, 3> c;
        //c = b = a;

        std::cout << (a * b) << std::endl;
        //std::cout << at(c, 1, 1);
        //std::cout << c << std::endl;
        //setElement(c, 1, 1, 10);
        //std::cout << c << std::endl;
    }
    catch (...) {
        std::cout << "Determinant doesn't exist!";
    }
}
