/**
*	Filename: game.h
*
*	Description: Project Dynamite level editor, is a level editor that can save .dynamite files
*				 these files can be loaded by the framework as scenes
*	Version: 30/10/2018
*
*	� 2018, www.jensapplications.com
*/

#pragma once
#include "..\dynamite\math\vector2.h"
#include "..\dynamite\camera.h"

class Core;

class TileGrid;

class Game {
protected:
	TileGrid* grid;
	Camera* camera;
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
};
