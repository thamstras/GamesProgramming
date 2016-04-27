#include "PregameScreen.h"

void transitToGame()
{
	// TODO: Finish transition to Game
	//Scene::getScene().turn = 1;
	//Scene::getScene().loadScene(SCENE_GAME_OURTURN);
	Scene::getScene().startGame();
}

PregameScreen::PregameScreen(SDL_Renderer * ren, std::string id) : RenderObject(id)
{

	Scene& scene = Scene::getScene();
	
	this->gridWidth = scene.gridWidth;
	this->gridHeight = scene.gridHeight;

	grid = new bool[100];
	for (int i = 0; i < 100; i++)
		grid[i] = false;

	select = new StaticSprite("selectionsquare", ren, this->id + "_select");

	ship1 = new SwapSprite("shipblueprint-2", "shipblueprint-2r", ren, this->id + "_ship1");
	ship2 = new SwapSprite("shipblueprint-2", "shipblueprint-2r", ren, this->id + "_ship2");
	ship3 = new SwapSprite("shipblueprint-3", "shipblueprint-3r", ren, this->id + "_ship3");
	ship4 = new SwapSprite("shipblueprint-3", "shipblueprint-3r", ren, this->id + "_ship4");
	ship5 = new SwapSprite("shipblueprint-4", "shipblueprint-4r", ren, this->id + "_ship5");
	ship6 = new SwapSprite("shipblueprint-5", "shipblueprint-5r", ren, this->id + "_ship6");


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
	//scene.registerRender(select);

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
	else {
		// Check if remote ready
		//		transitionToGame();
		if (Scene::getScene().remotePlayer->getReady())
			transitToGame();
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
	//doneButton->moveButton(400, 500);
	ShipData s1 = { 2, ship1->getX()/60, ship1->getY()/60, !(ship1->selectedSpriteA) };
	ShipData s2 = { 2, ship2->getX()/60, ship2->getY()/60, !(ship2->selectedSpriteA) };
	ShipData s6 = { 5, ship6->getX()/60, ship6->getY()/60, !(ship6->selectedSpriteA) };
	ShipData s3 = { 3, ship3->getX()/60, ship3->getY()/60, !(ship3->selectedSpriteA) };
	ShipData s4 = { 3, ship4->getX()/60, ship4->getY()/60, !(ship4->selectedSpriteA) };
	ShipData s5 = { 4, ship5->getX()/60, ship5->getY()/60, !(ship5->selectedSpriteA) };
	Scene::getScene().p1Data.ships[0] = s1;
	Scene::getScene().p1Data.ships[1] = s2;
	Scene::getScene().p1Data.ships[2] = s3;
	Scene::getScene().p1Data.ships[3] = s4;
	Scene::getScene().p1Data.ships[4] = s5;
	Scene::getScene().p1Data.ships[5] = s6;
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
