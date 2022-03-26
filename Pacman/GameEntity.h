#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <vector>
#include <string>

#include "Vector2f.h"

class Drawer;

class GameEntity
{
public:
	GameEntity(const Vector2f& aPosition, std::vector<std::string> imgs);
	~GameEntity(void);

	Vector2f GetPosition() const { return myPosition; }
	void SetPosition(const Vector2f& aPosition){ myPosition = aPosition; }

	bool Intersect(GameEntity* aGameEntity);
	void Draw(Drawer* aDrawer);

	void MarkForDelete() { myIdMarkedForDeleteFlag = true; }
	bool IsMarkedForDelete() const { return myIdMarkedForDeleteFlag; }

protected:

	bool myIdMarkedForDeleteFlag;
	Vector2f myPosition;
	std::vector<std::string> imgs;
};

#endif // GAMEENTITY_H