#pragma once
#include <SFML/Graphics.hpp>
#pragma warning(disable: 4996) // Disable deprecation
using namespace sf;
class menuObjects
{
public:
	void menuObjectsDefaultImageSet(int *psBigY, int *psTreeX, int *pmTitleY, int *psCuteX, sf::Sprite *snakeBi, sf::Sprite *menuTitle, sf::Sprite *snakeCute, sf::RenderWindow &win);//����� ������������ ���� �������� � ���� �� ������ �����
	void menuObjectsDefaultImageSetAdjustment(int *psBigY, int *psTreeX, int *pmTitleY, int *psCuteX);// ����� ������������� ������������ �������� �������� � ����
	void menuActiveText(Font *grobold, int *startTextPosX, Color *pSelected, RenderWindow &win, std::string str, int smX,int smY, bool sm);// ����� ������ � �������� ������� � ����
	void menuText(Font *srift, int sriftSize, RenderWindow &win, std::string str, int smX, int smY, Color *color); // ����� ������ ������ � ����
	void menuText_plus_valuie(Font *srift, int sriftSize, RenderWindow &win, std::string str, int smX, int smY, Color *color, int valuie);// ����� ������ ������ + ����������
};
