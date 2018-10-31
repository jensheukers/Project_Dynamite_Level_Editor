#include "tilegrid.h"
#include "../dynamite/core.h"
#include "../dynamite/scenemanager.h"
#include "../dynamite/component/sprite.h"
#include "../dynamite/component/collider.h"
#include "../dynamite/physics/physics.h"

TileGrid::TileGrid() {
	if (!SceneManager::Instance()->GetActiveScene()) {
		std::cout << "DYNAMITE_LEVEL_EDITOR: Active Scene has to be set before calling TileGrid!" << std::endl;
		return;
	}
	
	for (int x = 0; x < Game::GetWindowDimensions().GetX(); x += 32) {
		for (int y = 0; y < Game::GetWindowDimensions().GetY(); y += 32) {
			Entity* tile = new Entity();
			tile->position = Vector2(x,y);
			tile->AddComponent<Sprite>()->SetTexture(Core::Instance()->GetResourcePath("editor\\tile.tga"));
			tile->AddComponent<Collider>()->SetBounds(Vector2(32, 32));
			SceneManager::Instance()->GetActiveScene()->AddEntity(tile);
			tiles.push_back(tile);
		}
	}
}

Entity* TileGrid::GetEntityByTilePosition(Vector2 position) {
	for (int i = 0; i < tiles.size(); i++) {
		if(Physics::InRangePoint(position, *tiles[i]->GetComponent<Collider>())) {
			return tiles[i];
		}
	}
	return nullptr;
}


void TileGrid::HandleTilesOffset(Vector2 offset) {
	for (int i = 0; i < tiles.size(); i++) {
		tiles[i]->position = Vector2(tiles[i]->position.GetX() + offset.GetX(), tiles[i]->position.GetY() + offset.GetY());
	}
}