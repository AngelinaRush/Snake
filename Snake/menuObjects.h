#pragma once
#include <SFML/Graphics.hpp>
#pragma warning(disable: 4996) // Disable deprecation
using namespace sf;
class menuObjects
{
public:
	void menuObjectsDefaultImageSet(int *psBigY, int *psTreeX, int *pmTitleY, int *psCuteX, sf::Sprite *snakeBi, sf::Sprite *menuTitle, sf::Sprite *snakeCute, sf::RenderWindow &win);//метод устанавливки всех объектов в меню на нужные места
	void menuObjectsDefaultImageSetAdjustment(int *psBigY, int *psTreeX, int *pmTitleY, int *psCuteX);// метод корректировки устанавливки картинок объектов в меню
	void menuActiveText(Font *grobold, int *startTextPosX, Color *pSelected, RenderWindow &win, std::string str, int smX,int smY, bool sm);// метод работы с активным текстом в меню
	void menuText(Font *srift, int sriftSize, RenderWindow &win, std::string str, int smX, int smY, Color *color); // метод вывода текста в меню
	void menuText_plus_valuie(Font *srift, int sriftSize, RenderWindow &win, std::string str, int smX, int smY, Color *color, int valuie);// метод вывода текста + переменную
};
