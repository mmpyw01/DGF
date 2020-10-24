#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(400, 400));
	body.setPosition(100, 575);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y = -14*speed * deltaTime;
	
	

	if (body.getPosition().y + body.getSize().y < groundHeight || movement.y < 0)
	{
		movement.y += gravity;
	}
	else {
		body.setPosition(body.getPosition().x, groundHeight - body.getSize().y);
		movement.y = 0;
	}
	body.move(movement.x, movement.y);

	if (movement.y == 0.0f)
	{
		row = 0;
	}
	else if(movement.y<0){
		row = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		row = 2;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
