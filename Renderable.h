#pragma once
#include <SFML\Graphics.hpp>

class Renderable : public sf::Drawable
{
	virtual void update(float deltaT) = 0;
	virtual void handleEvents(sf::Event sfEvent) = 0;
	virtual void render() const = 0;

	// Geerbt über Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;
};