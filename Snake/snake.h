#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StructPoint.h"
using namespace sf;
class snake
{
public:
	void snakeCreate(RenderWindow &win, int *psnakeSize, int *px, int *py, Point *point, int *foodXX,
		             int *foodYY, int *pdir, Texture *pTbodyHorr, Texture *pTbodyVert, Texture *pTheadUp, Texture *pTheadRight,
		             Texture *pTheadDown, Texture *pTheadLeft, Texture *pThaaUp, Texture *pThaaDown, Texture *pThaaRight,
		             Texture *pThaaLeft, Texture *pTrightUp, Texture *pTleftUp, Texture *pTrightDown, Texture *pTleftDown, Texture *pTtailDown,
		             Texture *pTtailUp, Texture *pTtailLeft, Texture *pTtailRight, Sprite *ptail, Sprite *body, Sprite *head, bool *pstartNow2
	                 ); // создаем нашую змейку и даём ей дар логики)
};

