#include "Cherry.h"

Cherry::Cherry(Vector2f aPosition)
	: StaticGameEntity(aPosition, std::vector<std::string>{"dot.png"})
{
}

Cherry::~Cherry(void)
{
}
