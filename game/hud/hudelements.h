/**
*	Filename: hudelements.h
*
*	Description: Header file for all hud elements in the editor
*	Version: 12/11/2018
*
*	© 2018, www.jensapplications.com
*/

#pragma once
#include "../../dynamite/ui/uielement.h"
#include "../../dynamite/ui/text.h"

// MENUBAR FORMAT
class MenuBar : public UIElement {
public:
	Font* font;
	MenuBar();
};

// WINDOW FORMAT
class Window : public UIElement {
public:
	Font* font;
	Window();
	Window(Vector2 size);
};

// BUTTON FORMAT
class Button : public UIElement {
public:
	ColorRGB onEnterColor;
	ColorRGB onLeaveColor;
	Button();
	void OnEnter() override;
	void OnLeave() override;
};