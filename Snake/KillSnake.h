#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StructPoint.h"
using namespace sf;

class KillSnake
{
public:
	void KillSnakeS(int *psnakeSize, Sound *dieS, int *pgameState, int x, int y, Point *point);

};

