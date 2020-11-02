#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "MainMenu.h"

int page_number;

int main()
{

    sf::RenderWindow window(sf::VideoMode(1960, 1080), "Don't Get F",
        sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    MainMenu mainmenu(1960, 1080);

    sf::Vector2f velocity(sf::Vector2f(0, 0));

    sf::Texture t;
    if (!t.loadFromFile("images/bg.png"))
        return EXIT_FAILURE;
    t.setRepeated(true);
    sf::Sprite background(t);
    background.setPosition(0, 0);
    background.setColor(sf::Color(255, 255, 255, 200));

    sf::Shader parallaxShader;
    parallaxShader.loadFromMemory(
        "uniform float offset;"

        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic
        "    gl_FrontColor = gl_Color;"
        "}"
        , sf::Shader::Vertex);

    float offset = 0.f;
    sf::Clock clock;

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("images/sp5.png"))
        return EXIT_FAILURE;

    Player player(&playerTexture, sf::Vector2u(6, 5), 0.15f, 100.0f);

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("images/en.png"))
        return EXIT_FAILURE;
    Enemy enemy(&enemyTexture);


    float deltaTime = 0.0f;
    sf::Clock clock2;

    while (window.isOpen())
    {
       

        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::KeyReleased:
                switch (evnt.key.code)
                {
                case sf::Keyboard::W:
                    mainmenu.moveUp();
                    break;

                case sf::Keyboard::S:
                    mainmenu.moveDown();
                    break;

                case sf::Keyboard::Enter:
                    switch (mainmenu.mainMenuPressed())
                    {
                    case 0:
                        window.close();
                        page_number = 1;
                        break;
                    case 1:
                        window.close();
                        page_number = 2;
                        break;
                    case 2:
                        window.close();
                        page_number = 3;
                        break;
                    }
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

            //set an arbitrary value as the offset, you'd calculate this based on camera position
            
            
            mainmenu.Draw(window);
            window.display();
        }
    if (page_number == 1)
    { 
        
        //Play
        sf::RenderWindow window_play(sf::VideoMode(1920, 1080), "Play!", sf::Style::Fullscreen);
        while (window_play.isOpen())
        {
           
            deltaTime = clock2.restart().asSeconds();

            sf::Event evnt;
            while (window_play.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::KeyReleased:
                    switch (evnt.key.code)
                    {
                    case sf::Keyboard::Escape:
                        window_play.close();
                        main();
                        break;
                    }
                    break;
                }

            }
            parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 20);

            player.Update(deltaTime);

            window_play.clear();

            window_play.draw(background, &parallaxShader);
            player.Draw(window_play);
            enemy.Draw(window_play);
            window_play.display();
            window_play.setFramerateLimit(60);
        }
    }
        return EXIT_SUCCESS;
    }
