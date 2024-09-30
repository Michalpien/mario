#include "ErrorWindow.h"
#include <SFML/Graphics.hpp>

ErrorWindow::ErrorWindow(const std::string& errorMessage) {
    sf::RenderWindow window(sf::VideoMode(400, 200), "File loading error");

    sf::Font font;
    font.loadFromFile("assets/pixText.ttf");
    sf::Text errorText(errorMessage, font);
    errorText.setCharacterSize(24);
    errorText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = errorText.getLocalBounds();
    errorText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    errorText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(errorText);
        window.display();
    }
}

