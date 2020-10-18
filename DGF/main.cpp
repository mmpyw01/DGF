#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1960, 1080), "Don't Get F",
        sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

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

    sf::RectangleShape player(sf::Vector2f(400, 400));
    player.setPosition(100,575);
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("images/sp.png"))
        return EXIT_FAILURE;
    player.setTexture(&playerTexture);

    Animation animation(&playerTexture, sf::Vector2u(6, 5), 0.2f);

    float deltaTime = 0.0f;
    sf::Clock clock2;

    float offset = 0.f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock2.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }
           
        }
        
        //set an arbitrary value as the offset, you'd calculate this based on camera position
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 500);

        animation.Update(0, deltaTime);
        player.setTextureRect(animation.uvRect);

        window.clear();
        window.draw(background, &parallaxShader);
        window.draw(player);
        window.display();
    }

    return EXIT_SUCCESS;
}