#include "KillSnake.h"



void KillSnake::KillSnakeS(int *psnakeSize, Sound *dieS,int *pgameState, int x, int y, Point *point)
{
	for (int i = 1; i < (*psnakeSize); i++) {
		if (x == point[i].x && y == point[i].y) { // если змея себя укусила
			(*dieS).play(); // звук
			(*pgameState) = 2; // даём понять программе, что нужно открыть меню пройгрыша
		}
	}

	if (x > 929 || x < 15 || y>529 || y < 15) { // если змея вышла погулять за поле, убиваем её
		(*dieS).play(); // звук
		(*pgameState) = 2; // даём программе понять, что нужно включить меню пройгрыша
	}
};



