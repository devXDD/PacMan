#ifndef PACMAN_H
#define PACMAN_H
#include "Vector2f.h"
struct SDL_Surface;
class Drawer;
class Avatar;
class World;
class Ghost;
class Pacman
{
public:
	static Pacman* Create(Drawer* aDrawer);
	~Pacman(void);
	bool Update(float aTime);
	bool Draw();
	Vector2f myNextMovement;
	Vector2f GetNextMovement();

	bool shouldUpdate();
	bool shouldUp;

private:
	Pacman(Drawer* aDrawer);
	bool Init();
	bool UpdateInput();
	void MoveAvatar();
	bool CheckEndGameCondition();
	Drawer* myDrawer;
	float myTimeToNextUpdate;
	float myGhostGhostCounter;
	int myLives;
	int myScore;
	int myFps;
	
	Avatar* myAvatar;
	Ghost* myGhost;
	World* myWorld;
};

#endif // PACMAN_H