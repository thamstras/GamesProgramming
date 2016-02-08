#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


#ifdef _WIN32 // compiling on windows
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#else // NOT compiling on windows
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "AnimatedSprite.h"
#include "TextRenderer.h"

std::string exeName;
SDL_Window *win; //pointer to the SDL_Window
SDL_Renderer *ren; //pointer to the SDL_Renderer
SDL_Surface *surface; //pointer to the SDL_Surface
SDL_Texture *tex; //pointer to the SDL_Texture
SDL_Texture *tex2;
SDL_Surface *messageSurface; //pointer to the SDL_Surface for message
SDL_Texture *messageTexture; //pointer to the SDL_Texture for message
SDL_Rect message_rect; //SDL_rect for the message

AnimatedSprite* logo;
AnimatedSprite* theSprite;

TextRenderer* text;

bool done = false;

void cleanExit(int returnValue)
{
	if (messageTexture != nullptr) SDL_DestroyTexture(messageTexture);
	if (tex != nullptr) SDL_DestroyTexture(tex);
	if (ren != nullptr) SDL_DestroyRenderer(ren);
	if (win != nullptr) SDL_DestroyWindow(win);
	if (theSprite != nullptr) delete theSprite;
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

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}
}

void initTextures()
{
	std::string imagePath = "./assets/p1_spritesheet.png";
	surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}

	tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (tex == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}

	std::string imagePath2 = "./assets/Opengl-logo.svg.png";
	surface = IMG_Load(imagePath2.c_str());
	if (surface == nullptr) {
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		cleanExit(1);
	}

	tex2 = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (tex == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
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
	/*
	TTF_Font* sans = TTF_OpenFont("./assets/Hack-Regular.ttf", 96);
	if (sans == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		cleanExit(1);
	}
	SDL_Color White = { 255, 255, 255 };
	messageSurface = TTF_RenderText_Solid(sans, "Hello World!", White);
	messageTexture = SDL_CreateTextureFromSurface(ren, messageSurface);
	message_rect.x = 0;
	message_rect.y = 0;
	message_rect.w = 300;
	message_rect.h = 100;*/
	text = new TextRenderer("./assets/Hack-Regular.ttf", 96, "Hello, World!", ren);
	text->setScale(0.4f);
	text->moveString(0, 0);


}

void initSprites()
{
	theSprite = new AnimatedSprite(tex);

	//walk anim
	int f1 = theSprite->createAnimFrame(0, 0, 72, 97);
	int f2 = theSprite->createAnimFrame(73, 0, 72, 97);
	int f3 = theSprite->createAnimFrame(146, 0, 72, 97);
	int f4 = theSprite->createAnimFrame(0, 98, 72, 97);
	int f5 = theSprite->createAnimFrame(73, 98, 72, 97);
	int f6 = theSprite->createAnimFrame(146, 98, 72, 97);
	int f7 = theSprite->createAnimFrame(219, 0, 72, 97);
	int f8 = theSprite->createAnimFrame(292, 0, 72, 97);
	int f9 = theSprite->createAnimFrame(219, 98, 72, 97);
	int f11 = theSprite->createAnimFrame(292, 98, 72, 97);
	int f10 = theSprite->createAnimFrame(365, 0, 72, 97);
	int walkAnim[] = { f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11 };
	int walk = theSprite->createAnim(walkAnim, 11);

	theSprite->setFrameRate(10);
	theSprite->playAnim(walk);
	theSprite->moveSprite(300, 300);

	logo = new AnimatedSprite(tex2);
	int f = logo->createAnimFrame(0, 0, 2000, 876);
	int af[] = { f };
	int a = logo->createAnim(af, 1);
	logo->scaleSprite(0.25, 0.25);
	logo->setFrameRate(10);
	logo->playAnim(a);
}

void handleInput()
{
	//Event-based input handling
	//The underlying OS is event-based, so **each** key-up or key-down (for example)
	//generates an event.
	//  - https://wiki.libsdl.org/SDL_PollEvent
	//In some scenarios we want to catch **ALL** the events, not just to present state
	//  - for instance, if taking keyboard input the user might key-down two keys during a frame
	//    - we want to catch based, and know the order
	//  - or the user might key-down and key-up the same within a frame, and we still want something to happen (e.g. jump)
	//  - the alternative is to Poll the current state with SDL_GetKeyboardState

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
					case SDLK_ESCAPE: done = true;
				}
			break;
		}
	}
}
// end::handleInput[]

// tag::updateSimulation[]
void updateSimulation(double simLength = 0.02) //update simulation with an amount of time to simulate for (in seconds)
{
	logo->update(simLength);
	theSprite->update(simLength);
}

void render()
{
		//First clear the renderer
		SDL_RenderClear(ren);

		//Draw the texture
		//SDL_RenderCopy(ren, tex, NULL, NULL);
		logo->render(ren);
		theSprite->render(ren);
		text->render(ren);
		//Draw the text
		//SDL_RenderCopy(ren, messageTexture, NULL, &message_rect);

		//Update the screen
		SDL_RenderPresent(ren);
}


int main( int argc, char* args[] )
{
	initThings();
	initTextures();
	initText();

	initSprites();

	while (!done) //loop until done flag is set)
	{
		handleInput(); // this should ONLY SET VARIABLES

		updateSimulation(); // this should ONLY SET VARIABLES according to simulation

		render(); // this should render the world state according to VARIABLES

		SDL_Delay(20); // unless vsync is on??
	}

	cleanExit(0);
	return 0;
}
