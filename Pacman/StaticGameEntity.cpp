#include "StaticGameEntity.h"

StaticGameEntity::StaticGameEntity(Vector2f aPosition, std::vector<std::string> imgs)
: GameEntity(aPosition, imgs)
{
}

StaticGameEntity::~StaticGameEntity(void)
{
}
