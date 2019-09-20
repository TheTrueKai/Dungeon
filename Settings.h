#pragma once

#define exco extern constexpr

namespace Settings
{

	exco unsigned int FPS = 30;
	exco unsigned int WIDTH = 1536;
	exco unsigned int HEIGHT = 1536;
	exco char* TITLE = "Ray Casting Test";
	exco char* PLAYER_TEXTURE = "textures/characters/Character.png";
	exco unsigned int MAP_WIDTH = 24;
	exco unsigned int MAP_HEIGHT = 24;

	namespace Movement {
		exco float PLAYER_UP[2] = { 0, -1 };
		exco float PLAYER_DOWN[2] = { 0, 1 };
		exco float PLAYER_LEFT[2] = { -1, 0 };
		exco float PLAYER_RIGHT[2] = { 1, 0 };
	}
}