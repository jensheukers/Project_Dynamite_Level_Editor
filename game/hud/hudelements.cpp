/**
*	Filename: hudelements.cpp
*
*	Description: Source file for all hud elements in the editor
*	Version: 12/11/2018
*
*	© 2018, www.jensapplications.com
*/

#include "hudelements.h"
#include "../game.h"
#include "../../dynamite/core.h"
#include "../../dynamite/component/sprite.h"
#include "../../dynamite/component/collider.h"

MenuBar::MenuBar() {
	this->AddComponent<Sprite>()->CreateTexture(Core::Instance()->GetResourcePath("editor\\empty.tga"));
	this->GetComponent<Sprite>()->GetTexture()->SetColor(ColorRGB(20, 20, 20));

	this->GetComponent<Collider>()->SetBounds(Vector2((float)this->GetComponent<Sprite>()->GetTexture()->textureData->width,
		(float)this->GetComponent<Sprite>()->GetTexture()->textureData->height));

	this->SetScale(Vector2(Game::GetWindowDimensions().GetX() / 32, 1));

	SceneManager::Instance()->GetActiveScene()->AddUIElement(this);

	//Create the font
	font = new Font(Core::Instance()->GetResourcePath("font\\malgunGothic.tga"), Core::Instance()->GetResourcePath("font\\malgunGothic.csv"));

	//Create all the menu buttons
	
	//File Button
	Button* file = new Button();
	file->SetScale(Vector2(2.5f,1.0f));
	file->ignoreParentScaling = true;

	//File button Text
	Text* fileText = new Text(font);
	fileText->SetText("File");
	fileText->ignoreParentScaling = true;
	fileText->SetZLayer(5);

	//Selection Button
	Button* selection = new Button();
	selection->localPosition = Vector2(32 * 2.5f, 0);
	selection->SetScale(Vector2(2.5f, 1.0f));
	selection->ignoreParentScaling = true;

	//Selection button Text
	Text* selectionText = new Text(font);
	selectionText->SetText("Selection");
	selectionText->ignoreParentScaling = true;

	//Help Button
	Button* help = new Button();
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
	font = new Font(Core::Instance()->GetResourcePath("font\\malgunGothic.tga"), Core::Instance()->GetResourcePath("font\\malgunGothic.csv"));

	//Close Button
	Button* close = new Button();
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