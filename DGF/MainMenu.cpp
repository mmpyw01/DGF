#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
    if (!font.loadFromFile("fonts/Kanit-SemiBold.ttf"))
        printf("LOAD MAI DAI I SUS");

    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::Blue);
    mainMenu[0].setString("PLAY");
    mainMenu[0].setCharacterSize(40);
    mainMenu[0].setPosition(500, 500);

    //Score
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::White);
    mainMenu[1].setString("SCORE");
    mainMenu[1].setCharacterSize(40);
    mainMenu[1].setPosition(500, 600);

    //Quit
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(sf::Color::White);
    mainMenu[2].setString("QUIT");
    mainMenu[2].setCharacterSize(40);
    mainMenu[2].setPosition(500, 700);

    mainMenuSelected = 0;

}

MainMenu::~MainMenu()
{

}

//Draw MainMenu
void MainMenu::Draw(sf::RenderWindow& window)
{
    for (int i = 0; i < 3; i++)
    {
        window.draw(mainMenu[i]);
    }
}

//move up
void MainMenu::moveUp()
{
    if (mainMenuSelected - 1 >= -1)
    {
        mainMenu[mainMenuSelected].setFillColor(sf::Color::White);

        mainMenuSelected--;
        if (mainMenuSelected == -1)
        {
            mainMenuSelected = 2;
        }
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);
    }
}

//move down
void MainMenu::moveDown()
{
    if (mainMenuSelected + 1 <= Max_main_menu)
    {
        mainMenu[mainMenuSelected].setFillColor(sf::Color::White);

        mainMenuSelected++;
        if (mainMenuSelected == 3)
        {
            mainMenuSelected = 0;
        }
        mainMenu[mainMenuSelected].setFillColor(sf::Color::Blue);
    }
}