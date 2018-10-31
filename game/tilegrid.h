#pragma once
#include <iostream>
#include <vector>
#include "../dynamite/entity.h"

class TileGrid {
private:
	std::vector<Entity*> tiles;
public:
	TileGrid();
	Entity* GetEntityByTilePosition(Vector2 position);
	void HandleTilesOffset(Vector2 offset);
};