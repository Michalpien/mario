#include "WorldMap.h"
#include "ArenaMap.h"
#include "PauseMenu.h"
#include "Fight.h"
#include "ClassicMap.h"
#include "ErrorWindow.h"
#include <chrono>
#include <thread>


WorldMap::WorldMap() : ldtk_filename("assets/maps/WorldMap.ldtk"), open(true)
{
    std::ifstream file(ldtk_filename);
    file >> j;
}

WorldMap::~WorldMap()
{
}

void WorldMap::play(sf::RenderWindow& window, Player& player)
{

    // Extract the tileset data
    json tileset1 = j["defs"]["tilesets"][0];
    json tileset2 = j["defs"]["tilesets"][1];

    // Extract the image file path and load the texture
    std::string imagePath1 = "assets/tiles/MasterSimple.png";
    std::string imagePath2 = "assets/tiles/atlas.png";
    sf::Texture texture1;
    sf::Texture texture2;

    if (!texture1.loadFromFile(imagePath1))
    {
        std::cout << "tiles wrong path1";
        ErrorWindow error("assets/tiles/MasterSimple.png doesn't exist");
        window.close();
    }
    if (!texture2.loadFromFile(imagePath2))
    {
        std::cout << "tiles wrong path2";
        ErrorWindow error("assets/tiles/atlas.png doesn't exist");
        window.close();
    }
    // Create a sprite for each tile
    int tileSize = j["defs"]["tilesets"][0]["tileGridSize"];
    int spacing = j["defs"]["tilesets"][0]["spacing"];
    json gridTiles1 = j["levels"][0]["layerInstances"][2]["gridTiles"];
    json gridTiles2 = j["levels"][0]["layerInstances"][1]["gridTiles"];


    set_players_spawn_point(player);
    PauseMenu pause;
    // Run the main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                pause.display(window, player);
                pause.restart();
                open = !pause.ret;
            }
        }
        if (!open) { break; }
        update_player(window, player);

        // Clear the window
        window.clear();

        // Draw the map tiles

        for (auto& tile : gridTiles1)
        {
            int tileId = tile["t"];
            sf::Sprite sprite(texture1);
            sprite.setTextureRect(sf::IntRect(tile["src"][0], tile["src"][1], 16, 16));
            sprite.setPosition(tile["px"][0], tile["px"][1]);
            window.draw(sprite);
        }
        for (auto& tile : gridTiles2)
        {
            int tileId = tile["t"];
            sf::Sprite sprite(texture2);
            sprite.setTextureRect(sf::IntRect(tile["src"][0], tile["src"][1], 16, 16));
            sprite.setPosition(tile["px"][0], tile["px"][1]);
            window.draw(sprite);
        }
        player.draw(window);
        // Display the window
        window.display();
    }
}

void WorldMap::set_players_spawn_point(Player& player)
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
            boss_entry = sf::FloatRect(entity["px"][0], entity["px"][1], entity["width"], entity["height"]);
        }
        else if (entity["__identifier"] == "Colide2")
        {
            colliders.push_back(sf::FloatRect(entity["px"][0], entity["px"][1] - 4, entity["width"], entity["height"]));
        }
        else if (entity["__identifier"] == "Arena")
        {
            arena_entry = sf::FloatRect(entity["px"][0], entity["px"][1], entity["width"], entity["height"]);
        }
        else if (entity["__identifier"] == "Classic")
        {
            classic_entry = sf::FloatRect(entity["px"][0], entity["px"][1], entity["width"], entity["height"]);
        }
        else //add coliders
        {
            colliders.push_back(sf::FloatRect(entity["px"][0], entity["px"][1], entity["width"], entity["height"]));
        }
    }
}

// scene before changing map
void WorldMap::bossScene(sf::RenderWindow& window, Player& player, std::string obj)
{
    sf::Sprite boss_s;
    sf::Texture boss_t;
    if (obj == "boss")
    {
        boss_t.loadFromFile("images/litle_" + player.name_2 + ".png");
        boss_s.setPosition(boss_entry.left + 5, boss_entry.top);
        boss_s.setScale(1, 1);
    }
    else
    {
        boss_t.loadFromFile("images/goomba.png");
        boss_s.setPosition(arena_entry.left + 3, arena_entry.top - 13);
        boss_s.setScale(0.016f, 0.016f);
    }
    boss_s.setTexture(boss_t);
    window.draw(boss_s);
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

// moving player
void WorldMap::update_player(sf::RenderWindow& window, Player& player)
{
    player.left_right();
    player.up_down();

    auto player_collider = player.getPlayerCollider();
    // go to boss
    if (boss_entry.intersects(player_collider))
    {
        bossScene(window, player, "boss");
        Fight fight(player.name);
        Boss boss(player.name_2, 100);
        PlayerFight playerF(player.name, 100);
        playerF.addAtack("Shield", "images/Skils/defense.png", "images/Skils/defense_fight.png", 9, 99, 185, 198, 0, true);
        playerF.addAtack("Fire Burst", "images/Skils/fire.png", "images/Skils/fire_attack.png", 16, 64, 185, 218, 10);
        playerF.addAtack("MUDA MUDA", "images/Skils/fist.png", "images/Skils/fist_attack.png", 11, 50, 224, 199, 20);
        boss.addAtack("Shield", "images/Skils/defense.png", "images/Skils/defense_fight.png", 9, 99, 185, 198, 0, true);
        boss.addAtack("Fire Burst", "images/Skils/fire.png", "images/Skils/fire_attack.png", 16, 64, 185, 218, 10);
        boss.addAtack("MUDA MUDA", "images/Skils/fist.png", "images/Skils/fist_attack.png", 11, 50, 224, 199, 100);
        playerF.set_poz(195, 80, 50, 190, 165, 175);
        boss.set_poz(50, 190, 195, 80, 12, 12);
        fight.fight(window, playerF, boss);
        player.set_poz(boss_entry.left - 16, boss_entry.top);
        
    }
    // go to arena
    else if(arena_entry.intersects(player_collider))
    {
        bossScene(window, player, "arena");
        ArenaMap a_map;
        a_map.play(window, player);
        player.set_poz(arena_entry.left - 16, arena_entry.top);
    }
    else if (classic_entry.intersects(player_collider))
    {
        ClassicMap c_map;
        c_map.play(window, player);
        player.set_poz(classic_entry.left + 32, classic_entry.top);
        sf::View view(sf::FloatRect(0, 0, 256, 240));
        window.setView(view);
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
                    if (player_collider.top < intersect.top)
                        player.step_back(false, false, true);
                    else
                        player.step_back(false, false, false, true);
                }
            }
        }
    }
}
