#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(World& world, const Vector2f& aPosition, std::vector<std::string> imgs): GameEntity(aPosition, imgs), world(world)
{
	myCurrentTileX = myNextTileX =  myPosition.myX / 22;
	myCurrentTileY = myNextTileY =  myPosition.myY / 22;
}

MovableGameEntity::~MovableGameEntity(void)
{
}

bool MovableGameEntity::IsAtDestination()
{
	return myCurrentTileX == myNextTileX && myCurrentTileY == myNextTileY;
}

void MovableGameEntity::SetNextTile(int anX, int anY)
{
	int left_edge = 0;
	int right_edge = world.width - 1;
	/*std::cout << "Left: " << anX << std::endl;
	std::cout << "Right: " << anY << std::endl;*/
	if (world.TileIsTunnel(anX, anY)) {
		if (anX == left_edge) {
			myCurrentTileX = right_edge;
			myPosition.myX = myCurrentTileX * 22;
			myNextTileX = myCurrentTileX;
		}
		else if (anX == right_edge) {
			myCurrentTileX = left_edge;
			myPosition.myX = myCurrentTileX * 22;
			myNextTileX = myCurrentTileX;
		}
		else {
			myNextTileX = anX;
		}
	}
	else {
		myNextTileX = anX;
	}
	myNextTileY = anY;

}
