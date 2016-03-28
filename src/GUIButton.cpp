#include "GUIButton.h"

GUIButton::GUIButton(SDL_Renderer* ren, std::string buttonText, int x, int y, void (*callback)(), std::string ID)
{
	this->id = ID;
	onClick = callback;

	_x = x;
	_y = y;

	//make sprite;
	std::string spritePath = "./assets/buttonTex.png";
	sprite = new StaticSprite(spritePath, ren, this->id + "_sprite");
	
	//make text;
	std::string fontPath = "./assets/Hack-Regular.ttf";
	text = new TextSprite(fontPath, 16, buttonText, ren, this->id + "_text");
	
	//arrange everything
	sprite->moveSprite(x, y);
	text->moveString(x + 5, y + 5);
	SDL_Rect textBounds = text->getBoundingBox();
	_width = textBounds.w + 10;
	_height = textBounds.h + 10;
	sprite->scaleSprite(_width / 10, _height / 10);

	Scene::getScene().registerRender(sprite);
	Scene::getScene().registerRender(text);
}

GUIButton::~GUIButton()
{
}

void GUIButton::update(double simLength)
{
	Scene& scene = Scene::getScene();
	MouseData& data = scene.mouseData;
	if (data.leftMouseOnce)
	{
		if (data.mouseX > _x && data.mouseX < _x + _width)
			if (data.mouseY > _y && data.mouseY < _y + _height)
			{
				std::cout << "Clicked" << std::endl;
				onClick();
			}
	}
}

void GUIButton::render(SDL_Renderer * ren)
{
}
