/**
*	Filename: game.cpp
*
*	Version: 31/10/2018
*
*	© 2018, www.jensapplications.com
*/

#include "../dynamite/core.h"
#include "../dynamite/event/input.h"
#include "tilegrid.h"
#include "game.h"

Game::Game() {
	camera = new Camera();
	SceneManager::Instance()->CreateScene("_empty")->SetActiveCamera(camera);
	SceneManager::Instance()->SetActiveScene("_empty");

	grid = new TileGrid();
}

void Game::Update() {
	if (Input::Instance()->KeyPressed(KeyCode::ArrowRight)) {
		camera->SetPosition(Vector2(camera->GetXCoord() + 32, camera->GetYCoord()));
		grid->HandleTilesOffset(Vector2(32,0));
	}

	if (Input::Instance()->KeyPressed(KeyCode::ArrowLeft)) {
		camera->SetPosition(Vector2(camera->GetXCoord() - 32, camera->GetYCoord()));
		grid->HandleTilesOffset(Vector2(-32, 0));
	}

	if (Input::Instance()->KeyPressed(KeyCode::ArrowDown)) {
		camera->SetPosition(Vector2(camera->GetXCoord(), camera->GetYCoord() + 32));
		grid->HandleTilesOffset(Vector2(0, 32));
	}

	if (Input::Instance()->KeyPressed(KeyCode::ArrowUp)) {
		camera->SetPosition(Vector2(camera->GetXCoord(), camera->GetYCoord() - 32));
		grid->HandleTilesOffset(Vector2(0, -32));
	}
}