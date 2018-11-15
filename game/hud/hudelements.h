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
private:
	Text * title;
public:
	Font* font;
	Window();
	void SetTitleText(std::string titlestr);
};

// WINDOW SPECIFIC
class FileWindow : public Window {
public:
	FileWindow();
};

// WINDOW SPECIFIC
class SelectionWindow : public Window {
public:
	SelectionWindow();
};

// WINDOW SPECIFIC
class HelpWindow : public Window {
public:
	HelpWindow();
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

//Button specific
class FileButton : public Button {
private:
	Window* _fileWindow;
public:
	FileButton();
	void OnClick(int btn) override;
};

class SelectionButton : public Button {
private:
	Window * _selectionWindow;
public:
	SelectionButton();
	void OnClick(int btn) override;
};

class HelpButton : public Button {
private:
	Window * _helpWindow;
public:
	HelpButton();
	void OnClick(int btn) override;
};

class WindowCloseButton : public Button {
private:
	Window * window;
public:
	WindowCloseButton(Window* window);
	void OnClick(int btn) override;
};
