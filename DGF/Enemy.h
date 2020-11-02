#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class Enemy
{
public:
	Enemy(sf::Texture* texture);
	~Enemy();

	void Draw(sf::RenderWindow& window);
	void pollEvent();
	

private:
	sf::RectangleShape enemy;
	sf::RenderWindow* window;
	sf::Event ev;

	int point;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//void 
	//void spawnEnemy();
	void updateEnemies();
	void renderEnemies();
	void render();
	void update();
};

