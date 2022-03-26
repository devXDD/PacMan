#include "BigDot.h"

BigDot::BigDot(Vector2f aPosition)
	: StaticGameEntity(aPosition, std::vector<std::string>{"Big_Dot_32.png"})
{
}

BigDot::~BigDot(void)
{
}
