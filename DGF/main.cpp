#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1960, 1080), "Parallax Example",
        sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Texture t;
    if (!t.loadFromFile("images/bg.png"))
        return EXIT_FAILURE;
    t.setRepeated(true);
    sf::Sprite background(t);
    background.setPosition(0, 0);
    background.setColor(sf::Color(255, 255, 255, 200));

    sf::Texture pyTexture;
    if (!pyTexture.loadFromFile("images/sp3.png"))
        return EXIT_FAILURE;
    pyTexture.setRepeated(true);
    sf::Sprite sprite(pyTexture);
    sprite.setPosition(100, 733);

    int spriteSizeX = pyTexture.getSize().x / 6;
    int spriteSizeY = pyTexture.getSize().y / 5;

    sprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));

    int animationFrame = 0;
    

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
    int frameIndex = 0;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                sprite.move(.1f, 0.f);
                sprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 1, spriteSizeX, spriteSizeY));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                sprite.move(-.1f, 0.f);
                sprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 3, spriteSizeX, spriteSizeY));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                sprite.move(0.f, -.1f);
                sprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, 0, spriteSizeX, spriteSizeY));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                sprite.move(0.f, .1f);
                sprite.setTextureRect(sf::IntRect(spriteSizeX * animationFrame, spriteSizeY * 2, spriteSizeX, 32));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            animationFrame++;

            if (animationFrame >= 2) {
                animationFrame = 0;
            }
           
        }

        // I set an arbitrary value as the offset, you'd calculate this based on camera position
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 500);

        window.clear();
        window.draw(background, &parallaxShader);
        window.display();
    }

    return EXIT_SUCCESS;
}