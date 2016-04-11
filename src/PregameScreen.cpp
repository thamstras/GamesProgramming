#include "PregameScreen.h"

void transitToGame()
{
	//Scene::getScene().loadScene(SCENE_GAME_OURTURN);
}

PregameScreen::PregameScreen(SDL_Renderer * ren, std::string id)
{
	this->id = id;

	Scene& scene = Scene::getScene();
	
	this->gridWidth = scene.gridWidth;
	this->gridHeight = scene.gridHeight;

	grid = new bool[100];
	for (int i = 0; i < 100; i++)
		grid[i] = false;

	select = new StaticSprite("./assets/selectionSquare.png", ren, this->id + "_select");

	ship1 = new SwapSprite("./assets/shipblueprint-2.png", "./assets/shipblueprint-2r.png", ren, this->id + "_ship1");
	ship2 = new SwapSprite("./assets/shipblueprint-2.png", "./assets/shipblueprint-2r.png", ren, this->id + "_ship2");
	ship3 = new SwapSprite("./assets/shipblueprint-3.png", "./assets/shipblueprint-3r.png", ren, this->id + "_ship3");
	ship4 = new SwapSprite("./assets/shipblueprint-3.png", "./assets/shipblueprint-3r.png", ren, this->id + "_ship4");
	ship5 = new SwapSprite("./assets/shipblueprint-4.png", "./assets/shipblueprint-4r.png", ren, this->id + "_ship5");
	ship6 = new SwapSprite("./assets/shipblueprint-5.png", "./assets/shipblueprint-5r.png", ren, this->id + "_ship6");


	doneButton = new GUIButton(ren, "Done", -100, -100, transitToGame, this->id + "_doneButton");

	currentShip = 1;
	done = false;

	select->moveSprite(-100, -100);
	ship1->moveSprite(-100, -100);
	ship2->moveSprite(-100, -100);
	ship3->moveSprite(-100, -100);
	ship4->moveSprite(-100, -100);
	ship5->moveSprite(-100, -100);
	ship6->moveSprite(-100, -100);

	scene.registerRender(ship6);
	scene.registerRender(ship5);
	scene.registerRender(ship4);
	scene.registerRender(ship3);
	scene.registerRender(ship2);
	scene.registerRender(ship1);
	scene.registerRender(select);

	scene.registerRender(doneButton);
}

PregameScreen::~PregameScreen()
{
}

void PregameScreen::update(double simLength)
{
	MouseData mouse = Scene::getScene().mouseData;
	
	int mouseGridX = mouse.mouseX / gridWidth;
	int mouseGridY = mouse.mouseY / gridHeight;

	int selectX = mouseGridX * gridWidth;
	int selectY = mouseGridY * gridHeight;

	if (!done)
	{
		select->moveSprite(selectX, selectY);

		getCurrentShip()->moveSprite(selectX, selectY);

		if (mouse.leftMouseOnce)
		{
			int shipSize = getCurrentShipSize();
			int dir = !(getCurrentShip()->selectedSpriteA);
			if (fitsOnGrid(mouseGridX, mouseGridY, shipSize, dir))
			{
				placeOnGrid(mouseGridX, mouseGridY, shipSize, dir);
				currentShip++;

				if (currentShip > 6)
					showDoneButton();
			}
		}
		if (mouse.rightMouseOnce)
		{
			getCurrentShip()->swap();
		}
	}
}

void PregameScreen::render(SDL_Renderer * ren)
{
}



SwapSprite * PregameScreen::getCurrentShip()
{
	switch (currentShip)
	{
	case 1:
		return ship1;
	case 2:
		return ship2;
	case 3:
		return ship3;
	case 4:
		return ship4;
	case 5:
		return ship5;
	case 6:
		return ship6;
	default:
		return ship1;
	}
}

int PregameScreen::getCurrentShipSize()
{
	switch (currentShip)
	{
	case 1:
		return 2;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return 3;
	case 5:
		return 4;
	case 6:
		return 5;
	default:
		return 0;
	}
}

void PregameScreen::showDoneButton()
{
	done = true;
	select->moveSprite(-100, -100);
	doneButton->moveButton(400, 500);
	//Scene::getScene().p1Data = ;
	//Scene::getScene().p2Data = ;
}

bool PregameScreen::gridOpen(int X, int Y)
{
	if (X > 9 || Y > 9)
		return false;
	if (X < 0 || Y < 0)
		return false;
	int i = (Y * 10) + X;
	return !grid[i];
}

void PregameScreen::closeGrid(int X, int Y)
{
	if (X > 9 || Y > 9)
		return;
	if (X < 0 || Y < 0)
		return;
	int i = (Y * 10) + X;
	grid[i] = true;
}

bool PregameScreen::fitsOnGrid(int X, int Y, int size, int direction)
{
	bool fits = true;
	if (direction == 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (!gridOpen(X + i, Y))
			{
				fits = false;
				break;
			}
		}
	}
	else {
		for (int i = 0; i < size; i++)
		{
			if (!gridOpen(X, Y + i))
			{
				fits = false;
				break;
			}
		}
	}
	return fits;
}

void PregameScreen::placeOnGrid(int X, int Y, int size, int direction)
{
	if (direction == 0)
	{
		for (int i = 0; i < size; i++)
		{
			closeGrid(X + i, Y);
		}
	}
	else {
		for (int i = 0; i < size; i++)
		{
			closeGrid(X, Y + i);
		}
	}
}