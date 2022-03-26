#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <iostream>
#include "Vector2f.h"

class Drawer;
class Dot;
class BigDot;
class Cherry;

struct Tile {
	int x;
	unsigned int y;

	bool tunnel;
	bool blocking;

	bool visited;

	Tile(int x, int y, bool tunnel, bool blocking): x(x), y(y), tunnel(tunnel), blocking(blocking), visited(false) {}
};
typedef struct Tile Tile;

class World
{
public:
	World(void);
	~World(void);

	World::World(const World& old) {
		std::cout << "NEW" << std::endl;
	}

	void Init();

	void Draw(Drawer* aDrawer);
	bool TileIsValid(int anX, int anY);
	
	bool TileIsTunnel(int x, int y);

	bool HasIntersectedDot(const Vector2f& aPosition);
	bool HasIntersectedBigDot(const Vector2f& aPosition);
	bool HasIntersectedCherry(const Vector2f& aPosition);


	void GetPath(int aFromX, int aFromY, int aToX, int aToY, std::list<Tile*>& aList);

	int width = 0;

private:

	Tile* GetTile(int aFromX, int aFromY);
	bool Pathfind(Tile* aFromTile, Tile* aToTile, std::list<Tile*>& aList);
	bool ListDoesNotContain(Tile* aFromTile, std::list<Tile*>& aList);


	bool InitPathmap();
	bool InitDots();
	bool InitBigDots();

	std::list<Tile*> myPathmapTiles;
	std::list<Dot*> myDots;
	std::list<BigDot*> myBigDots;
	std::list<Cherry*> myCherry;
};

#endif // WORLD_H