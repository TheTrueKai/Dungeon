#include "Engine.h"

int main()
{
	Engine engine;
	engine.initialize();
	engine.hideConsole(false);
	engine.run();

	return 0;
}