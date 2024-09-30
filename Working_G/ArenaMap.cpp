#include "ArenaMap.h"
#include "PauseMenu.h"
#include "Enemy.h"
#include "Bullet.h"
#include "ErrorWindow.h"
#include <chrono>
#include <thread>

ArenaMap::ArenaMap() : WorldMap() 
{
    std::ifstream file("assets/maps/arena.ldtk");
    file >> j;
    end = false;
    lastUpdate = clock.getElapsedTime();
    enemies = {Enemy(25, 25)};
    counter = 0;
}

void ArenaMap::play(sf::RenderWindow& window, Player& player)
{
    //changing character
    player.set_line(0);
    player.set_height(16);
    player.set_frames(4);
    std::string message;
    sf::Font font;
    font.loadFromFile("assets/pixText.ttf");
    sf::Text text(message, font);
    text.setCharacterSize(140);
    text.setScale(0.1f, 0.1f);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(10, 10);


    // Extract the tileset data
    json tileset1 = j["defs"]["tilesets"][0];

    // Extract the image file path and load the texture
    std::string imagePath = "assets/tiles/Dungeon.png";
    sf::Texture texture1;

    if (!texture1.loadFromFile(imagePath))
    {
        std::cout << "assets/tiles/Dungeon.png doesn't exist";
        ErrorWindow error("File doesn't exist");
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
        message = std::to_string(counter) + "/4";
        text.setString(message);

        // Clear the window
        window.clear();

        // Draw the map tiles

        for (auto& tile : gridTiles)
        {
            int tileId = tile["t"];
            sf::Sprite sprite(texture1);
            sprite.setTextureRect(sf::IntRect(tile["src"][0], tile["src"][1], 16, 16));
            sprite.setPosition(tile["px"][0], tile["px"][1] - 16);
            window.draw(sprite);
        }
        update_bullets(window, player);
        player.draw(window);
        draw_items(window);
        window.draw(text);;
        //std::this_thread::sleep_for(std::chrono::milliseconds(800));
        // Display the window
        window.display();
    }
    // changing character to starting
    player.set_line(1);
    player.set_height(10);
    player.set_frames(1);
    
}

void ArenaMap::set_players_spawn_point(Player& player)
{
    json entities = j["levels"][0]["layerInstances"][0]["entityInstances"];

    for (auto& entity : entities)
    {
        if (entity["__identifier"] == "Spawn")
        {
            player.set_poz(entity["px"][0], entity["px"][1]);
        }
        else
        {
            colliders.push_back(sf::FloatRect(entity["px"][0], entity["px"][1], entity["width"], entity["height"]));
        }
    }
}

void ArenaMap::update_player(sf::RenderWindow& window, Player& player)
{
    // moving character
    player.left_right();
    player.up_down();
    // colliding with walls
    auto player_collider = player.getPlayerCollider();
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
                if (player_collider.top < intersect.top)
                    player.step_back(false, false, true);
                else
                    player.step_back(false, false, false, true);
            }
        }
    }
}

// moving and spawning enemies
void ArenaMap::update_enemies(sf::RenderWindow& window, Player& player)
{
    if ((clock.getElapsedTime() - lastSpawn).asSeconds() > 4)
    {
        switch (counter)
        {
        case 0:
            enemies.push_back(Enemy(240, 0));
            break;
        case 1:
            enemies.push_back(Enemy(0, 220));
            break;
        case 2:
            enemies.push_back(Enemy(240, 0));
            break;
        case 3:
            enemies.push_back(Enemy(240, 220));
            break;
        }
        lastSpawn = clock.getElapsedTime();
    }

    // colliding with player
    for (Enemy& enemy : enemies)
    {
        enemy.update(player);
        if (enemy.getCollider().intersects(player.getPlayerCollider()))
        {
            end = true;
            sf::Texture lost;
            lost.loadFromFile("images/lost.png");
            sf::Sprite lost_s;
            lost_s.setTexture(lost);
            lost_s.setPosition(7, 5);
            lost_s.setScale(0.9f, 0.9f);
            window.draw(lost_s);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
    }
    
}

// drawing items
void ArenaMap::draw_items(sf::RenderWindow& window)
{
    for (Enemy& enemy : enemies)
    {
        enemy.draw(window);
    }
    for (Bullet& bullet : bullets)
    {
        bullet.draw(window);
    }
}

// moving bullets and checking colliding
void ArenaMap::update_bullets(sf::RenderWindow& window, Player& player)
{
    if ((clock.getElapsedTime() - lastUpdate).asSeconds() > 1)
    {
        int x = player.get_x();
        int y = player.get_y();
        Bullet bullet(x + 3, y + 3, window);
       /* bullets.push_back(Bullet(x + 3, y + 3, window));*/
        bullets.push_back(bullet);
        lastUpdate = clock.getElapsedTime();

    }
    int b = -1;
    int e;
    for (Bullet& bullet : bullets)
    {
        // checking collidng with wall
        b += 1;
        bullet.update(window);
        sf::FloatRect bullet_collider = bullet.getCollider();
        for (auto& rect : colliders)
        {
            if (bullet_collider.intersects(rect) && bullets.begin() + b < bullets.end())
            {
                bullets.erase(bullets.begin() + b);
                break;
            }
        }

        // checking colliding with enemy
        e = -1;
        for (Enemy& enemy : enemies)
        {
            sf::FloatRect enemy_collider = enemy.getCollider();
            e += 1;
            if (bullet_collider.intersects(enemy_collider))
            {
                if (bullets.begin() + b < bullets.end())
                {
                    bullets.erase(bullets.begin() + b);
                }
                if (enemies.begin() + e < enemies.end())
                {
                    enemies.erase(enemies.begin() + e);
                }
                counter += 1;
            }
        }
        
    }
    // winning game
    if (counter == 4)
    {
        end = true;
        sf::Texture win;
        sf::Sprite win_s;
        win.loadFromFile("images/won.png");
        win_s.setTexture(win);
        win_s.setPosition(36, 16);
        win_s.setScale(0.7f, 0.7f);
        window.draw(win_s);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

}