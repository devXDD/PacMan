#include "Avatar.h"


Avatar::Avatar(World& world, const Vector2f& aPosition)
: MovableGameEntity(world, aPosition, std::vector<std::string>{"closed_right_32.png", "closed_left_32.png", "closed_down_32.png", "closed_up_32.png", "open_right_32.png", "open_left_32.png", "open_down_32.png", "open_up_32.png"})
{
}
Avatar::~Avatar(void)
{

}

size_t sprite = 0;

void Avatar::Update(float aTime)
{
	int tileSize = 22;
	Vector2f destination(myNextTileX * tileSize, myNextTileY * tileSize);
	Vector2f direction = destination - myPosition;
	float distanceToMove = aTime * 70.f;
	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}

	bool mouth_closed = (bool) ((SDL_GetTicks() / 125)%2);

	if (direction.myX > 0) {
		sprite = 0;
	}
	else if (direction.myX < 0) {
		sprite = 1;
	}
	else if (direction.myY > 0) {
		sprite = 2;
	}
	else if (direction.myY < 0) {
		sprite = 3;
	}
	else {
		sprite = sprite % 4;
	}

	sprite = mouth_closed ? sprite : sprite + 4;
}

void Avatar::Draw(Drawer* aDrawer) {
	aDrawer->Draw(imgs.at(sprite), (int)myPosition.myX + 220, (int)myPosition.myY + 60);
}
