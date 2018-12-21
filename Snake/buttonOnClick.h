#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

class buttonOnClick
{
private:

	float menuTimer = 0.6, extraTimer = 0.0f, keyPresstimer;
	float *pmenuTimer = &menuTimer,*pextraTimer =&extraTimer,*pkeyPresstimer=&keyPresstimer;
	
public:
	void crossExit(sf::RenderWindow  & win); // // работа с клавишами окна и бардюра
	bool keyMusicOverMenu(sf::RenderWindow  & win, bool music, sf::Music &menuMusic); // включение отключение музыки в меню пройгрыша
	bool keyMusic(sf::RenderWindow  & win, bool music, sf::Music &overMusic); // включение отключение музыки пои переходе гл меню
	bool keyMusicGame(sf::RenderWindow  & win, bool music, sf::Music &gameMusic); // включение отключение музыки при входе в игру
	void MenuKeySelection(sf::RenderWindow  & win, unsigned int *menuSelection, sf::Sound *selectS, sf::Sound *selectedS, sf::Music *menuMusic, int *pgameState);//  метод управления кнопками меню
	void MenuKeyBack(sf::RenderWindow  & win, int *pscore, int *psnakeSize, int *pgameState, bool *pstartNow, bool *pmenuStart); // метод управления кнопками enter,backspace,Escape
	void MenuKeyBackToolAndHighScore(int *pgameState);// метод выхода из инструкции и очков нажатием клавиши enter или esscape
	int GameControl(int dir);// метод управления в игре
};

