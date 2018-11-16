/**
*	Filename: hudelements.cpp
*
*	Description: Source file for all hud elements in the editor
*	Version: 16/11/2018
*
*	© 2018, www.jensapplications.com
*/

#include "hudelements.h"
#include "../game.h"
#include "../../dynamite/core.h"
#include "../../dynamite/resourcemanager.h"
#include "../../dynamite/component/sprite.h"
#include "../../dynamite/component/collider.h"
#include "../../dynamite/physics/physics.h"

MenuBar::MenuBar() {
	this->AddComponent<Sprite>()->CreateTexture(Core::Instance()->GetResourcePath("editor\\empty.tga"));
	this->GetComponent<Sprite>()->GetTexture()->SetColor(ColorRGB(20, 20, 20));

	this->GetComponent<Collider>()->SetBounds(Vector2((float)this->GetComponent<Sprite>()->GetTexture()->textureData->width,
		(float)this->GetComponent<Sprite>()->GetTexture()->textureData->height));

	this->SetScale(Vector2(Game::GetWindowDimensions().GetX() / 32, 1));

	SceneManager::Instance()->GetActiveScene()->AddUIElement(this);

	//Create the font
	font = ResourceManager::Instance()->GetFont("malgunGothic");

	//Create all the menu buttons
	
	//File Button
	FileButton* file = new FileButton();
	file->SetScale(Vector2(2.5f,1.0f));
	file->ignoreParentScaling = true;

	//File button Text
	Text* fileText = new Text(font);
	fileText->SetText("File");
	fileText->ignoreParentScaling = true;
	fileText->SetZLayer(5);

	//Selection Button
	SelectionButton* selection = new SelectionButton();
	selection->localPosition = Vector2(32 * 2.5f, 0);
	selection->SetScale(Vector2(2.5f, 1.0f));
	selection->ignoreParentScaling = true;

	//Selection button Text
	Text* selectionText = new Text(font);
	selectionText->SetText("Selection");
	selectionText->ignoreParentScaling = true;

	//Help Button
	HelpButton* help = new HelpButton();
	help->localPosition = Vector2(64 * 2.5f, 0);
	help->SetScale(Vector2(2.5f, 1.0f));
	help->ignoreParentScaling = true;

	//Help button Text
	Text* helpText = new Text(font);
	helpText->SetText("Help");
	helpText->ignoreParentScaling = true;

	//Add Childs
	this->AddChild(file);
	this->AddChild(selection);
	this->AddChild(help);

	file->AddChild(fileText);
	selection->AddChild(selectionText);
	help->AddChild(helpText);
}

Window::Window() {
	this->AddComponent<Sprite>()->CreateTexture(Core::Instance()->GetResourcePath("editor\\empty.tga"));
	this->GetComponent<Sprite>()->GetTexture()->SetColor(ColorRGB(20, 20, 20));

	this->GetComponent<Collider>()->SetBounds(Vector2((float)this->GetComponent<Sprite>()->GetTexture()->textureData->width,
		(float)this->GetComponent<Sprite>()->GetTexture()->textureData->height));

	this->SetScale(Vector2(15, 10));

	SceneManager::Instance()->GetActiveScene()->AddUIElement(this);

	//Create the font
	Font* font = ResourceManager::Instance()->GetFont("malgunGothic");

	title = new Text(font);
	title->localPosition = Vector2(10,5);

	this->AddChild(title);

	//Close Button
	WindowCloseButton* close = new WindowCloseButton(this);
	close->onEnterColor = ColorRGB(255,0,0);
	close->onLeaveColor = ColorRGB(150, 0, 0);
	close->GetComponent<Sprite>()->GetTexture()->SetColor(close->onLeaveColor);
	close->localPosition = Vector2((this->GetComponent<Sprite>()->GetTexture()->textureData->width * this->GetScale().GetX()) - this->GetComponent<Sprite>()->GetTexture()->textureData->width, 0);
	close->ignoreParentScaling = true;

	this->AddChild(close);

	// Add close cross to close button
	Text* closeCross = new Text(font);
	closeCross->SetText("X");
	closeCross->localPosition = Vector2(10,6);
	closeCross->ignoreParentScaling = true;

	close->AddChild(closeCross);
}

void Window::Update() {
	//Handle window positions
	if (Physics::InRangePoint(Input::Instance()->GetMousePositionRelativeToScreen(), this->GetComponent<Collider>())) {
		if (Input::Instance()->ButtonPressed(2)) {
			_movingWindow = true;
		}
	}

	if (_movingWindow && !Input::Instance()->ButtonPressed(2)) {
		_movingWindow = false;
	}

	if (_movingWindow) {
		this->position = Input::Instance()->GetMousePositionRelativeToScreen();
	}
}

void Window::SetTitleText(std::string titlestr) {
	title->SetText(titlestr);
}

//Windows
FileWindow::FileWindow() {
	this->SetTitleText("File");
}


SelectionWindow::SelectionWindow() {
	this->SetTitleText("Selection");
}

HelpWindow::HelpWindow() {
	this->SetTitleText("Help");

	//Controls
	Text* ctrl1 = new Text(ResourceManager::Instance()->GetFont("malgunGothic"));
	ctrl1->SetText("~ = Open Menu");
	ctrl1->localPosition = Vector2(10, 2 * 32);
	this->AddChild(ctrl1);

	Text* ctrl2 = new Text(ResourceManager::Instance()->GetFont("malgunGothic"));
	ctrl2->SetText("RMB = Place Current Entity");
	ctrl2->localPosition = Vector2(10, 3 * 32);
	this->AddChild(ctrl2);

	Text* ctrl3 = new Text(ResourceManager::Instance()->GetFont("malgunGothic"));
	ctrl3->SetText("LMB = Remove Current Entity");
	ctrl3->localPosition = Vector2(10, 4 * 32);
	this->AddChild(ctrl3);

	Text* ctrl4 = new Text(ResourceManager::Instance()->GetFont("malgunGothic"));
	ctrl4->SetText("Left/Right Arrow = Move Camera Horizontal");
	ctrl4->localPosition = Vector2(10, 5 * 32);
	this->AddChild(ctrl4);

	Text* ctrl5 = new Text(ResourceManager::Instance()->GetFont("malgunGothic"));
	ctrl5->SetText("Up/Down Arrow = Move Camera Vertical");
	ctrl5->localPosition = Vector2(10, 6 * 32);
	this->AddChild(ctrl5);

	//Credits
	Text* credits = new Text(ResourceManager::Instance()->GetFont("malgunGothic"));
	credits->SetText("Project Dynamite Level Editor, Created by Jens Heukers");
	credits->localPosition = Vector2(10, 8 * 32);
	this->AddChild(credits);

	Text* version = new Text(ResourceManager::Instance()->GetFont("malgunGothic"));
	version->SetText("Version: ");
	version->Append(Game::GetVersion());
	version->localPosition = Vector2(10, 9 * 32);
	this->AddChild(version);
}

Button::Button() {
	this->onEnterColor = ColorRGB(100, 100, 100);
	this->onLeaveColor = ColorRGB(40, 40, 40);

	this->AddComponent<Sprite>()->CreateTexture(Core::Instance()->GetResourcePath("editor\\empty.tga"));
	this->GetComponent<Sprite>()->GetTexture()->SetColor(onLeaveColor);

	this->GetComponent<Collider>()->SetBounds(Vector2((float)this->GetComponent<Sprite>()->GetTexture()->textureData->width,
		(float)this->GetComponent<Sprite>()->GetTexture()->textureData->height));
}

void Button::OnEnter() {
	this->GetComponent<Sprite>()->GetTexture()->SetColor(onEnterColor);
}

void Button::OnLeave() {
	this->GetComponent<Sprite>()->GetTexture()->SetColor(onLeaveColor);
}

FileButton::FileButton() {
	this->_fileWindow = new FileWindow();
	_fileWindow->position = Vector2(0, 32); //TEMPORARY HARDCODED

	this->_fileWindow->SetActive(false);
}

void FileButton::OnClick(int btn) {
	if (!this->_fileWindow->IsActive()) {
		this->_fileWindow->SetActive(true);
	}
	else {
		this->_fileWindow->SetActive(false);
	}
}

SelectionButton::SelectionButton() {
	this->_selectionWindow = new SelectionWindow();
	_selectionWindow->position = Vector2(_selectionWindow->GetScale().GetX() * 32, 32); //TEMPORARY HARDCODED

	this->_selectionWindow->SetActive(false);
}

void SelectionButton::OnClick(int btn) {
	if (!this->_selectionWindow->IsActive()) {
		this->_selectionWindow->SetActive(true);
	}
	else {
		this->_selectionWindow->SetActive(false);
	}
}

HelpButton::HelpButton() {
	this->_helpWindow = new HelpWindow();
	_helpWindow->position = Vector2(0, (_helpWindow->GetScale().GetY() * 32) + 32); //TEMPORARY HARDCODED

	this->_helpWindow->SetActive(false);
}

void HelpButton::OnClick(int btn) {
	if (!this->_helpWindow->IsActive()) {
		this->_helpWindow->SetActive(true);
	}
	else {
		this->_helpWindow->SetActive(false);
	}
}


WindowCloseButton::WindowCloseButton(Window* window) {
	this->window = window;
}

void WindowCloseButton::OnClick(int btn) {
	this->window->SetActive(false);
}