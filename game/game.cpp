/**
*	Filename: game.cpp
*
*	Version: 12/11/2018
*
*	© 2018, www.jensapplications.com
*/

#include "..\dynamite\core.h"
#include "..\dynamite\component\sprite.h"
#include "..\dynamite\event\input.h"
#include "tilegrid.h"
#include "game.h"

Game::Game() {
	camera = new Camera();
	SceneManager::Instance()->CreateScene("_empty")->SetActiveCamera(camera);
	SceneManager::Instance()->SetActiveScene("_empty");

	grid = new TileGrid();
	gridEnabled = true;

	ResourceManager::Instance()->AddFont("malgunGothic", Core::Instance()->GetResourcePath("font\\malgunGothic.tga"), Core::Instance()->GetResourcePath("font\\malgunGothic.csv"));

	cameraPosText = new Text(ResourceManager::Instance()->GetFont("malgunGothic"));

	menubar = new MenuBar();
	menubar->SetActive(false);

	SceneManager::Instance()->GetActiveScene()->AddUIElement(cameraPosText);
}

void Game::Update() {
	if (cameraPosText->IsActive()) {
		cameraPosText->SetText("Camera Position : ");
		cameraPosText->Append(std::to_string(camera->GetXCoord()));
		cameraPosText->Append(" , ");
		cameraPosText->Append(std::to_string(camera->GetYCoord()));
	}

	if (Input::Instance()->KeyPressed(KeyCode::Grave)) {
		if (this->gridEnabled) {
			this->DisableGrid();
			cameraPosText->SetActive(false);
			menubar->SetActive(true);
		}
		else {
			currentTile->GetComponent<Sprite>()->SetTexture(Core::Instance()->GetResourcePath("editor\\tile_selected.tga"));
			this->gridEnabled = true;
			cameraPosText->SetActive(true);
			menubar->SetActive(false);
		}
	}

	//Handle Grid

	if (!gridEnabled) {
		return;
	}

	if (grid->GetEntityByTilePosition(Input::Instance()->GetMousePosition())) {
		currentTile = grid->GetEntityByTilePosition(Input::Instance()->GetMousePosition());
		if (currentTile != previousTile) {
			currentTile->GetComponent<Sprite>()->SetTexture(Core::Instance()->GetResourcePath("editor\\tile_selected.tga"));

			if (previousTile) {
				previousTile->GetComponent<Sprite>()->SetTexture(Core::Instance()->GetResourcePath("editor\\tile.tga"));
			}
		}

		previousTile = grid->GetEntityByTilePosition(Input::Instance()->GetMousePosition());
	}

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

void Game::DisableGrid() {
	this->gridEnabled = false;
	currentTile->GetComponent<Sprite>()->SetTexture(Core::Instance()->GetResourcePath("editor\\tile.tga"));
}