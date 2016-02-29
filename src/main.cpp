#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <chrono>

#ifdef _WIN32 // compiling on windows
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#else // NOT compiling on windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "RenderObject.h"
#include "StaticSprite.h"
#include "AnimatedSprite.h"
#include "TextSprite.h"
#include "Scene.h"

//typedef std::chrono::high_resolution_clock Clock;
//typedef std::chrono::nanoseconds Duration;
//typedef std::chrono::time_point<Clock, Duration> Time_Point;

std::string exeName;
SDL_Window *win; //pointer to the SDL_Window
SDL_Renderer *ren; //pointer to the SDL_Renderer
SDL_Surface *surface; //pointer to the SDL_Surface

std::vector<RenderObject*> objectList;

bool done = false;
bool key = false;
bool clearSprites = false;

//Time_Point frameStart;
//Time_Point lastFrameStart;

std::chrono::time_point<std::chrono::high_resolution_clock> frameStart;
std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameStart;
double lft;

void cleanExit(int returnValue)
{
	if (ren != nullptr) SDL_DestroyRenderer(ren);
	if (win != nullptr) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(returnValue);
}

void initThings()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	std::cout << "SDL initialised OK!\n";

	//create window
	win = SDL_CreateWindow("SDL Hello World!", 100, 100, 600, 600, SDL_WINDOW_SHOWN);

	//error handling
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
	std::cout << "SDL CreatedWindow OK!\n";

	//ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
}

void initText()
{
	if (TTF_Init() == -1)
	{
		std::cout << "TTF_Init Failed: " << TTF_GetError() << std::endl;
		cleanExit(1);
	}
	
	TextSprite* text(new TextSprite("./assets/Hack-Regular.ttf", 96, "Hello, World!", ren));
	text->setScale(0.4f);
	text->moveString(0, 0);
	objectList.push_back(text);
	Scene::RenderList.push_back(text);


}
void makePlayer(int x, int y)
{
	std::string path = "./assets/p1_spritesheet.png";
	AnimatedSprite* sprite(new AnimatedSprite(path, ren));

	//walk anim
	int walkAnim[11] = { 0 };
	walkAnim[0] = sprite->createAnimFrame(0, 0, 72, 97);
	walkAnim[1] = sprite->createAnimFrame(73, 0, 72, 97);
	walkAnim[2] = sprite->createAnimFrame(146, 0, 72, 97);
	walkAnim[3] = sprite->createAnimFrame(0, 98, 72, 97);
	walkAnim[4] = sprite->createAnimFrame(73, 98, 72, 97);
	walkAnim[5] = sprite->createAnimFrame(146, 98, 72, 97);
	walkAnim[6] = sprite->createAnimFrame(219, 0, 72, 97);
	walkAnim[7] = sprite->createAnimFrame(292, 0, 72, 97);
	walkAnim[8] = sprite->createAnimFrame(219, 98, 72, 97);
	walkAnim[9] = sprite->createAnimFrame(292, 98, 72, 97);
	walkAnim[10] = sprite->createAnimFrame(365, 0, 72, 97);
	int walk = sprite->createAnim(walkAnim, 11);

	sprite->setFrameRate(10);
	sprite->playAnim(walk);
	sprite->moveSprite(x, y);

	objectList.push_back(sprite);
}
void initSprites()
{
	makePlayer(300, 300);

	std::string path = "./assets/Opengl-logo.svg.png";
	AnimatedSprite* logo(new AnimatedSprite(path, ren));
	int f = logo->createAnimFrame(0, 0, 2000, 876);
	int af[] = { f };
	int a = logo->createAnim(af, 1);
	logo->scaleSprite(0.25, 0.25);
	logo->setFrameRate(10);
	logo->playAnim(a);

	objectList.push_back(logo);
}

void handleInput()
{
	/*//Event-based input handling
	//The underlying OS is event-based, so **each** key-up or key-down (for example)
	//generates an event.
	//  - https://wiki.libsdl.org/SDL_PollEvent
	//In some scenarios we want to catch **ALL** the events, not just to present state
	//  - for instance, if taking keyboard input the user might key-down two keys during a frame
	//    - we want to catch based, and know the order
	//  - or the user might key-down and key-up the same within a frame, and we still want something to happen (e.g. jump)
	//  - the alternative is to Poll the current state with SDL_GetKeyboardState*/

	SDL_Event event; //somewhere to store an event

	//NOTE: there may be multiple events per frame
	while (SDL_PollEvent(&event)) //loop until SDL_PollEvent returns 0 (meaning no more events)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			done = true; //set donecreate remote branch flag if SDL wants to quit (i.e. if the OS has triggered a close event,
							//  - such as window close, or SIGINT
			break;

			//keydown handling - we should to the opposite on key-up for direction controls (generally)
		case SDL_KEYDOWN:
			//Keydown can fire repeatable if key-repeat is on.
			//  - the repeat flag is set on the keyboard event, if this is a repeat event
			//  - in our case, we're going to ignore repeat events
			//  - https://wiki.libsdl.org/SDL_KeyboardEvent
			if (!event.key.repeat)
				switch (event.key.keysym.sym)
				{
					//hit escape to exit
				case SDLK_ESCAPE: done = true; break;
				case SDLK_SPACE: key = true; break;
				case SDLK_r: clearSprites = true; break;
				}
			break;
		}
	}
}
// end::handleInput[]

// tag::updateSimulation[]
void updateSimulation(double simLength = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
	for (auto const& object : objectList)
	{
		object->update(simLength);
	}
	if (key)
	{
		makePlayer(rand() % 500, rand() % 500);
		key = false;
	}
	if (clearSprites)
	{
		objectList.clear();
		clearSprites = false;
	}
}

void render()
{
		//First clear the renderer
		SDL_RenderClear(ren);

		//Draw things
		for (auto const& object : objectList)
		{
			object->render(ren);
		}

		//Update the screen
		SDL_RenderPresent(ren);
}

void postRender()
{
	auto lastFrameTime = frameStart.time_since_epoch() - lastFrameStart.time_since_epoch();
	lft = lastFrameTime.count() / 1000000000.0f;
	double fps = 1.0f / lft;
	//std::cout << "\r" << lft << "\t" << fps << "          ";
}

int main( int argc, char* args[] )
{
	initThings();

	initText();
	initSprites();

	

	while (!done) //loop until done flag is set)
	{
		frameStart = std::chrono::high_resolution_clock::now();
		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(lft); // this should ONLY SET VARIABLES according to simulation

		render(); // this should render the world state according to VARIABLES

		postRender();

		//SDL_Delay(20); // unless vsync is on??
		lastFrameStart = frameStart;
	}

	cleanExit(0);
	return 0;
}
