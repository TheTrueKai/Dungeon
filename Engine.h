#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Map.h"

class Engine
{
public:
	Engine();
	~Engine();

public:
	void hideConsole(bool state);
	void initialize();
	void run();

private:
	void update(float deltaT);
	void render() const;
	void handleEvents(sf::Event eEvent);


private:
	sf::RenderWindow* pWindow;
	Map* pMap;
	unsigned int nWidth;
	unsigned int nHeight;

};

