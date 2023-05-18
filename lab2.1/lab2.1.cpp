#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

class AnimatedText
{
private:

    int m_time = 0;
    float m_OneSymbolTime = 0;

public:

    std::string m_Stroka = "";

    AnimatedText(const std::string& Stroka, int time)
    {
        m_Stroka = Stroka;
        m_time = time;
    }

    void Timing()
    {
        m_OneSymbolTime = (float(m_time) / m_Stroka.length());
    }

    void Sleep() const
    {
        std::this_thread::sleep_for(std::chrono::seconds(int(m_OneSymbolTime)));
    }

};

int main()
{
    std::string stroka;
    std::getline(std::cin, stroka);

    int time;
    std::cin >> time;

    AnimatedText AnimText(stroka, time);

    AnimText.Timing();

    AnimatedText SfmlText(stroka, time);

    sf::RenderWindow window(sf::VideoMode(500, 500), "AnimatedText");

    sf::Text TEXT;
    sf::Font FONT;

    FONT.loadFromFile("times.ttf");
    TEXT.setFont(FONT);
    TEXT.setPosition(50, 30);
    TEXT.setFillColor(sf::Color::White);
    //TEXT.setStyle(sf::Text::Underlined);
    TEXT.setCharacterSize(50);
    TEXT.setString(SfmlText.m_Stroka);
    SfmlText.Timing();

    std::string WrittenString = "";

    int c = 0;

    while (window.isOpen())
    {
        window.setFramerateLimit(20);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (c < SfmlText.m_Stroka.length())
        {
            WrittenString += SfmlText.m_Stroka[c];
            TEXT.setString(WrittenString);
            window.draw(TEXT);
            SfmlText.Sleep();
            window.display();
            window.clear(sf::Color::Black);
        }

        c++;
    }


    for (int i = 0; i < stroka.length(); i++)   //writes it on concole window
    {
        std::cout << AnimText.m_Stroka[i];
        AnimText.Sleep();
    }
}