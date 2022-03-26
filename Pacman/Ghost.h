#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"
#include "World.h"

class Ghost : public MovableGameEntity
{
public:
	Ghost(World& world, const Vector2f& aPosition);
	~Ghost(void);

	void Update(float aTime, World* aWorld);

	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	void Die(World* aWorld);

	void Draw(Drawer* aDrawer);

protected:

	int myDesiredMovementX;
	int myDesiredMovementY;

	std::list<Tile*> myPath;

};

#endif // GHOST_H