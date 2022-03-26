#ifndef MOVABLEGAMEENTITY_H
#define MOVABLEGAMEENTITY_H

#include "Drawer.h"
#include "World.h"
#include "GameEntity.h"
#include "Vector2f.h"
#include "SDL.h"

class MovableGameEntity : public GameEntity
{
public:
	MovableGameEntity(World& world, const Vector2f& aPosition, std::vector<std::string> imgs);
	~MovableGameEntity(void);

	void SetNextTile(int anX, int anY);
	int GetCurrentTileX() const { return myCurrentTileX; }
	int GetCurrentTileY() const { return myCurrentTileY; }

	bool IsAtDestination();

protected:

	World& world;

	int myCurrentTileX;
	int myCurrentTileY;

	int myNextTileX;
	int myNextTileY;

};

#endif // MOVABLEGAMEENTITY_H