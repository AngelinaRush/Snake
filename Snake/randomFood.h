#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StructPoint.h"
#include "menuObjects.h"
using namespace sf;
class randomFood
{

public:
	void generationSetFood(int *foodXX, int *foodYY, sf::Sprite &food);// ����� ��������� ���������� ������������ ������
	void generationFood(RenderWindow &win, int *foodXX, int *foodYY, sf::Sprite &food, Texture &Tfood, int *pfps, Texture *pTbonusFood, int *px, int *py, int *psnakeSize, int *pscore, Point *point, Sound *pbonusTime, Sound *peat, Sound *pbonusAppear, Color *pbeat, Font *pgothic, int *pfoodCount, int *pbonus, bool *pbonusStart, bool *pincreaseLevel, bool *pbonusBool);//  ����� �������� � ���������� ������
};

