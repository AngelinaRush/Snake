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
	void crossExit(sf::RenderWindow  & win); // // ������ � ��������� ���� � �������
	bool keyMusicOverMenu(sf::RenderWindow  & win, bool music, sf::Music &menuMusic); // ��������� ���������� ������ � ���� ���������
	bool keyMusic(sf::RenderWindow  & win, bool music, sf::Music &overMusic); // ��������� ���������� ������ ��� �������� �� ����
	bool keyMusicGame(sf::RenderWindow  & win, bool music, sf::Music &gameMusic); // ��������� ���������� ������ ��� ����� � ����
	void MenuKeySelection(sf::RenderWindow  & win, unsigned int *menuSelection, sf::Sound *selectS, sf::Sound *selectedS, sf::Music *menuMusic, int *pgameState);//  ����� ���������� �������� ����
	void MenuKeyBack(sf::RenderWindow  & win, int *pscore, int *psnakeSize, int *pgameState, bool *pstartNow, bool *pmenuStart); // ����� ���������� �������� enter,backspace,Escape
	void MenuKeyBackToolAndHighScore(int *pgameState);// ����� ������ �� ���������� � ����� �������� ������� enter ��� esscape
	int GameControl(int dir);// ����� ���������� � ����
};

