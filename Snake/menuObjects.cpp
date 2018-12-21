#include "menuObjects.h"



// ����� ������������ ���� �������� � ���� �� ������ �����
void menuObjects::menuObjectsDefaultImageSet(int *psBigY,int *psTreeX, int *pmTitleY, int *psCuteX, sf::Sprite *snakeBig, sf::Sprite *menuTitle, sf::Sprite *snakeCute, sf::RenderWindow &win)
{
	using namespace sf;
	//������������� �� �� ������ �����
	(*snakeBig).setPosition(0, *psBigY);//������������� ������� ����� ������ �������� � ����
	(*menuTitle).setPosition(0, *pmTitleY); // ������������� ������� ������� �������� ������� �����
	(*snakeCute).setPosition(*psCuteX, 300); // ������������� ������� ������ ������ �������� �����
	win.draw(*snakeBig); // ��������� ���� �������� � ����
	win.draw(*snakeCute); // ��������� ���� �������� � ����
	 win.draw(*menuTitle); // ��������� ���� �������� � ����
};

// ����� ������������� ������������ �������� �������� � ����
void menuObjects::menuObjectsDefaultImageSetAdjustment(int *psBigY, int *psTreeX, int *pmTitleY, int *psCuteX)
{
	if (*psBigY > 0) *psBigY -= 7; //������������ ��� ������� ����� ������ �������� � ���� ��� ��������� �������� ����
	if (*psTreeX < 0) *psTreeX += 20; //������������ ������� ����� ������� �������� � ���� ��� ���������� �������� ����
	if (*pmTitleY < 0) *pmTitleY += 10; // ������������ ������� ������� �������� ������� ����� � ���� ��� ���������� �������� ����
	if (*psCuteX < 700) *psCuteX += 12; // ������������ ������� ������ ������ �������� ����� ��� ���������� �������� ����
};

// ����� ������ � �������� ������� � ����
void menuObjects::menuActiveText(Font *grobold, int *startTextPosX, Color *pSelected, RenderWindow &win, std::string str, int smX, int smY, bool sm)
{
	Text startText(str, *grobold, 40); // ����� ������ �����, ����� grobold, ���� 40
	if ((*startTextPosX) > smX)       (*startTextPosX) -= 40; // ������������ �� ���� ������� ������ 
	if (sm) startText.setPosition((*startTextPosX), smY); else  startText.setPosition(smX,smY); // ������� ������� ������ 
	startText.setFillColor(*pSelected); // �������  ������� ������ 
	win.draw(startText);
};

// ����� ������ ������ � ����
void menuObjects::menuText(Font *srift, int sriftSize, RenderWindow &win, std::string str, int smX, int smY, Color *color)
{
	Text developerText(str, *srift, sriftSize);// ����� �������
	developerText.setPosition(smX, smY); // ������� ������� 
	developerText.setFillColor(*color); // �������  ������� 
	win.draw(developerText); // ��������� ���� ������� 
};
// ����� ������ ������ � ����
void menuObjects::menuText_plus_valuie(Font *srift, int sriftSize, RenderWindow &win, std::string str, int smX, int smY, Color *color, int valuie)
{
	char hurryUp[20];

	Text hurryUpTextt(str, *srift, sriftSize); // ������ ���������� ����� � 22 ������
	hurryUpTextt.setFillColor(*color); // �������� Hurry Up ������
	hurryUpTextt.setPosition(smX, smY); // ������������� ����� Hurry Up

	sprintf(hurryUp, "%d", valuie); // ����� ������ Hurry Up
	Text hurryUpText(hurryUp, *srift, sriftSize); // ������ ���������� ����� � 22 ������
	hurryUpText.setFillColor(*color); // �������� Hurry Up ������
	hurryUpText.setPosition(smX+ (str.length()*0.5)*sriftSize, smY); // ������������� ����� Hurry Upz	

	win.draw(hurryUpText); // ������� � ���� Hurry Up
	win.draw(hurryUpTextt); // ������� � ���� Hurry Up
};


