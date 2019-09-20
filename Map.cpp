#include "Map.h"



Map::Map()
{
	cellHeight = Settings::HEIGHT / Settings::MAP_HEIGHT;
	cellWidth = Settings::WIDTH / Settings::MAP_WIDTH;

	pCell = new sf::RectangleShape();
	pCell->setSize(sf::Vector2f(cellWidth, cellHeight));

	pPlayer = new Player();
	pPlayer->setPosition(100, 100);

	worldMap =
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,2,0,2,0,2,0,0,0,1 },
		{ 1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,2,2,2,0,2,0,0,0,1 },
		{ 1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,2,0,2,0,2,0,0,0,1 },
		{ 1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	yeet.loadFromFile("textures/map/greystone.png");
	pCell->setTexture(&yeet);
}


Map::~Map()
{
	delete pCell;
	pCell = nullptr;
}

void Map::update(float deltaT)
{
	pPlayer->update(deltaT);
	calculatePlayerPositionIndex();
	solvePlayerMapCollision();
}

void Map::handleEvents(sf::Event sfEvent)
{
	pPlayer->handleEvents(sfEvent);
}

void Map::render() const
{
}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < Settings::MAP_WIDTH; i++)
	{
		for (int j = 0; j < Settings::MAP_HEIGHT; j++)
		{
			int type;
			if ((type = worldMap[j][i]) != 0)
			{
				pCell->setFillColor(getColor(type));
				pCell->setPosition(i * cellWidth, j * cellHeight);
				target.draw(*pCell, states);
			}		
		}
	}
	/*pCell->setPosition(playerPositionIndex.x * cellWidth, playerPositionIndex.y * cellHeight);
	pCell->setFillColor(getColor(99));
	target.draw(*pCell, states);
	*/
	sf::RectangleShape rs; 
	sf::IntRect r = pPlayer->getHitBox();
	rs.setFillColor(sf::Color::Red);
	rs.setPosition(r.left, r.top);
	rs.setSize(sf::Vector2f(r.width, r.height));
	target.draw(rs);

	target.draw(*pPlayer);
}

sf::Vector2i Map::CoordinateToIndex(float x, float y) const
{
	return sf::Vector2i(x / cellWidth, y / cellHeight);
}

void Map::calculatePlayerPositionIndex()
{
	sf::Vector2i playerPos;

	playerPos.x += pPlayer->getPosition().x + pPlayer->getSize().x / 2;
	playerPos.y += pPlayer->getPosition().y + pPlayer->getSize().y / 1.5;

	playerPositionIndex.x = playerPos.x / cellWidth;
	playerPositionIndex.y = playerPos.y / cellHeight;
}

void Map::solvePlayerMapCollision()
{
	sf::IntRect hitbox = pPlayer->getHitBox();

	using namespace Settings::Movement;
	if (pPlayer->isMovingInDirection(PLAYER_UP[0], PLAYER_UP[1]))//The Player is Moving Up
	{
		//For Up and Down movement the Left and Right corner are checked
		sf::Vector2i leftIndex = CoordinateToIndex((float)hitbox.left, (float)hitbox.top);
		sf::Vector2i rightIndex = CoordinateToIndex((float)hitbox.left + hitbox.width, (float)hitbox.top);

		if (worldMap[leftIndex.y][leftIndex.x] != 0 || worldMap[rightIndex.y][rightIndex.x] != 0)
		{
			hitbox.top = (leftIndex.y + 1) * cellHeight + 1;
			pPlayer->setHitBox(hitbox);
		}
	}
	else if (pPlayer->isMovingInDirection(PLAYER_DOWN[0], PLAYER_DOWN[1]))//The Player is Moving Down
	{
		//For Up and Down movement the Left and Right corner are checked
		sf::Vector2i leftIndex = CoordinateToIndex((float)hitbox.left, (float)hitbox.top + hitbox.height);
		sf::Vector2i rightIndex = CoordinateToIndex((float)hitbox.left + hitbox.width, (float)hitbox.top + hitbox.height);

		if (worldMap[leftIndex.y][leftIndex.x] != 0 || worldMap[rightIndex.y][rightIndex.x] != 0)
		{
			hitbox.top = leftIndex.y * cellHeight - hitbox.height - 1;
			pPlayer->setHitBox(hitbox);
		}
	}
	else if (pPlayer->isMovingInDirection(PLAYER_LEFT[0], PLAYER_LEFT[1]))//The Player is Moving Left
	{

		//For Left and Right movement the top and bottom corner are checked
		sf::Vector2i topIndex = CoordinateToIndex((float)hitbox.left, (float)hitbox.top);
		sf::Vector2i bottomIndex = CoordinateToIndex((float)hitbox.left, (float)hitbox.top + hitbox.height);

		if (worldMap[topIndex.y][topIndex.x] != 0 || worldMap[bottomIndex.y][bottomIndex.x] != 0)
		{
			hitbox.left = (topIndex.x + 1) * cellWidth + 1;
			pPlayer->setHitBox(hitbox);
		}

	}
	else if (pPlayer->isMovingInDirection(PLAYER_RIGHT[0], PLAYER_RIGHT[1]))//The Player is Moving Right
	{
		sf::Vector2i topIndex = CoordinateToIndex((float)hitbox.left + hitbox.width, (float)hitbox.top);
		sf::Vector2i bottomIndex = CoordinateToIndex((float)hitbox.left + hitbox.width, (float)hitbox.top + hitbox.height);

		if (worldMap[topIndex.y][topIndex.x] != 0 || worldMap[bottomIndex.y][bottomIndex.x] != 0)
		{
			hitbox.left = topIndex.x * cellWidth - hitbox.width - 1;
			pPlayer->setHitBox(hitbox);
		}

	}
}

const sf::Color Map::getColor(int type) const
{
	switch (type)
	{
	case 0:
		return sf::Color::Black;
	case 1:
		return sf::Color(232, 162, 0);
	case 2:
		return sf::Color::Cyan;
	case 3:
		return sf::Color::Green;
	case 4:
		return sf::Color::Magenta;
	case 5:
		return sf::Color::Yellow;
	default:
		return sf::Color::White;
	}
}

const sf::Texture Map::getTexture(int type) const
{
	return yeet;
}
