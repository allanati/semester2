#pragma once
#include <iostream>
#include <string>

namespace an
{
	class Coder
	{
	private:
		std::string m_Message;
		std::string m_Words[30];

		int m_FiboKey[30] = {1,2};
		int m_CurrentKey[30] = {};

		int m_WordCount = 1;


		void FibonacciSequence()
		{
			for (int i = 2; i < m_WordCount; i++)
			{
				m_FiboKey[i] = m_FiboKey[i - 1] + m_FiboKey[i - 2];
			}
		}

		void WordsCount(const std::string& Message)
		{
			for (int i = 0; i < Message.length(); i++)
			{
				if (Message[i] == ' ')
				{
					m_WordCount++;
				}
			}
			if (m_WordCount > 30)
			{
				throw "Too many words!";
			}
		}

	public:

		Coder(std::string Message);

		~Coder()
		{
			std::cout << "End of program";
		}

		void ShowText();

		void InputKey();

		void Encode();

		void Decode();

		void Output();

		void isKeyCorrect();

		void OutputCurrentKey();

	};
}