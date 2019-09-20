#include "Engine.h"
#include <Windows.h>
#include <iostream>


Engine::Engine()
{
	pWindow = nullptr;
	pMap = new Map();
}


Engine::~Engine()
{
	delete pWindow;
	pWindow = nullptr;
	delete pMap;
	pMap = nullptr;
}

void Engine::hideConsole(bool state)
{
	HWND console = GetConsoleWindow();
	if (state)
		ShowWindow(console, SW_HIDE);
	else
		ShowWindow(console, SW_SHOW);
}

void Engine::initialize()
{
	pWindow = new sf::RenderWindow(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::TITLE, sf::Style::Close);
	pWindow->setVerticalSyncEnabled(true);
}

void Engine::run()
{
	if (pWindow == nullptr)
	{
		initialize();
	}

	sf::Event eEvent;
	sf::Clock cClock;

	while (pWindow->isOpen())
	{
		while (pWindow->pollEvent(eEvent))
		{
			handleEvents(eEvent);
		}

		update(cClock.restart().asSeconds());

		pWindow->clear();
		render();
		pWindow->display();

	}
	pWindow->close();
}

void Engine::update(float deltaT)
{
	pMap->update(deltaT);
}

void Engine::render() const
{
	pWindow->draw(*pMap);
}

void Engine::handleEvents(sf::Event eEvent)
{
	if (eEvent.type == sf::Event::Closed)
	{
		pWindow->close();
		return;
	}

	if (eEvent.type == sf::Event::KeyPressed)
	{
		if (eEvent.key.code == sf::Keyboard::Escape)
		{
			pWindow->close();
			return;
		}

		pMap->handleEvents(eEvent);
	}
}