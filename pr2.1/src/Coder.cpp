#include "Coder.hpp"

namespace an {

	Coder::Coder(std::string Message)
	{
		m_Message = Message;
		WordsCount(Message);
		FibonacciSequence();

		int counter = -1;
		for (int i = 0; i < m_WordCount; i++)
		{
			counter++;
			while (Message[counter] != ' ')
			{
				if (counter >= Message.length())
				{
					break;
				}
				m_Words[i] += Message[counter];
				counter++;
			}
		}
	}

	void Coder::ShowText()
	{
		std::string s = "";
		for (int i = 0; i < m_WordCount; i++)
		{
			s += m_Words[i];
			s += " ";
		}
		std::cout << s << std::endl;
	}
	
	void Coder::InputKey()
	{
		std::cout << "Input key: ";
		for (int i = 0; i < m_WordCount; i++)
		{
			std::cin >> m_CurrentKey[i];
		}

		isKeyCorrect();
	}

	void Coder::Encode()
	{
		std::string SwapWords[30];
		
		for (int i = 0; i < m_WordCount; i++)
		{
			for (int j = 0; j < m_WordCount; j++)
			{
				if (m_CurrentKey[i] == m_FiboKey[j])
				{
					SwapWords[i] = m_Words[j];
				}
			}
		}

		for (int i = 0; i < m_WordCount; i++)
		{
			m_Words[i] = SwapWords[i];
		}
	}

	void Coder::Decode()
	{
		std::string SwapWords[30];

		for (int i = 0; i < m_WordCount; i++)
		{
			for (int j = 0; j < m_WordCount; j++)
			{
				if (m_CurrentKey[i] == m_FiboKey[j])
				{
					SwapWords[j] = m_Words[i];
				}
			}

		}

		for (int i = 0; i < m_WordCount; i++)
		{
			m_Words[i] = SwapWords[i];
		}
	}

	void Coder::Output()
	{
		std::cout << std::endl;

		for (int i = 0; i < m_WordCount; i++)
		{
			std::cout << m_Words[i] << " ";			
		}

		std::cout << std::endl << std::endl;
	}

	void Coder::isKeyCorrect()
	{
		int flag = 0;

		for (int i = 0; i < m_WordCount; i++)
		{
			for (int j = 0; j < m_WordCount; j++)
			{
				if (m_CurrentKey[i] == m_FiboKey[j])
				{
					flag++;
				}
			}

		}

		if (flag != m_WordCount) 
		{
			throw "Incorrect code!";
		}
	}

	void Coder::OutputCurrentKey()
	{
		std::cout << "Current key: ";

		for (int i = 0; i < m_WordCount; i++)
		{
			std::cout << m_CurrentKey[i] << " ";
		}
	}
}