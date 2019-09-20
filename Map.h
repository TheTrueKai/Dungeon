#pragma once
#include "Settings.h"
#include "Player.h"
#include "Renderable.h"
#include <vector>

typedef std::vector<std::vector<int>> intMatrix;

class Map : public Renderable
{
public:
	Map();
	~Map();

	// Geerbt über Renderable
	virtual void update(float deltaT) override;
	virtual void handleEvents(sf::Event sfEvent) override;
	virtual void render() const override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	sf::Vector2i CoordinateToIndex(float x, float y) const;

private:
	int cellWidth, cellHeight;
	sf::RectangleShape* pCell;
	intMatrix worldMap;
	const sf::Color getColor(int type) const;
	const sf::Texture getTexture(int type) const;
	sf::Texture yeet;

private:
	Player* pPlayer;
	sf::Vector2i playerPositionIndex;
	void calculatePlayerPositionIndex();
	void solvePlayerMapCollision();
};
