#ifndef PACMAN_H
#define PACMAN_H

#include "Vector2f.h"

struct SDL_Surface;

#include "Drawer.h"
#include "Avatar.h"
#include "World.h"
#include "Ghost.h"

class Pacman
{
public:
	static Pacman* Create(Drawer* aDrawer);
	Pacman();
	~Pacman(void);
	bool Update(float aTime);
	bool Draw();

	double angle;

	double GetAngle();

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

	Vector2f desired_direction;
	Vector2f direction;
	
	Avatar* myAvatar;
	Ghost* myGhost;
	World* myWorld;
};

#endif // PACMAN_H