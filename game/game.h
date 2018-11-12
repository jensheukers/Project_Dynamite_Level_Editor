/**
*	Filename: game.h
*
*	Description: Project Dynamite level editor, is a level editor that can save .dynamite files
*				 these files can be loaded by the framework as scenes
*	Version: 9/11/2018
*
*	© 2018, www.jensapplications.com
*/

#pragma once
#include "..\dynamite\math\vector2.h"
#include "..\dynamite\camera.h"
#include "..\dynamite\entity.h"
#include "..\dynamite\ui\text.h"
#include "hud\hudelements.h"

class Core;

class TileGrid;

class Game {
protected:
	MenuBar * menubar;
	TileGrid* grid;
	Camera* camera;
	Entity* currentTile;
	Entity* previousTile;
	Text* cameraPosText;
	bool gridEnabled;
public:

	/**
	* Constructor
	*/
	Game();

	/**
	* Returns the game title
	*/
	static const char* GetGameName() {
		return "Project Dynamite - Level Editor";
	}

	/**
	* Returns the dimensions of the window.
	*/
	static Vector2 GetWindowDimensions() {
		return Vector2(1080,720);
	}

	/**
	* Update method gets called each frame.
	*/
	virtual void Update();

	void DisableGrid();
};
