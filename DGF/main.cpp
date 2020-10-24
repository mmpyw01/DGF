#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1960, 1080), "Don't Get F",
        sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

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
    if(!playerTexture.loadFromFile("images/sp5.png"))
        return EXIT_FAILURE;

    Player player(&playerTexture, sf::Vector2u(6, 5), 0.15f, 100.0f);

    float deltaTime = 0.0f;
    sf::Clock clock2;

    while (window.isOpen())
    {
        deltaTime = clock2.restart().asSeconds();
        
        sf::Event event;


        //Event Loop:
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        
        //set an arbitrary value as the offset, you'd calculate this based on camera position
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 20);

        player.Update(deltaTime);

        window.clear();
        window.draw(background, &parallaxShader);
        player.Draw(window);
        //player.drawTo(window);
        window.display();
    }

    return EXIT_SUCCESS;
}