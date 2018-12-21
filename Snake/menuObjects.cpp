#include "menuObjects.h"



// метод устанавливки всех объектов в меню на нужные места
void menuObjects::menuObjectsDefaultImageSet(int *psBigY,int *psTreeX, int *pmTitleY, int *psCuteX, sf::Sprite *snakeBig, sf::Sprite *menuTitle, sf::Sprite *snakeCute, sf::RenderWindow &win)
{
	using namespace sf;
	//устанавливаем всё на нужные места
	(*snakeBig).setPosition(0, *psBigY);//устанавливаем позицию левой нижней картинки в меню
	(*menuTitle).setPosition(0, *pmTitleY); // устанавливаем позицию верхней картинки средней части
	(*snakeCute).setPosition(*psCuteX, 300); // устанавливаем позицию правой нижней картинки внизу
	win.draw(*snakeBig); // заполняем окно картиной в меню
	win.draw(*snakeCute); // заполняем окно картиной в меню
	 win.draw(*menuTitle); // заполняем окно картиной в меню
};

// метод корректировки устанавливки картинок объектов в меню
void menuObjects::menuObjectsDefaultImageSetAdjustment(int *psBigY, int *psTreeX, int *pmTitleY, int *psCuteX)
{
	if (*psBigY > 0) *psBigY -= 7; //корректируем при позицию левой нижней картинки в меню при изменниях размеров окна
	if (*psTreeX < 0) *psTreeX += 20; //корректируем позицию левой верхней картинки в меню при изменениях размеров окна
	if (*pmTitleY < 0) *pmTitleY += 10; // корректируем позицию верхней картинки средней части в меню при изменениях размеров окна
	if (*psCuteX < 700) *psCuteX += 12; // корректируем позицию правой нижней картинки внизу при изменениях размеров окна
};

// метод работы с активным текстом в меню
void menuObjects::menuActiveText(Font *grobold, int *startTextPosX, Color *pSelected, RenderWindow &win, std::string str, int smX, int smY, bool sm)
{
	Text startText(str, *grobold, 40); // текст кнопки старт, шрифт grobold, кеги 40
	if ((*startTextPosX) > smX)       (*startTextPosX) -= 40; // вырванивание по окну надписи кнопки 
	if (sm) startText.setPosition((*startTextPosX), smY); else  startText.setPosition(smX,smY); // позиция надписи кнопки 
	startText.setFillColor(*pSelected); // заливка  надписи кнопки 
	win.draw(startText);
};

// метод вывода текста в меню
void menuObjects::menuText(Font *srift, int sriftSize, RenderWindow &win, std::string str, int smX, int smY, Color *color)
{
	Text developerText(str, *srift, sriftSize);// текст надписи
	developerText.setPosition(smX, smY); // позиция надписи 
	developerText.setFillColor(*color); // заливка  надписи 
	win.draw(developerText); // заполняем окно текстом 
};
// метод вывода текста в меню
void menuObjects::menuText_plus_valuie(Font *srift, int sriftSize, RenderWindow &win, std::string str, int smX, int smY, Color *color, int valuie)
{
	char hurryUp[20];

	Text hurryUpTextt(str, *srift, sriftSize); // ставим готический шрифт с 22 кегами
	hurryUpTextt.setFillColor(*color); // заливаем Hurry Up цветом
	hurryUpTextt.setPosition(smX, smY); // позиционируем текст Hurry Up

	sprintf(hurryUp, "%d", valuie); // текст вывода Hurry Up
	Text hurryUpText(hurryUp, *srift, sriftSize); // ставим готический шрифт с 22 кегами
	hurryUpText.setFillColor(*color); // заливаем Hurry Up цветом
	hurryUpText.setPosition(smX+ (str.length()*0.5)*sriftSize, smY); // позиционируем текст Hurry Upz	

	win.draw(hurryUpText); // выводим в окно Hurry Up
	win.draw(hurryUpTextt); // выводим в окно Hurry Up
};


