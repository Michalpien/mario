#include "ClassicMap.h"
#include "ErrorWindow.h"
#include <chrono>
#include <thread>

ClassicMap::ClassicMap() : WorldMap()
{
    std::ifstream file("assets/maps/ClassicMap.ldtk");
    file >> j;
    end = false;
    enemies = { Enemy(210, 212), Enemy(310, 212) };
    counter = 0;
}

void ClassicMap::play(sf::RenderWindow& window, Player& player)
{
    //changing character
    player.set_line(0);
    player.set_height(16);
    player.set_frames(4);
    sf::Texture blue;
    sf::Sprite blue_s;
    blue.loadFromFile("images/blue.png");
    blue_s.setTexture(blue);
    

    // Extract the tileset data
    json tileset1 = j["defs"]["tilesets"][0];

    // Extract the image file path and load the texture
    std::string imagePath = "assets/tiles/Map.png";
    sf::Texture texture1;

    if (!texture1.loadFromFile(imagePath))
    {
        std::cout << "tiles wrong path";
        ErrorWindow error("assets/tiles/Map.png doesn't exist");
        window.close();
    }
    // Create a sprite for each tile
    int tileSize = j["defs"]["tilesets"][0]["tileGridSize"];
    int spacing = j["defs"]["tilesets"][0]["spacing"];
    json gridTiles = j["levels"][0]["layerInstances"][1]["gridTiles"];

    set_players_spawn_point(player);  // Extract the tileset data
    // Run the main loop
    while (window.isOpen() && !end)
    {

        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                end = true;
            }
        }
        if (!open) { break; }
        // updating objects
        update_player(window, player);
        update_enemies(window, player);

        // Clear the window
        window.clear();
        // draw backround
        window.draw(blue_s);
        // Draw the map tiles
        
        for (auto& tile : gridTiles)
        {
            int tileId = tile["t"];
            sf::Sprite sprite(texture1);
            sprite.setTextureRect(sf::IntRect(tile["src"][0], tile["src"][1], 16, 16));
            sprite.setPosition(tile["px"][0] - 16, tile["px"][1] - 16);
            window.draw(sprite);
        }
        
        player.draw(window);
        draw_items(window);
        // Display the window
        window.display();
    }
    // changing character to starting
    player.set_line(1);
    player.set_height(10);
    player.set_frames(1);
    player.let_jump(true);
    player.change_direction(true);

}

void ClassicMap::set_players_spawn_point(Player& player)
{
    json entities = j["levels"][0]["layerInstances"][0]["entityInstances"];

    for (auto& entity : entities)
    {
        if (entity["__identifier"] == "Spawn")
        {
            player.set_poz(entity["px"][0], entity["px"][1]);
        }
        else if (entity["__identifier"] == "Boss")
        {
            exit = sf::FloatRect(entity["px"][0] - 16, entity["px"][1] - 16, entity["width"], entity["height"]);
        }
        else
        {
            colliders.push_back(sf::FloatRect(entity["px"][0] - 16, entity["px"][1] - 16, entity["width"], entity["height"]));
        }
    }
}

void ClassicMap::update_player(sf::RenderWindow& window, Player& player)
{
    player.gravitation();
    player.left_right();
    if (player.get_x() > 240)
    { 
        window.setView(sf::View(sf::FloatRect(160, 0, 256, 240)));
    }
    else if(player.get_x() < 210)
    {
        window.setView(sf::View(sf::FloatRect(0, 0, 256, 240)));
    }
    player.jump();
    

    auto player_collider = player.getPlayerCollider();
    // go to boss
    if (exit.intersects(player_collider))
    {
        end = true;
        sf::Texture win;
        sf::Sprite win_s;
        win.loadFromFile("images/won.png");
        win_s.setTexture(win);
        win_s.setPosition(196, 16);
        win_s.setScale(0.7f, 0.7f);
        window.draw(win_s);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    }

    else
    {
        for (auto& rect : colliders) {
            sf::FloatRect intersect;
            if (player_collider.intersects(rect, intersect)) {
                if (intersect.width < intersect.height) {
                    if (player_collider.left < intersect.left)
                        player.step_back(false, true);
                    else
                        player.step_back(true, false);
                }
                else {
                    player.stop_y();
                    if (player_collider.top + 10 < intersect.top)
                    {
                        player.step_back(false, false, true);
                        player.let_jump(true);
                    }
                    else
                        player.step_back(false, false, false, true);
                }
            }

        }
    }
}

void ClassicMap::update_enemies(sf::RenderWindow& window, Player& player)
{
    // colliding with player
    for (Enemy& enemy : enemies)
    {
        if (enemy.getCollider().intersects(player.getPlayerCollider()))
        {
            end = true;
            sf::Texture lost;
            lost.loadFromFile("images/lost.png");
            sf::Sprite lost_s;
            lost_s.setTexture(lost);
            if (player.get_x() > 240)
            {
                lost_s.setPosition(167, 5);
            }
            else if (player.get_x() < 210)
            {
                lost_s.setPosition(7, 5);
            }
            lost_s.setScale(0.9f, 0.9f);
            window.draw(lost_s);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
        // colliding with walls
        sf::FloatRect enemy_collider = enemy.getCollider();
        for (auto& rect : colliders)
        {
            if (enemy_collider.intersects(rect))
            {
                enemy.change_direction();
            }
        }
        enemy.walk();
  }
}

void ClassicMap::draw_items(sf::RenderWindow& window)
{
    for (Enemy& enemy : enemies)
    {
        enemy.draw(window);
    }
}