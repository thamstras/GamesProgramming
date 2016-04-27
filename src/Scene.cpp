#include "Scene.h"

#include <iostream>
#include <string>

#include "TestScreen.h"
#include "PregameScreen.h"
#include "GameGrid.h"

Scene* Scene::_theScene;

Scene& Scene::getScene() 
{
	if (_theScene == NULL) _theScene = new Scene();
	return *_theScene;
}

// Intended to be called once per frame from the main loop by the input handling.
// Responsible for updating mouse state and setting/unsetting the single press inputs.
void Scene::updateMouseData(float x, float y, bool left, bool right)
{
	mouseData.leftMouseOnce = false;
	mouseData.rightMouseOnce = false;

	mouseData.mouseX = x;
	mouseData.mouseY = y;
	if (mouseData.leftMouse != left)
	{
		mouseData.leftMouse = left;
		if (left)
		{
			mouseData.leftMouseOnce = true;
		}
	}
	if (mouseData.rightMouse != right)
	{
		mouseData.rightMouse = right;
		if (right)
		{
			mouseData.rightMouseOnce = true;
		}
	}
}

void Scene::sendGrid()
{
	remotePlayer->sendGrid(p1Data);
}

void Scene::startGame()
{
	p2Data = remotePlayer->getGrid();
	sendGrid();
	loadScene(SCENE_GAME_OURGRID);
}

// Store Renderer pointer for Scene Changes. TODO: Possibly no more need for passing this all the time?
void Scene::giveRenderer(SDL_Renderer * ren)
{
	this->renderer = ren;
}

// Add an object to the Phys list
int Scene::registerPhys(PhysObj * obj)
{
	if (!listsLocked)
	{
		PhysList.push_back(obj);
		std::cout << "Registered Phys Object: " << &obj << std::endl;
		return 0;
	}
	else {
		PhysObjBuffer.push_back(obj);
		std::cout << "Delayed Registered Phys Object: " << &obj << std::endl;
		return 0;
	}
}

// Add an object to the Render List
int Scene::registerRender(RenderObject * obj)
{
	if (!listsLocked)
	{
		RenderList.push_back(obj);
		std::cout << "Registered Render Object: " << obj << " ID: " << obj->id << std::endl;
		return 0;
	}
	else {
		RenderObjBuffer.push_back(obj);
		std::cout << "Delayed Registered Render Object: " << obj << " ID: " << obj->id << std::endl;
		return 0;
	}
}

// Run an update Cycle (and change scene if requested) (and register new objects)
void Scene::runUpdate(double simLength)
{
	if (mouseData.leftMouseOnce)
	{
		p1Fire = true;
	}
	else {
		p1Fire = false;
	}
	// Update Input Axes
	remotePlayer->sendState(P1_axis_X, p1_axis_Y, p1Fire, ourTurn, lastShotHit);
	remotePlayer->sendPhys(p1PosX, p1PosY, p2PosX, p2PosY);
	remotePlayer->update();
	p2_axis_X = remotePlayer->axis_X;
	p2_axis_Y = remotePlayer->axis_Y;
	p2Fire = remotePlayer->fire;

	
		
	// Run update on objects
	listsLocked = true;
	if (!PhysList.empty())
	{
		for (auto const& object : PhysList)
		{
			object->preStep();
		}
		for (auto const& object : PhysList)
		{
			object->tickPhysics(simLength);
		}
		for (auto const& object : PhysList)
		{
			object->postStep();
		}
	}
	if (!RenderList.empty())
	{
		for (auto const& object : RenderList)
		{
			object->update(simLength);
		}
	}
	listsLocked = false;

	// Register buffered objects
	if (!PhysObjBuffer.empty())
	{
		for (auto const& obj : PhysObjBuffer)
		{
			PhysList.push_back(obj);
		}
		PhysObjBuffer.clear();
	}
	if (!RenderObjBuffer.empty())
	{
		for (auto const& obj : RenderObjBuffer)
		{
			RenderList.push_back(obj);
		}
		RenderObjBuffer.clear();
	}

	// Change Scene if needed
	// NOTE: it seems like a waste to register just before it could be deleted,
	// but it needs to be registered fully so it actaully gets deleted and we don't
	// leak memory.
	if (newScene != currentScene)
	{
		changeScene();
	}
}

// Run a render cycle
void Scene::render(SDL_Renderer* ren)
{
	if (!RenderList.empty())
	{
		for (auto const& object : RenderList)
		{
			object->render(ren);
		}
	}
}

// Delete all objects in prep for a new scene
void Scene::cleanup()
{
	for (auto obj : PhysList)
	{
		delete obj;
	}
	PhysList.clear();
	for (auto obj : RenderList)
	{
		delete obj;
	}
	RenderList.clear();
}

void loadTestScreen(SDL_Renderer* ren)
{
	TestScreen* screen = new TestScreen(ren, "_TestScreen");
	Scene::getScene().registerRender(screen);
}

void loadMainMenu(SDL_Renderer* ren)
{
	GUIButton* button1 = new GUIButton(ren, "Start Game", 100, 100, []() {Scene::getScene().loadScene(SCENE_PREGAME); }, "_MainMenu_Button1");
	GUIButton* button2 = new GUIButton(ren, "Instructions", 100, 200, []() {Scene::getScene().loadScene(SCENE_INSTRUCTIONS); }, "_MainMenu_Button2");
	GUIButton* button3 = new GUIButton(ren, "Quit", 100, 300, []() {Scene::getScene().loadScene(SCENE_QUIT); }, "_MainMenu_Button3");

	AnimatedSprite * logo = new AnimatedSprite("battleship", ren, "_MainMenu_Logo");
	int a1 = logo->createAnimFrame(10, 0, 232, 118);
	int a2 = logo->createAnimFrame(251, 0, 232, 118);
	int a3 = logo->createAnimFrame(492, 0, 232, 116);
	int a4 = logo->createAnimFrame(733, 0, 232, 116);
	int a[] = { a1, a2, a3, a4 };
	int an = logo->createAnim(a, 4);
	logo->setFrameRate(10);
	logo->playAnim(an);
	logo->moveSprite(150, 400);

	Scene::getScene().registerRender(logo);

	Scene::getScene().registerRender(button1);
	Scene::getScene().registerRender(button2);
	Scene::getScene().registerRender(button3);
}

void loadInstructions(SDL_Renderer* ren)
{
	GUIButton* button = new GUIButton(ren, "Back", 300, 300, []() {Scene::getScene().loadScene(SCENE_MENU); }, "_instructions_BackButton");
	Scene::getScene().registerRender(button);

	TextSprite* text = new TextSprite("./assets/Hack-Regular.ttf", 64, "Use the mouse and left click to", ren, "_instructions_text");
	text->setScale(0.25f);
	text->moveString(50, 100);
	Scene::getScene().registerRender(text);
	
	TextSprite* text2 = new TextSprite("./assets/Hack-Regular.ttf", 64, "Place your ships!", ren, "_instructions_text");
	text2->setScale(0.25f);
	text2->moveString(50, 125);
	Scene::getScene().registerRender(text2);

	TextSprite* text3 = new TextSprite("./assets/Hack-Regular.ttf", 64, "Use WASD and left click to", ren, "_instructions_text");
	text3->setScale(0.25f);
	text3->moveString(50, 175);
	Scene::getScene().registerRender(text3);

	TextSprite* text4 = new TextSprite("./assets/Hack-Regular.ttf", 64, "shoot at your opponent's ships!", ren, "_instructions_text");
	text4->setScale(0.25f);
	text4->moveString(50, 200);
	Scene::getScene().registerRender(text4);
	
}

void loadPregame(SDL_Renderer* ren)
{
	PregameScreen* screen = new PregameScreen(ren, "_pregameScreen");
	Scene::getScene().registerRender(screen);
}

void makeP2()
{
	/*
	 TODO: THIS
	 TODO: RemotePlayer class
	 TODO: RemotePlayerAI class
	 TODO: RemotePlayerLocal class
	 TODO: RemotePlayerNetwork class?
	if (multiplayer)
		Let P2 place ships
	else
		init AI
		Generate Grid
	
	*/
}

/*void loadTheirGrid(SDL_Renderer* ren)
{
	if (Scene::getScene().p2Data.ships[0].size = 0)
	{
		makeP2();
	}
	GameGrid* grid = new GameGrid(THEIR_GRID, ren, "_ThierGrid");

	Scene::getScene().registerRender(grid);

}
*/
void loadOurGrid(SDL_Renderer* ren)
{
	GameGrid* grid = new GameGrid(OUR_GRID, ren, "_OurGrid");

	Scene::getScene().registerRender(grid);
}

/*void Scene::turnover(int winner)
{
	switch (winner)
	{
	case 0:
		if (turn == 1)
		{
			turn = 2;
			loadScene(SCENE_GAME_THEIRGRID);
		}
		else {
			turn = 1;
			loadScene(SCENE_GAME_OURGRID);
		}
		break;
	case 1:
		//Local player won
		break;
	case 2:
		//Remote/AI player won
		break;
	default:
		break;
	}
}*/

void loadP1Win(SDL_Renderer * ren)
{
	TextSprite * text = new TextSprite("./assets/hack-regular.ttf", 96, "Player 1 (Human) Wins!", ren, "_WinScreen_Text");
	text->moveString(150, 200);
	text->setScale(0.2);

	GUIButton * button = new GUIButton(ren, "Return", 300, 400, []() {Scene::getScene().loadScene(SCENE_MENU); }, "_WinScreen_Text");

	Scene::getScene().registerRender(text);
	Scene::getScene().registerRender(button);
}

void loadP2Win(SDL_Renderer * ren)
{
	TextSprite * text = new TextSprite("./assets/hack-regular.ttf", 96, "Player 2 (AI) Wins!", ren, "_WinScreen_Text");
	text->moveString(150, 200);
	text->setScale(0.3);
	
	GUIButton * button = new GUIButton(ren, "Return", 300, 400, []() {Scene::getScene().loadScene(SCENE_MENU); }, "_WinScreen_Text");

	Scene::getScene().registerRender(text);
	Scene::getScene().registerRender(button);
}

// Request a Scene change
void Scene::loadScene(SceneList scene)
{
	newScene = scene;
}

// Acutally do the scene change.
void Scene::changeScene()
{
	switch (newScene)
	{
	case SCENE_TITLE:
		cleanup();
		break;
	case SCENE_MENU:
		cleanup();
		loadMainMenu(renderer);
		break;
	case SCENE_INSTRUCTIONS:
		cleanup();
		loadInstructions(renderer);
		break;
	case SCENE_PREGAME:
		cleanup();
		loadPregame(renderer);
		break;
	case SCENE_TEST_SCENE:
		cleanup();
		loadTestScreen(renderer);
		break;
	case SCENE_GAME_OURGRID:
		cleanup();
		loadOurGrid(renderer);
		break;
	case SCENE_GAME_THEIRGRID:
		cleanup();
		//loadTheirGrid(renderer);
		break;
	case SCENE_P1_WIN:
		cleanup();
		loadP1Win(renderer);
		break;
	case SCENE_P2_WIN:
		cleanup();
		loadP2Win(renderer);
		break;
	case SCENE_QUIT:
		cleanup();
		quitting = true;
		break;
	default:
		break;
	}
	currentScene = newScene;
}
