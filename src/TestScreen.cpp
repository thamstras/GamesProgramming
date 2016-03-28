#include "TestScreen.h"

TestScreen::TestScreen(SDL_Renderer* ren, std::string id)
{
	this->id = id;
	std::cout << "Making TestScene" << std::endl;

	std::string manPath = "./assets/p1_spritesheet.png";
	std::string logoPath = "./assets/Opengl-logo.svg.png";
	Scene& scene = Scene::getScene();

	man = new AnimatedSprite(manPath, ren, this->id + "_man");

	//walk anim
	int walkAnim[11] = { 0 };
	walkAnim[0] = man->createAnimFrame(0, 0, 72, 97);
	walkAnim[1] = man->createAnimFrame(73, 0, 72, 97);
	walkAnim[2] = man->createAnimFrame(146, 0, 72, 97);
	walkAnim[3] = man->createAnimFrame(0, 98, 72, 97);
	walkAnim[4] = man->createAnimFrame(73, 98, 72, 97);
	walkAnim[5] = man->createAnimFrame(146, 98, 72, 97);
	walkAnim[6] = man->createAnimFrame(219, 0, 72, 97);
	walkAnim[7] = man->createAnimFrame(292, 0, 72, 97);
	walkAnim[8] = man->createAnimFrame(219, 98, 72, 97);
	walkAnim[9] = man->createAnimFrame(292, 98, 72, 97);
	walkAnim[10] = man->createAnimFrame(365, 0, 72, 97);
	int walk = man->createAnim(walkAnim, 11);

	man->setFrameRate(10);
	man->playAnim(walk);
	man->moveSprite(300, 300);

	scene.registerRender(man);

	logo = new StaticSprite(logoPath, ren, this->id + "_logo");
	logo->scaleSprite(0.25, 0.25);

	Scene::getScene().registerRender(logo);

	ball = new Ball(ren, glm::vec2(150, 150), glm::vec2(30, 30), 1.0f, this->id + "_ball");
	ball->bindPlayer(1);

	scene.registerRender(ball);

	text = new TextSprite("./assets/Hack-Regular.ttf", 96, "Hello, World!", ren, this->id + "_text");
	text->setScale(0.4f);
	text->moveString(0, 0);

	scene.registerRender(text);

	button = new GUIButton(ren, "TestButton", 100, 100, []() {Scene::getScene().loadScene(SCENE_MENU); }, this->id + "_button");
	scene.registerRender(button);
}

TestScreen::~TestScreen()
{
	std::cout << "Destroying TestScreen" << std::endl;
}

void TestScreen::update(double simLength)
{
	//std::cout << this << std::endl;
}

void TestScreen::render(SDL_Renderer * ren)
{
	/* Does Nothing */
}
