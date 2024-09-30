#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "MainMenu.h"
#include "WorldMap.h"
#include "Fight.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024,960), "Mario Word");
    sf::View view(sf::FloatRect(0, 0, 256, 240));
    window.setView(view);
    window.setFramerateLimit(120);

    
    WorldMap w_map;
    
    Player player;
    MainMenu menu;
    
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        menu.picking(window, player);
        menu.draw(window, player);
        window.display();
    }
    
}