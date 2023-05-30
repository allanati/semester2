#include <iostream>

const int N = 1000;

void Copy(int* mas1, int* mas2, size_t size)
{
    // Determine the number of elements that can be copied in a single block
    size_t blockSize = sizeof(size_t) / sizeof(int);
    size_t numBlocks = size / blockSize;

    // Perform block copying
    size_t* tmp1 = reinterpret_cast<size_t*>(mas1);
    size_t* tmp2 = reinterpret_cast<size_t*>(mas2);
    for (size_t i = 0; i < numBlocks; i++)
    {
        *tmp1++ = *tmp2++;
    }

    // Perform byte-level copying for the remaining elements
    char* tmp1Char = reinterpret_cast<char*>(tmp1);
    char* tmp2Char = reinterpret_cast<char*>(tmp2);
    size_t remainingBytes = (size - numBlocks * blockSize) * sizeof(int);
    for (size_t i = 0; i < remainingBytes; i++)
    {
        *tmp1Char++ = *tmp2Char++;
    }
}

void Output(int* mas) {
    for (int i = 0; i < 10; i++)
    {
        std::cout << mas[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int mas1[N] = { 0, 1, 2, 3, 4, 5, 6 };
    int mas2[N] = { 3, 2, 1 };

    Copy(mas1, mas2, N);

    Output(mas1);
    Output(mas2);

    return 0;
}