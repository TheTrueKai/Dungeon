#include "Animation.h"



Animation::Animation()
{
	SpriteStartingPosition = { 0,0 };
	IndividualSpriteSize = { 100, 100 };
	currentSprite = 0;
	spriteAmount = 0;
	updateTime = 1.0f;
	time = 0.0f;
	direction = 1;
}

void Animation::setTexture(sf::String path)
{
	texture.loadFromFile(path);
	sprite.setTexture(texture);
}

void Animation::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Animation::setIndividualSpriteSize(int width, int height)
{
	IndividualSpriteSize.x = width;
	IndividualSpriteSize.y = height;
	sprite.setTextureRect(sf::IntRect(SpriteStartingPosition, IndividualSpriteSize));
}

void Animation::setSpriteStartingPosition(int x, int y)
{
	SpriteStartingPosition.x = x;
	SpriteStartingPosition.y = y;
	sprite.setTextureRect(sf::IntRect(SpriteStartingPosition, IndividualSpriteSize));
	currentSprite = 0;
	direction = 1;
}

void Animation::setUpdateTime(float time)
{
	updateTime = time;
}

void Animation::setSpriteAmount(int amount)
{
	spriteAmount = amount;
}

void Animation::setScale(float scale)
{
	sprite.setScale(scale, scale);
}

sf::Vector2i Animation::getIndividualSrpiteSize() const
{
	sf::Vector2i size;
	size.x = sprite.getGlobalBounds().width;
	size.y = sprite.getGlobalBounds().height;
	return size;
}

sf::Vector2f Animation::getPosition() const
{
	return sprite.getPosition();
}

void Animation::update(float deltaT)
{
	time += deltaT;
	if (time >= updateTime)
	{
		time = 0.0f;
		nextImage();
	}
}

void Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Animation::nextImage()
{
	SpriteStartingPosition.x += IndividualSpriteSize.x * direction;
	currentSprite += direction;
	sprite.setTextureRect(sf::IntRect(SpriteStartingPosition, IndividualSpriteSize));

	if (currentSprite <= 0 || currentSprite >= spriteAmount - 1)
	{
		direction = -direction;
	}

	/*SpriteStartingPosition.x += IndividualSpriteSize.x;
	currentSprite++;
	if (currentSprite >= spriteAmount - 1)
	{
		currentSprite = 0;
	}*/

	system("cls");
	printf("Sprite box: X:%d, Y:%d, WIDTH:%d, HEIGHT:%d\n", SpriteStartingPosition.x, SpriteStartingPosition.y, IndividualSpriteSize.x, IndividualSpriteSize.y);
	printf("CurrentSprite: %d\n", currentSprite);
	printf("amount of sprites: %d\n", spriteAmount);
}


