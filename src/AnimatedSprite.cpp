#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(SDL_Texture* tex)
{
	this->_tex = tex;

	_frameList = std::vector<SDL_Rect>();
	_animList = std::vector<SpriteAnim>();

	_x = 10;
	_y = 10;

}

AnimatedSprite::AnimatedSprite(const AnimatedSprite& other)
{
	std::cout << "AnimatedSprite::AnimatedSprite(const AnimatedSprite& other)\n";
	this->_x = other._x;
	this->_y = other._y;
	this->_frameRate = other._frameRate;
	this->_tex = other._tex;
	this->_currAnim = other._currAnim;
	this->_animFrame = other._animFrame;
	this->_currFrame = other._currFrame;
	this->_currFrameRect = other._currFrameRect;
	this->_frameList = other._frameList;
	this->_animList = other._animList;
}

AnimatedSprite& AnimatedSprite::operator=(const AnimatedSprite& other)
{
	if (this != &other)
	{
		std::cout << "AnimatedSprite& AnimatedSprite::operator=(const AnimatedSprite& other)\n";
		this->_x = other._x;
		this->_y = other._y;
		this->_frameRate = other._frameRate;
		this->_tex = other._tex;
		this->_currAnim = other._currAnim;
		this->_animFrame = other._animFrame;
		this->_currFrame = other._currFrame;
		this->_currFrameRect = other._currFrameRect;
		this->_frameList = other._frameList;
		this->_animList = other._animList;
	}
	return *this;
}



AnimatedSprite::~AnimatedSprite()
{
	std::cout << "AnimatedSprite::~AnimatedSprite()\n";
}

void AnimatedSprite::update(double simLength)
{
	_animFrame++;
	_currFrame = _animFrame / _frameRate;
	SpriteAnim anim = _animList[_currAnim];
	_currFrame %= anim.nFrames;
	_currFrameRect = anim.frames[_currFrame];
}

void AnimatedSprite::render(SDL_Renderer *renderer)
{
	SDL_Rect destRect;
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _currFrameRect.w;
	destRect.h = _currFrameRect.h;
	SDL_RenderCopy(renderer, _tex, &_currFrameRect, &destRect);
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

void AnimatedSprite::moveSprite(int x, int y)
{
	this->_x = x;
	this->_y = y;
}
