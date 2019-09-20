#include "Player.h"



Player::Player()
{
	hitbox = {24,40,16,24};

	animation.setTexture(Settings::PLAYER_TEXTURE);
	animation.setIndividualSpriteSize(64, 64);
	animation.setSpriteStartingPosition(0, 8 * 64);
	animation.setSpriteAmount(8);
	animation.setUpdateTime(0.1f);
	animation.setPosition(0.0f, 0.0f);
	moving = false;
	walking_speed = 300;

	float scale = 4.0f;
	animation.setScale(scale);
	hitbox.top *= (int)scale;
	hitbox.left *= (int)scale;
	hitbox.width *= (int)scale;
	hitbox.height *= (int)scale;
}


Player::~Player()
{
}

void Player::update(float deltaT)
{
	move();
	if (moving) {
		animation.update(deltaT);

		position.x += moveDirection.x * deltaT * walking_speed;
		position.y += moveDirection.y * deltaT * walking_speed;

		solveCollision();
		animation.setPosition(position.x, position.y);
	}
}

void Player::move()
{
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveUp();
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveDown();
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveLeft();
		moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveRight();
		moving = true;
	}
	else
	{
		moving = false;
		moveDirection.x = 0;
		moveDirection.y = 0;
	}
}

void Player::handleEvents(sf::Event sfEvent)
{
		
}

void Player::render() const
{
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(animation);
}

void Player::moveUp()
{
	if (!isMovingUp())
	{
		animation.setSpriteStartingPosition(0, 8 * 64);
		moveDirection.x += Settings::Movement::PLAYER_UP[0];
		moveDirection.y += Settings::Movement::PLAYER_UP[1];
	}
}

void Player::moveDown()
{
	if (!isMovingDown())
	{
		animation.setSpriteStartingPosition(0, 10 * 64);
		moveDirection.x += Settings::Movement::PLAYER_DOWN[0];
		moveDirection.y += Settings::Movement::PLAYER_DOWN[1];
	}
}

void Player::moveLeft()
{
	if (!isMovingLeft())
	{
		animation.setSpriteStartingPosition(0, 9 * 64);
		moveDirection.x += Settings::Movement::PLAYER_LEFT[0];
		moveDirection.y += Settings::Movement::PLAYER_LEFT[1];
	}
}

void Player::moveRight()
{
	if (!isMovingRight())
	{
		animation.setSpriteStartingPosition(0, 11 * 64);
		moveDirection.x += Settings::Movement::PLAYER_RIGHT[0];
		moveDirection.y += Settings::Movement::PLAYER_RIGHT[1];
	}
}

bool Player::isMovingInDirection(const sf::Vector2f & direction) const
{
	return (moveDirection == direction);
}

bool Player::isMovingInDirection(float x, float y) const
{
	return (moveDirection.x == x && moveDirection.y == y);
}

bool Player::isMovingUp() const
{
	return moveDirection.y == Settings::Movement::PLAYER_UP[1];
}

bool Player::isMovingDown() const
{
	return moveDirection.y == Settings::Movement::PLAYER_DOWN[1];
}

bool Player::isMovingRight() const
{
	return moveDirection.x == Settings::Movement::PLAYER_RIGHT[0];
}

bool Player::isMovingLeft() const
{
	return moveDirection.x == Settings::Movement::PLAYER_LEFT[0];
}

sf::Vector2f Player::getPosition() const
{
	return animation.getPosition();
}

sf::Vector2i Player::getSize() const
{
	return animation.getIndividualSrpiteSize();
}

sf::IntRect Player::getHitBox() const
{
	sf::IntRect hb = hitbox;
	hb.top += (int)position.y;
	hb.left += (int)position.x;
	return hb;
}

void Player::setHitBox(const sf::IntRect & hitbox)
{
	position.x = (float)hitbox.left - this->hitbox.left;
	position.y = (float)hitbox.top - this->hitbox.top;
}

void Player::setPosition(const sf::Vector2f & pos)
{
	animation.setPosition(pos.x, pos.y);
	position = pos;
}

void Player::setPosition(float x, float y)
{
	animation.setPosition(x, y);
	position.x = x;
	position.y = y;
}

void Player::solveCollision()
{
	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x + animation.getIndividualSrpiteSize().x > Settings::WIDTH)
	{
		position.x = (float)Settings::WIDTH - animation.getIndividualSrpiteSize().x;
	}

	if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.y + animation.getIndividualSrpiteSize().y > Settings::WIDTH)
	{
		position.y = (float)Settings::HEIGHT - animation.getIndividualSrpiteSize().y;
	}

}
