#include "KillSnake.h"



void KillSnake::KillSnakeS(int *psnakeSize, Sound *dieS,int *pgameState, int x, int y, Point *point)
{
	for (int i = 1; i < (*psnakeSize); i++) {
		if (x == point[i].x && y == point[i].y) { // ���� ���� ���� �������
			(*dieS).play(); // ����
			(*pgameState) = 2; // ��� ������ ���������, ��� ����� ������� ���� ���������
		}
	}

	if (x > 929 || x < 15 || y>529 || y < 15) { // ���� ���� ����� �������� �� ����, ������� �
		(*dieS).play(); // ����
		(*pgameState) = 2; // ��� ��������� ������, ��� ����� �������� ���� ���������
	}
};



