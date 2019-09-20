#pragma once
#include <SFML\Graphics.hpp>

class Animation : public sf::Drawable
{
public:
	Animation();
	~Animation()
	{
	}

	void setTexture(sf::String path);
	void setPosition(float x, float y);
	void setIndividualSpriteSize(int width, int height);
	void setSpriteStartingPosition(int x, int y);
	void setUpdateTime(float time);
	void setSpriteAmount(int amount);
	void setScale(float scale);


	sf::Vector2i getIndividualSrpiteSize() const;
	sf::Vector2f getPosition() const;

	void update(float deltaT);

	// Geerbt über Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	void nextImage();

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i SpriteStartingPosition;
	sf::Vector2i IndividualSpriteSize;
	float time;
	float updateTime;
	int currentSprite;
	int spriteAmount;
	int direction;
};

