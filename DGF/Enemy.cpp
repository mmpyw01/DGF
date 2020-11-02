#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture)
{
	enemy.setSize(sf::Vector2f(200, 200));
	enemy.setPosition(1500, 720);
	enemy.setTexture(texture);
}

Enemy::~Enemy()
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}

/*void Enemy::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Enemy::spawnEnemy()
{

}

void Enemy::updateEnemies()
{
	
}

void Enemy::update()
{
	this->pollEvent();
	this->updateEnemies();
}

void Enemy::renderEnemies()
{
}

void Enemy::render()
{
	this->window->clear();

	this->renderEnemies();

	this->window->display();
}*/


