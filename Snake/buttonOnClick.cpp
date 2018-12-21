#include "buttonOnClick.h"

Clock menuClock, extraClock, keyPressclock, *pmenuClock = &menuClock,*pextraClock= &extraClock,*pkeyPressclock=&keyPressclock;

void buttonOnClick::crossExit(sf::RenderWindow  & win){ // ������ � ��������� ���� � �������
	sf::Event ev; //������� ������ ������
	while (win.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)// ���� �������� ������� ������� �� �������
			win.close(); // ��������� ����
	}
}

bool buttonOnClick::keyMusicOverMenu(sf::RenderWindow  & win, bool music, sf::Music &menuMusic) {// ��������� ���������� ������ � ���� ���������
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::M) && menuTimer > .5) { // ���� ������ ������� "�" 
		if (music && menuMusic.Playing) // ���� ������ �������� � ������ ������ ����
			menuMusic.pause(), music = false; // ������ ������ �� �����
		else menuMusic.play(), music = true; // ����� �������������
		(*pmenuClock).restart(); //�������� ������ ������� ������� ��� ������ � ������ ��������
	}
	return music;
}

bool buttonOnClick::keyMusic(sf::RenderWindow  & win, bool music, sf::Music &overMusic) { // ��������� ���������� ������
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::M) && menuTimer > .5) {// ���� ������ ������� �
		if (music && overMusic.Playing) overMusic.pause(), music = false;//��������� ������ ���� ��������
		else overMusic.play(), music = true;//�������� ������ ���� ���������
		(*pmenuClock).restart(); //�������� ������ ������� ������� ��� ������ � ������ ��������
	}
	return music;
}

bool buttonOnClick::keyMusicGame(sf::RenderWindow  & win, bool music, sf::Music &gameMusic) { // ��������� ���������� ������
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::M) && menuTimer > .5) {
		if (music && gameMusic.Playing)
			gameMusic.pause(), music = false; // ���� ������ ������ ��������� �
		else gameMusic.play(), music = true; // ���� ��� ������ ��������
		(*pmenuClock).restart(); //�������� ������ ������� ������� ��� ������ � ������ ��������
	}
	return music;
}

void buttonOnClick::MenuKeySelection(sf::RenderWindow  & win, unsigned int *menuSelection,sf::Sound *selectS, sf::Sound *selectedS, sf::Music *menuMusic, int *pgameState) {//����� ���������� �������� ����
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();

	
	if (Keyboard::isKeyPressed(Keyboard::Down) && menuTimer > .2)  // ���� ������ ������� ���� � ������� 0,2���
		(*menuSelection)++, (*pmenuClock).restart(), (*selectS).play(); // �������� ���������� ������+ �������� ������ ������� ������� ��� ������ � ������ ��������+ ��������� ������ ������

	if (Keyboard::isKeyPressed(Keyboard::Up) && menuTimer > .2) // ���� ������ ������� ����� � ������� 0,2���
		(*menuSelection)--, (*pmenuClock).restart(), (*selectS).play(); // �������� ���������� ������+ �������� ������ ������� ������� ��� ������ � ������ ��������+ ��������� ������ ������

	
	if ((Keyboard::isKeyPressed(Keyboard::Enter)  && menuTimer > .2)|| (sf::Mouse::isButtonPressed(sf::Mouse::Left))) { // ���� ������ ������� enter � ������� 0,2���
		(*pextraClock).restart(); // �������� ������� ������� �������
		(*selectedS).play(); // ���� �������� ���������� �� ���� ������
		switch (*menuSelection % 4) { // �������� ���� �� 4�� ������� � ���� � ������� ���������� ������
		case 0: // ������ 0-���� �����
			(*pgameState) = 1; // ��� ��������� ������, ��� ����� �������� ����
			(*menuMusic).stop(); // ������������� ������
			break;
		case 1: // ������ 1-�� �����
			(*pgameState) = 3; // ��� ��������� ������, ��� ����� �������� ���� ����������
			break;
		case 2: // ������ 2-�� �����
			(*pgameState) = 4; // ��� ��������� ������, ��� ����� �������� ���� �������
			break;
		case 3: // ������ 3-�� �����
			win.close(); // ��� ��������� ������, ��� ����� ������� ����
			break;
		}

	}
	// ����� ��������� ����� ���� �� 4�� ������
	if (sf::IntRect(350, 140, 1500, 50).contains(sf::Mouse::getPosition(win))) { if ((*menuSelection) == (1 || 2 || 3)) (*selectS).play(); (*menuSelection) = 0; }
	if (sf::IntRect(350, 220, 1500, 50).contains(sf::Mouse::getPosition(win))) { if ((*menuSelection) != 1) (*selectS).play(); (*menuSelection) = 1; }
	if (sf::IntRect(350, 300, 1500, 50).contains(sf::Mouse::getPosition(win))) { if ((*menuSelection) != 2) (*selectS).play(); (*menuSelection) = 2; }
	if (sf::IntRect(350, 380, 1500, 50).contains(sf::Mouse::getPosition(win))) { if ((*menuSelection) != 3) (*selectS).play(); (*menuSelection) = 3; }

}

void buttonOnClick::MenuKeyBack(sf::RenderWindow  & win, int *pscore, int *psnakeSize, int *pgameState, bool *pstartNow, bool *pmenuStart) {// ����� ���������� �������� enter,backspace,Escape
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::BackSpace) || Mouse::isButtonPressed(sf::Mouse::Right)) { // ���� ������ ���� �� 3�� ������ enter ��� backspace ��� escape
		int sBigY = 240, sTreeX = -400, mTitleY = -200, sCuteX = 260; // ���������� ��������� �������� � ������� ����
		(*pscore) = 0; // �������� ����
		(*psnakeSize) = 3;//����������� ������ �������
		(*pgameState) = 0; // ��� ��������� ��� ���� ������� ������� ����
		(*pstartNow) = true;
		(*pmenuStart) = true;
		sBigY = 240; // ���������� ��������� �������� � ������� ���� ������ �������� ����������� 
		sTreeX = -400; // ���������� ��������� �������� � ������� ���� ������ �������� ����������� 
		mTitleY = -200; // ���������� ��������� �������� � ������� ���� ������ �������� ����������� 
		sCuteX = 260;  // ���������� ��������� �������� � ������� ���� ������ �������� ����������� 
		(*pmenuClock).restart(); //�������� ������ ������� ������� ��� ������ � ������ ��������
	}

}

void buttonOnClick::MenuKeyBackToolAndHighScore(int *pgameState) { // ����� ������ �� ���������� � ����� �������� ������� enter ��� esscape
	(*pextraTimer) = (*pextraClock).getElapsedTime().asSeconds(); // ����������� �������
	if (Keyboard::isKeyPressed(Keyboard::Enter) && extraTimer > .2) // ���� ������ ������� enter � ������� 0,2���
		(*pgameState) = 0, (*pextraClock).restart(); // ��� ��������� ������ ��� ����� ������� �� ���� + �������� ������ �������
	if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::BackSpace) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))  // ���� ������ ���� �� ������ Escape ��� BackSpace
		(*pgameState) = 0; // ��� ��������� ������ ��� ����� ������� �� ����
}

int buttonOnClick::GameControl(int dir) {// ����� ���������� � ����
	//4-� �����������  ��������
	(*pkeyPresstimer) = (*pkeyPressclock).getElapsedTime().asSeconds();
	if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && dir != 2 && dir != 0 && (*pkeyPresstimer) > .05)
		dir = 0, (*pkeyPressclock).restart();  // �������� �����������+ ���������� ������ ��� ������ � ������ ��������
	if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && dir != 3 && dir != 1 && (*pkeyPresstimer) > .05)
		dir = 1, (*pkeyPressclock).restart(); // �������� �����������+ ���������� ������ ��� ������ � ������ ��������
	if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && dir != 0 && dir != 2 && (*pkeyPresstimer) > .05)
		dir = 2, (*pkeyPressclock).restart(); // �������� �����������+ ���������� ������ ��� ������ � ������ ��������
	if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && dir != 1 && dir != 3 && (*pkeyPresstimer) > .05)
		dir = 3, (*pkeyPressclock).restart(); // �������� �����������+ ���������� ������ ��� ������ � ������ ��������
	return dir;
}
