#ifndef AVATAR_H
#define AVATAR_H

#include "MovableGameEntity.h"
#include "Vector2f.h"

class Avatar : public MovableGameEntity
{
public:
	Avatar(World& world, const Vector2f& aPosition);
	~Avatar(void);

	void Update(float aTime);

	void Draw(Drawer* aDrawer);

private:


};

#endif //AVATAR_H