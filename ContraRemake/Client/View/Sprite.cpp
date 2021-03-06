/*
 * Sprite.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: giova
 */

#include "Sprite.hh"

Sprite::Sprite(GameView* _gameView, std::string path, int _source_rect_width, int _source_rect_height, int _dest_rect_width, int _dest_rect_height)
{
	gameView = _gameView;

	destinationWidth = _dest_rect_width;
	destinationHeight = _dest_rect_height;

	texture = gameView->textureGenerator(path.c_str());

	gameView->queryTexture(texture, &textureWidth, &textureHeight);

	src.x = 0;
	src.y = 0;
	src.w = _source_rect_width;
	src.h = _source_rect_height;
}

Sprite::~Sprite()
{
	this->destroy();
}

void Sprite::render(int x, int y)
{
	gameView->draw(texture, &src, x, y, destinationWidth, destinationHeight);
}

void Sprite::update()
{
	src.x = src.x + src.w;

	if(src.x >= textureWidth)
		src.x = 0;
}

void Sprite::moveToPos(int pos)
{
	src.x = src.w * pos;

	if(src.x >= textureWidth)
		src.x = 0;
}

void Sprite::destroy()
{
	SDL_DestroyTexture(texture);

	texture = NULL;
	gameView = NULL;
}
