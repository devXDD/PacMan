#include "GameEntity.h"
#include "Drawer.h"

GameEntity::GameEntity(const Vector2f& aPosition, std::vector<std::string> imgs)
:myPosition(aPosition)
,imgs(imgs)
,myIdMarkedForDeleteFlag(false)
{
}

GameEntity::~GameEntity(void)
{
}

bool GameEntity::Intersect(GameEntity* aGameEntity)
{

	return false;	
}

void GameEntity::Draw(Drawer* aDrawer)
{
	aDrawer->Draw(imgs.front(), (int)myPosition.myX + 220, (int)myPosition.myY + 60);
}
