#include <iostream>
#include <string>
#include "Coder.hpp"

int main()
{
	try
	{
		std::cout << "Input message: ";
		std::string str;
		std::getline(std::cin, str);
		an::Coder Sypher(str);
		Sypher.InputKey();
		std::cout << std::endl << "Encode: " << std::endl;
		Sypher.Encode();
		Sypher.OutputCurrentKey();
		std::cout << std::endl << "Output: ";
		Sypher.Output();
		std::cout << std::endl << "Decode: " << std::endl;
		Sypher.Decode();
		Sypher.OutputCurrentKey();
		std::cout << std::endl << "Output: ";
		Sypher.Output();

	}

	catch (const char message) {
		std::cout << message;
	}

}