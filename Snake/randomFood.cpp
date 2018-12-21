#include "randomFood.h"

void randomFood::generationSetFood(int *foodXX, int *foodYY, sf::Sprite &food) { // ����� ��������� ���������� ������������ ������
	(*foodXX) = (rand() % 928) + 16; // ���������� ��������� ���������� �� �
	(*foodXX) -= (*foodXX % 16); // ������� ������ ��� �� ���������� �
	(*foodYY) = (rand() % 528) + 16; // ���������� ��������� ���������� �� �
	(*foodYY) -= (*foodYY % 16); // ������� ������ ��� �� ���������� �
	food.setPosition(*foodXX, *foodYY); // ������ ���� � ��������������� ���� ����������
}

void randomFood::generationFood(RenderWindow &win, int *foodXX, int *foodYY, sf::Sprite &food, Texture &Tfood, int *pfps, Texture *pTbonusFood, int *px, int *py, int *psnakeSize, int *pscore, Point *point, Sound *pbonusTime, Sound *peat, Sound *pbonusAppear, Color *pbeat, Font *pgothic, int *pfoodCount, int *pbonus, bool *pbonusStart, bool *pincreaseLevel, bool *pbonusBool) {//  ����� �������� � ���������� ������
	
	if ((*pfoodCount) % 10 == 0 && (*pincreaseLevel)) // ���� �������� �� 10 ��� ������� � �������� �������(����� �����)
		(*pfps)++, (*pincreaseLevel) = false, win.setFramerateLimit((*pfps)); // ��������� ������� ���������� ������+ ������� ���� ���������� ������+ ��������� �������� ���������� ������

	if ((*pfoodCount) % 5 == 0 && (*pfoodCount) != 0 && (*pbonusBool)) { // ���� �������� �� 5 ��� ������� + ����� ���� �� ���� �����+ ����� ��������
		if (*pbonusStart) {
			food.setTexture(*pTbonusFood); // ������ �������� �������� ������
			(*pbonusAppear).play(); // �������� ���� ��������� ������
			(*pbonusTime).play(); // �������� ������ ��������� �����
			*pbonusStart = false; //������ ������ � ���, ��� ����� ��� ���
			(*pbonus) = (*pfps) * 50; // ����� �������� ������
		}
		if ((*pbonus) > 1) { // ���� ����� ������ �� �������
			if ((*px) == (*foodXX) && (*py) == (*foodYY)) { // ���� ����� �����
				(*pbonusAppear).play(); // �������� ���� ������������ ������
				(*pbonusTime).stop(); // ��������� ������ ��������� �����
				randomFood randomFood;// ������ ������ ������ ��������� ������
				randomFood.generationSetFood(foodXX, foodYY, food); // ������ ����� �� ���� �����������
				(*psnakeSize)++; // �������� � �������� ������ +1
				(*pfoodCount)++; // �������� � ������� ��� +1
				(*pscore) += (*pbonus); // �������� ����� � �����
				(*pincreaseLevel) = true; // ������ ���� � ���, ��� ����� �����
			}
			menuObjects menuObjects;// ������ ������ ������
			menuObjects.menuText_plus_valuie(pgothic, 22, win, "Hurry Up :", 380, 565, pbeat, *pbonus); // ����� ������ � ���������� � �������� �����


			(*pbonus) -= 10; // �������� 10 ����� �� ������
		}
		if ((*pbonus) == 0) // ���� ����� ����� 0
			(*pbonusBool) = false, food.setTexture(Tfood), (*pbonusAppear).play();  // ������ ������� �������� ��� � ������ ��������
	}
	else {
		food.setTexture(Tfood); // ������ �������� �������� ������
		(*pbonusStart) = true; // ������ ������ ����������� ������
		if ((*px) == (*foodXX) && (*py) == (*foodYY)) { // ���� ����� �����
			(*peat).play(); // �������
			(*pscore) += ((*pfps) - 9); // ��������� ���� �� ������� fps-9
			randomFood randomFood;// ������ ������ ������ ��������� ������
			randomFood.generationSetFood(foodXX, foodYY, food); // ������ ����� 

			(*psnakeSize)++; // ��������� ������ � �������� ����
			(*pfoodCount)++; // ������� �������
			(*pbonusBool) = true; // �������� ��� �� ����� �������� ����� ��� ������ �������
			(*pincreaseLevel) = true; // ������ ���� � ���, ��� ����� �����
		}
	}


	for (int i = 1; i < (*psnakeSize) - 1; i++) {
		while ((*foodXX) == point[i].x && (*foodYY) == point[i].y) { // ���� �������� ������ ���� �� ������
			randomFood randomFood;// ������ ������ ������
			randomFood.generationSetFood(foodXX, foodYY, food); // ������ ����� 
		}
	}
	win.draw(food);// ���������� � ���� ���
}