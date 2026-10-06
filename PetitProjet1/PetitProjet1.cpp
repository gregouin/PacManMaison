#include <SFML/Graphics.hpp>
#include "tilemap.h"
#include "Player.h"
#include "Ennemy.h"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode({ 760, 800 }), "SFML works!");
    window.setFramerateLimit(60);

    Tilemap testmap;
    sf::VertexArray map = testmap.LoadMap();
    Player player;

    //sf::Font font("C:/Users/g.piret/Desktop/Projet/PetitProjet1/Asset/Font/score.ttf");
    sf::Font font("C:/Users/gregx/Downloads/PetitProjet1-master/PetitProjet1-master/Asset/Font/score.ttf");
    sf::Text Score(font);

    Score.setString(std::to_string(player.getScore()));
    Score.setPosition(sf::Vector2f(375, 5));
    

    sf::CircleShape Coin;
    Coin.setRadius(5);
    Coin.setFillColor(sf::Color::Yellow);
    
    sf::Clock moveTime;

    Ennemy Blinky(Couleur::rouge,player);

    while (window.isOpen())
    {
        Score.setString(std::to_string(player.getScore()));
        while (const std::optional event = window.pollEvent())
        {
            if (moveTime.getElapsedTime().asMilliseconds()>=200)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                {
                    player.targetTo(player.west,testmap);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                {
                    player.targetTo(player.east,testmap);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
                {
                    player.targetTo(player.north,testmap);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                {
                    player.targetTo(player.south,testmap);
                }
                moveTime.restart();
            }
           
            
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        player.move();
        Blinky.move(player.getTargetPos());
        window.clear(sf::Color::Black);
        window.draw(map);
        window.draw(player.GetSprite());
        for (int i = 0; i < 20; i++)
        {
            for (int x = 0; x < 19; x++) {
                if (testmap.GetCodeMap()[x][i] == '.')
                {
                    Coin.setPosition(sf::Vector2f(i*40+17.5,x*40+17.5));
                    window.draw(Coin);
                    
                }
            }
        }
        window.draw(Score);
        window.draw(Blinky.GetSprite());
        window.display();
    }
}