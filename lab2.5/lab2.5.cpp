#include <iostream>
#include <vector>

struct BitInfo {
	size_t byteIndex;
	unsigned char bitIndex;
};


template<>
class std::vector<bool> {
private:
	unsigned char* m_arr; // указатель на динамически выделенную память
	size_t m_allocatedBytes; // количество элементов в m_arr
	size_t m_usedBits; // количество использованных бит в массиве

	BitInfo getBitInfo(size_t bitIndex) 
	{
		return BitInfo
		{
			(size_t)(bitIndex / 8.0),
			(unsigned char)(bitIndex % 8)
		};
	}

	void set(unsigned char* byte, unsigned char index)	//1
	{
		*byte |= (1 << index);
	}

	void reset(unsigned char* byte, unsigned char index)	//0
	{
		*byte &= ~(1 << index);
	}

	bool check(unsigned char* byte, unsigned char index) 
	{
		return (*byte & (1 << (index))) != 0;
	}

	void setBit(unsigned char* array, size_t bitIndex, bool value) { // устанавливает в определенном индексе заданное значение
		
		BitInfo bitInfo = getBitInfo(bitIndex);
		unsigned char* byte = &array[bitInfo.byteIndex];

		if (value) {
			set(byte, bitInfo.bitIndex);
		} 
		else {
			reset(byte, bitInfo.bitIndex);
		}
	}

	bool getBit(unsigned char* array, size_t bitIndex) {	// возвращает значение по этому индексу
		BitInfo bitInfo = getBitInfo(bitIndex);
		return check(&array[bitInfo.byteIndex], bitInfo.bitIndex);
	}

public:
	std::vector<bool>() : m_arr(new unsigned char[1]), m_allocatedBytes(1), m_usedBits(0) {}

	void add(bool value) 		//добавляет новое значение в конец
	{
		setBit(m_usedBits, value);

		if (++m_usedBits == m_allocatedBytes * 8) 			// если необходимо, выделяем еще 1 байт
		{
			unsigned char* temp = new unsigned char[++m_allocatedBytes];
			for (size_t i = 0; i < m_allocatedBytes - 1; i++) {
				temp[i] = m_arr[i];
			}

			delete[] m_arr;
			m_arr = temp;
		}
	}

	void insert(size_t bitIndex, bool value)	// вставляет значение по индексу, сдвигая все значения с этого индекса вперёд
	{
		if (m_usedBits + 1 == m_allocatedBytes * 8) {
			m_allocatedBytes++;
		}

		unsigned char* newArr = new unsigned char[m_allocatedBytes];
		size_t currentIndex = 0;
		while (currentIndex != bitIndex) {
			setBit(newArr, currentIndex, getBit(m_arr, currentIndex));
			currentIndex++;
		}

		setBit(newArr, currentIndex++, value);

		size_t j = bitIndex;
		while (j < m_usedBits) {
			setBit(newArr, currentIndex++, getBit(m_arr, j));
			j++;
		}

		m_usedBits++;

		delete[] m_arr;
		m_arr = newArr;
	}

	void erase(size_t startIndex, size_t endIndex) // удаляет диапазон значений и перезаписывает массив
	{		
		// проверяем, правильные и индексы
		if (m_usedBits == 0 || endIndex >= m_usedBits || endIndex < startIndex) {
			throw std::exception();
		}

		size_t bitsToRemove = endIndex - startIndex + 1;
		size_t newUsedBits = m_usedBits - bitsToRemove;
		size_t newAllocatedBytes = (size_t)std::ceill(newUsedBits / 8.0);

		unsigned char* newArr = new unsigned char[newAllocatedBytes];

		size_t newIndex = 0;
		for (size_t oldIndex = 0; oldIndex < m_usedBits; oldIndex++) {
			if (oldIndex < startIndex || oldIndex > endIndex) {
				setBit(newArr, newIndex++, getBit(m_arr, oldIndex));
			}
		}

		delete[] m_arr;

		m_arr = newArr;
		m_allocatedBytes = newAllocatedBytes;
		m_usedBits = newUsedBits;
	}

	// возвращает количество использованных бит
	size_t size() 
	{
		return m_usedBits;
	}

	// устанавливает значение по индексу
	void setBit(size_t bitIndex, bool value) 
	{
		setBit(m_arr, bitIndex, value);
	}

	// получает значение по индексу
	bool getBit(size_t bitIndex) 
	{
		return getBit(m_arr, bitIndex);
	}


	void print() 
	{
		for (size_t i = 0; i < m_usedBits; i++) {
			std::cout << getBit(i) << std::endl;
		}
	}
};


int main() {

	std::vector<bool> vector;
	vector.add(true);					//[1]
	vector.add(true);					//[11]
	vector.insert(1, false);			//[101]
	vector.print(); 
	std::cout << std::endl;

	vector.add(true);					//[1011]
	vector.add(true);					//[10111]
	vector.erase(1, 3);					//[11]
	vector.print();
	std::cout << std::endl;

	vector.setBit(vector.size() - 1, false);		//[10]
	vector.add(true);								//[101]
	vector.print();
}