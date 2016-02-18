#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string imagePath, SDL_Renderer* ren) : StaticSprite( imagePath, ren)
{

	/*SDL_Surface* surface = IMG_Load(imagePath.c_str());
	if (surface == nullptr) {
		std::cout << "SDL IMG_Load Error: " << SDL_GetError() << std::endl;
		//cleanExit(1);
	}

	this->_tex = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	if (this->_tex == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		//cleanExit(1);
	}
	
	_x = 10;
	_y = 10;

	_scaleX = 1.0f;
	_scaleY = 1.0f;*/



}

AnimatedSprite::AnimatedSprite(const AnimatedSprite& other) : StaticSprite(other)
{
	std::cout << "AnimatedSprite::AnimatedSprite(const AnimatedSprite& other)\n";
	//this->_x = other._x;
	//this->_y = other._y;
	this->_frameRate = other._frameRate;
	//this->_tex = other._tex;
	this->_currAnim = other._currAnim;
	this->_animFrame = other._animFrame;
	this->_currFrame = other._currFrame;
	//this->_currFrameRect = other._currFrameRect;
	this->_frameList = other._frameList;
	this->_animList = other._animList;
}

AnimatedSprite& AnimatedSprite::operator=(const AnimatedSprite& other)
{
	if (this != &other)
	{
		std::cout << "AnimatedSprite& AnimatedSprite::operator=(const AnimatedSprite& other)\n";
		StaticSprite::operator=(other);
		//this->_x = other._x;
		//this->_y = other._y;
		this->_frameRate = other._frameRate;
		//this->_tex = other._tex;
		this->_currAnim = other._currAnim;
		this->_animFrame = other._animFrame;
		this->_currFrame = other._currFrame;
		//this->_currFrameRect = other._currFrameRect;
		this->_frameList = other._frameList;
		this->_animList = other._animList;
	}
	return *this;
}

AnimatedSprite::~AnimatedSprite()
{
	std::cout << "AnimatedSprite::~AnimatedSprite()\n";
	//SDL_DestroyTexture(this->_tex); //Done by StaticSprite
}

void AnimatedSprite::update(double simLength)
{
	_animFrame++;
	_currFrame = _animFrame / _frameRate;
	SpriteAnim anim = _animList[_currAnim];
	_currFrame %= anim.nFrames;
	_srcRect = anim.frames[_currFrame];
}

void AnimatedSprite::render(SDL_Renderer *renderer)
{
	SDL_Rect destRect;
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _srcRect.w * _scaleX;	//Note: The narrowing cast here is intended.
	destRect.h = _srcRect.h * _scaleY;
	SDL_RenderCopy(renderer, _tex, &_srcRect, &destRect);
}

int AnimatedSprite::createAnimFrame(int left, int top, int width, int height)
{
	SDL_Rect frame = { left, top, width, height };
	_frameList.push_back(frame);
	return _frameList.size() - 1;
}

int AnimatedSprite::createAnim(int* frames, int nFrames)
{
	SDL_Rect* animFrames = new SDL_Rect[nFrames];
	for (int i = 0; i < nFrames; i++)
	{
		animFrames[i] = _frameList[frames[i]];
	}
	SpriteAnim anim = SpriteAnim(nFrames, animFrames);
	_animList.push_back(anim);
	delete[] animFrames;
	return _animList.size() - 1;
}

void AnimatedSprite::setFrameRate(int frameRate)
{
	_frameRate = frameRate;
}

void AnimatedSprite::playAnim(int anim)
{
	_currAnim = anim;
	_animFrame = 0;
}

/*void AnimatedSprite::moveSprite(int x, int y)
{
	this->_x = x;
	this->_y = y;
}*/

/*void AnimatedSprite::scaleSprite(float xScale, float yScale)
{
	this->_scaleX = xScale;
	this->_scaleY = yScale;
}*/
