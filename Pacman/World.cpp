#include "World.h"
#include <sstream>
#include <fstream>
#include <string>
#include "Dot.h"
#include "BigDot.h"
#include "Drawer.h"


World::World(void)
{
}
World::~World(void)
{
}
void World::Init()
{
	InitPathmap();
	InitDots();
	InitBigDots();
}

bool World::InitPathmap()
{
	std::string line;
	std::ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		unsigned int lineIndex = 0;
		int max_width = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				bool tunnel = (i == 0 || i == line.length() - 1) && line[i] == 'T';
				Tile* tile = new Tile(i, lineIndex, tunnel, (line[i] == 'x'));
				myPathmapTiles.push_back(tile);
			}

			lineIndex++;
			if (line.length() > max_width) {
				max_width = line.length();
			}
		}
		this->width = max_width;
		myfile.close();
	}
	return true;
}
bool World::InitDots()
{
	std::string line;
	std::ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == '.')
				{
					Dot* dot = new Dot(Vector2f(i*22, lineIndex*22));
					myDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}
	return true;
}
bool World::InitBigDots()
{
	std::string line;
	std::ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			std::getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == 'o')
				{
					BigDot* dot = new BigDot(Vector2f(i*22, lineIndex*22));
					myBigDots.push_back(dot);
				}
			}
			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

void World::Draw(Drawer* aDrawer)
{
	aDrawer->Draw("playfield.png");

	for(std::list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		Dot* dot = *list_iter;
		dot->Draw(aDrawer);
	}

	for(std::list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		BigDot* dot = *list_iter;
		dot->Draw(aDrawer);
	}
}

bool World::TileIsValid(int anX, int anY)
{
	for (Tile* tile : this->myPathmapTiles) {
		if (anX == tile->x && anY == tile->y && !tile->blocking)
			return true;
	}

	return false;
}

Tile* World::GetTile(int x, int y)
{
	for (Tile* tile : this->myPathmapTiles) {
		if (tile->x == x && tile->y == y)
		{
			return tile;
		}
	}
	return NULL;
}

bool World::TileIsTunnel(int x, int y) {
	Tile* tile = this->GetTile(x, y);
	if (tile == NULL) {
		return false;
	}
	else {
		return GetTile(x, y)->tunnel;
	}
}

bool World::HasIntersectedDot(const Vector2f& aPosition)
{
	for(std::list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		Dot* dot = *list_iter;
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			myDots.remove(dot);
			delete dot;
			return true;
		}
	}
	return false;
}

bool World::HasIntersectedBigDot(const Vector2f& aPosition)
{
	for(std::list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		BigDot* dot = *list_iter;
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			myBigDots.remove(dot);
			delete dot;
			return true;
		}
	}

	return false;
}

bool World::HasIntersectedCherry(const Vector2f& aPosition)
{
	return true;
}

void World::GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<Tile*>& aList)
{
	Tile* fromTile = GetTile(aFromX, aFromY);
	Tile* toTile = GetTile(aToX, aToY);

	for(std::list<Tile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		Tile* tile = *list_iter;
		tile->visited = false;
	}

	Pathfind(fromTile, toTile, aList);
}

bool World::ListDoesNotContain(Tile* aFromTile, std::list<Tile*>& aList)
{
	for(std::list<Tile*>::iterator list_iter = aList.begin(); list_iter != aList.end(); list_iter++)
	{
		Tile* tile = *list_iter;
		if (tile == aFromTile)
		{
			return false;
		}
	}
	return true;
}

bool SortFromGhostSpawn(Tile* a, Tile* b)
{
	unsigned int la = abs((int)a->x - 13) + abs((int)a->y - 13);
	unsigned int lb = abs((int)b->x - 13) + abs((int)b->y - 13);

    return la < lb;
}

bool World::Pathfind(Tile* aFromTile, Tile* aToTile, std::list<Tile*>& aList)
{
	aFromTile->visited = true;

	if (aFromTile->blocking)
		return false;

	if (aFromTile == aToTile)
		return true;

	std::list<Tile*> neighborList;

	Tile* up = GetTile(aFromTile->x, aFromTile->y - 1);
	if (up && !up->visited && ListDoesNotContain(up, aList))
		neighborList.push_front(up);

	Tile* down = GetTile(aFromTile->x, aFromTile->y + 1);
	if (down && !down->visited && !down->blocking && ListDoesNotContain(down, aList))
		neighborList.push_front(down);

	Tile* right = GetTile(aFromTile->x + 1, aFromTile->y);
	if (right && !right->visited && !right->blocking && ListDoesNotContain(right, aList))
		neighborList.push_front(right);

	Tile* left = GetTile(aFromTile->x - 1, aFromTile->y);
	if (left && !left->visited && !left->blocking && ListDoesNotContain(left, aList))
		neighborList.push_front(left);

	neighborList.sort(SortFromGhostSpawn);

	for(std::list<Tile*>::iterator list_iter = neighborList.begin(); list_iter != neighborList.end(); list_iter++)
	{
		Tile* tile = *list_iter;

		aList.push_back(tile);

		if (Pathfind(tile, aToTile, aList))
			return true;

		aList.pop_back();
	}

	return false;
}