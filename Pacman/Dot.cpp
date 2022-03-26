#include "Dot.h"

Dot::Dot(Vector2f aPosition)
	: StaticGameEntity(aPosition, std::vector<std::string>{"Small_Dot_32.png"})
{
}

Dot::~Dot(void)
{
}
