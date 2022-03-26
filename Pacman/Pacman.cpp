#include "Pacman.h"
#include "Drawer.h"
#include "SDL.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Avatar.h"
#include "World.h"
#include "Ghost.h"

Pacman::Pacman()
{

}

Pacman* Pacman::Create(Drawer* aDrawer)
{
	Pacman* pacman = new Pacman(aDrawer);

	if (!pacman->Init())
	{
		delete pacman;
		pacman = NULL;
	}
	return pacman;
}
Pacman::Pacman(Drawer* aDrawer): myDrawer(aDrawer), myTimeToNextUpdate(0.f), desired_direction(-1.f, 0.f), direction(-1.f,0.f), myScore(0), myFps(0), myLives(3), myGhostGhostCounter(0.f)
{
	myWorld = new World();
	myAvatar = new Avatar(*myWorld, Vector2f(13 * 22, 22 * 22));
	myGhost = new Ghost(*myWorld, Vector2f(13 * 22, 13 * 22));
}
Pacman::~Pacman(void)
{
}
bool Pacman::Init()
{
	myWorld->Init();

	return true;
}
bool Pacman::Update(float aTime)
{
	if (!UpdateInput())
		return false;

	if (CheckEndGameCondition())
	{
		myDrawer->DrawText("You win!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);
		return true;
	}
	else if (myLives <= 0)
	{
		myDrawer->DrawText("You lose!", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 70);	
		return true;
	}

	MoveAvatar();
	myAvatar->Update(aTime);
	myGhost->Update(aTime, myWorld);

	if (myWorld->HasIntersectedDot(myAvatar->GetPosition()))
		myScore += 10;

	myGhostGhostCounter -= aTime;

	if (myWorld->HasIntersectedBigDot(myAvatar->GetPosition()))
	{
		myScore += 20;
		myGhostGhostCounter = 20.f;
		myGhost->myIsClaimableFlag = true;
	}

	if (myGhostGhostCounter <= 0)
	{
		myGhost->myIsClaimableFlag = false;
	}

	if ((myGhost->GetPosition() - myAvatar->GetPosition()).Length() < 10.f)
	{
		if (myGhostGhostCounter <= 0.f)
		{
			myLives--;

			myAvatar->SetPosition(Vector2f(13*22,22*22));
			myGhost->SetPosition(Vector2f(13*22,13*22));
		}
		else if (myGhost->myIsClaimableFlag && !myGhost->myIsDeadFlag)
		{
			myScore += 50;
			myGhost->myIsDeadFlag = true;
			myGhost->Die(myWorld);
		}
	}
	
	if (aTime > 0)
		myFps = (int) (1 / aTime);

	return true;
}


bool Pacman::UpdateInput()
{
	SDL_PumpEvents();
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	

	if (keystate[SDL_SCANCODE_UP])
	{
		desired_direction = Vector2f(0, -1);
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		desired_direction = Vector2f(0, 1);
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		desired_direction = Vector2f(1, 0);
	}
	else if (keystate[SDL_SCANCODE_LEFT])
	{
		desired_direction = Vector2f(-1, 0);
	}

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	return true;
}

double Pacman::GetAngle()
{
	return angle;
}

void Pacman::MoveAvatar()
{
	if (myAvatar->IsAtDestination())
	{
		int desired_NextTileX = myAvatar->GetCurrentTileX() + desired_direction.myX;
		int desired_NextTileY = myAvatar->GetCurrentTileY() + desired_direction.myY;

		if (myWorld->TileIsValid(desired_NextTileX, desired_NextTileY)) {
			direction = desired_direction;
			myAvatar->SetNextTile(desired_NextTileX, desired_NextTileY);
		}
		else {
			int nextTileX = myAvatar->GetCurrentTileX() + direction.myX;
			int nextTileY = myAvatar->GetCurrentTileY() + direction.myY;

			if (myWorld->TileIsValid(nextTileX, nextTileY))
			{
				myAvatar->SetNextTile(nextTileX, nextTileY);
			}
		}

	}
}

bool Pacman::CheckEndGameCondition()
{
	return false;
}

bool Pacman::Draw()
{
	myWorld->Draw(myDrawer);
	myAvatar->Draw(myDrawer);
	myGhost->Draw(myDrawer);

	std::string scoreString;
	std::stringstream scoreStream;
	scoreStream << myScore;
	scoreString = scoreStream.str();
	myDrawer->DrawText("Score", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 50);
	myDrawer->DrawText(scoreString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 90, 50);

	std::string livesString;
	std::stringstream liveStream;
	liveStream << myLives;
	livesString = liveStream.str();
	myDrawer->DrawText("Lives", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 80);
	myDrawer->DrawText(livesString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 90, 80);

	myDrawer->DrawText("FPS", "freefont-ttf\\sfd\\FreeMono.ttf", 880, 50);
	std::string fpsString;
	std::stringstream fpsStream;
	fpsStream << myFps;
	fpsString = fpsStream.str();
	myDrawer->DrawText(fpsString.c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 930, 50);

	return true;
}
