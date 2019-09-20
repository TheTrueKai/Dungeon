#pragma once
#include "Renderable.h"
#include "Animation.h"
#include "Settings.h"


class Player : public Renderable
{
public:
	Player();
	~Player();

	// Geerbt über Renderable
	virtual void update(float deltaT) override;
	virtual void handleEvents(sf::Event sfEvent) override;
	virtual void render() const override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool isMovingInDirection(const sf::Vector2f& direction) const;
	bool isMovingInDirection(float x, float y) const;

	bool isMovingUp() const;
	bool isMovingDown() const;
	bool isMovingRight() const;
	bool isMovingLeft() const;

	sf::Vector2f getPosition() const;
	sf::Vector2i getSize() const;
	sf::IntRect getHitBox() const;

	void setHitBox(const sf::IntRect& hitbox);
	void setPosition(const sf::Vector2f& pos);
	void setPosition(float x, float y);

private:
	void solveCollision();
	void move();

private:
	Animation animation;
	sf::Vector2f moveDirection;
	sf::Vector2f position;
	sf::IntRect hitbox;
	bool moving;
	float walking_speed;
};

