#include "buttonOnClick.h"

Clock menuClock, extraClock, keyPressclock, *pmenuClock = &menuClock,*pextraClock= &extraClock,*pkeyPressclock=&keyPressclock;

void buttonOnClick::crossExit(sf::RenderWindow  & win){ // работа с клавишами окна и бардюра
	sf::Event ev; //создаем объект класса
	while (win.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)// если получено событие нажатие на крестик
			win.close(); // закрываем окно
	}
}

bool buttonOnClick::keyMusicOverMenu(sf::RenderWindow  & win, bool music, sf::Music &menuMusic) {// включение отключение музыки в меню пройгрыша
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::M) && menuTimer > .5) { // если нажата клавиша "М" 
		if (music && menuMusic.Playing) // если музыка включена и играет музыка меню
			menuMusic.pause(), music = false; // ставим музыку на паузу
		else menuMusic.play(), music = true; // иначе воспроизводим
		(*pmenuClock).restart(); //обнуляем таймер зажатия клавиши для борьбы с ложным нажатием
	}
	return music;
}

bool buttonOnClick::keyMusic(sf::RenderWindow  & win, bool music, sf::Music &overMusic) { // включение отключение музыки
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::M) && menuTimer > .5) {// если нажата клавиша М
		if (music && overMusic.Playing) overMusic.pause(), music = false;//выключаем музыку если включена
		else overMusic.play(), music = true;//включаем музыку если отключена
		(*pmenuClock).restart(); //обнуляем таймер зажатия клавиши для борьбы с ложным нажатием
	}
	return music;
}

bool buttonOnClick::keyMusicGame(sf::RenderWindow  & win, bool music, sf::Music &gameMusic) { // включение отключение музыки
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::M) && menuTimer > .5) {
		if (music && gameMusic.Playing)
			gameMusic.pause(), music = false; // если музыка играет отключаем её
		else gameMusic.play(), music = true; // если нет играет включаем
		(*pmenuClock).restart(); //обнуляем таймер зажатия клавиши для борьбы с ложным нажатием
	}
	return music;
}

void buttonOnClick::MenuKeySelection(sf::RenderWindow  & win, unsigned int *menuSelection,sf::Sound *selectS, sf::Sound *selectedS, sf::Music *menuMusic, int *pgameState) {//метод управления кнопками меню
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();

	
	if (Keyboard::isKeyPressed(Keyboard::Down) && menuTimer > .2)  // если нажата клавиша вниз в течение 0,2сек
		(*menuSelection)++, (*pmenuClock).restart(), (*selectS).play(); // изменяем переменную выбора+ обнуляем таймер зажатия клавиши для борьбы с ложным нажатием+ запускаем музыку выбора

	if (Keyboard::isKeyPressed(Keyboard::Up) && menuTimer > .2) // если нажата клавиша вверх в течение 0,2сек
		(*menuSelection)--, (*pmenuClock).restart(), (*selectS).play(); // изменяем переменную выбора+ обнуляем таймер зажатия клавиши для борьбы с ложным нажатием+ запускаем музыку выбора

	
	if ((Keyboard::isKeyPressed(Keyboard::Enter)  && menuTimer > .2)|| (sf::Mouse::isButtonPressed(sf::Mouse::Left))) { // если нажата клавиша enter в течение 0,2сек
		(*pextraClock).restart(); // обнуляем счётчик нажатия клавшии
		(*selectedS).play(); // звук открытия выбранного из меню пункта
		switch (*menuSelection % 4) { // выбираем один из 4ех пунктов в меню с помощью переменной выбора
		case 0: // выбран 0-евой пункт
			(*pgameState) = 1; // даём программе понять, что нужно включить игру
			(*menuMusic).stop(); // останавливаем музыку
			break;
		case 1: // выбран 1-ый пункт
			(*pgameState) = 3; // даём программе понять, что нужно включить меню инструкция
			break;
		case 2: // выбран 2-ой пункт
			(*pgameState) = 4; // даём программе понять, что нужно включить меню рекорда
			break;
		case 3: // выбран 3-ий пункт
			win.close(); // даём программе понять, что нужно закрыть окно
			break;
		}

	}
	// выбор движением мышки одну из 4ех кнопок
	if (sf::IntRect(350, 140, 1500, 50).contains(sf::Mouse::getPosition(win))) { if ((*menuSelection) == (1 || 2 || 3)) (*selectS).play(); (*menuSelection) = 0; }
	if (sf::IntRect(350, 220, 1500, 50).contains(sf::Mouse::getPosition(win))) { if ((*menuSelection) != 1) (*selectS).play(); (*menuSelection) = 1; }
	if (sf::IntRect(350, 300, 1500, 50).contains(sf::Mouse::getPosition(win))) { if ((*menuSelection) != 2) (*selectS).play(); (*menuSelection) = 2; }
	if (sf::IntRect(350, 380, 1500, 50).contains(sf::Mouse::getPosition(win))) { if ((*menuSelection) != 3) (*selectS).play(); (*menuSelection) = 3; }

}

void buttonOnClick::MenuKeyBack(sf::RenderWindow  & win, int *pscore, int *psnakeSize, int *pgameState, bool *pstartNow, bool *pmenuStart) {// метод управления кнопками enter,backspace,Escape
	menuTimer = (*pmenuClock).getElapsedTime().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::BackSpace) || Mouse::isButtonPressed(sf::Mouse::Right)) { // если нажата одна из 3ех клавиш enter или backspace или escape
		int sBigY = 240, sTreeX = -400, mTitleY = -200, sCuteX = 260; // переменные координат картинок в главном меню
		(*pscore) = 0; // обнуляем очки
		(*psnakeSize) = 3;//изначальный размер котопса
		(*pgameState) = 0; // даём программе что надо открыть главное меню
		(*pstartNow) = true;
		(*pmenuStart) = true;
		sBigY = 240; // переменные координат картинок в главном меню ставим значение поумолчанию 
		sTreeX = -400; // переменные координат картинок в главном меню ставим значение поумолчанию 
		mTitleY = -200; // переменные координат картинок в главном меню ставим значение поумолчанию 
		sCuteX = 260;  // переменные координат картинок в главном меню ставим значение поумолчанию 
		(*pmenuClock).restart(); //обнуляем таймер зажатия клавиши для борьбы с ложным нажатием
	}

}

void buttonOnClick::MenuKeyBackToolAndHighScore(int *pgameState) { // метод выхода из инструкции и очков нажатием клавиши enter или esscape
	(*pextraTimer) = (*pextraClock).getElapsedTime().asSeconds(); // определение таймера
	if (Keyboard::isKeyPressed(Keyboard::Enter) && extraTimer > .2) // если нажата клавиша enter в течение 0,2сек
		(*pgameState) = 0, (*pextraClock).restart(); // даём программе понять что нужно открыть гл меню + обнулить таймер нажатия
	if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::BackSpace) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))  // если нажата одна из клавиш Escape или BackSpace
		(*pgameState) = 0; // даём программе понять что нужно открыть гл меню
}

int buttonOnClick::GameControl(int dir) {// метод управления в игре
	//4-и направления  движения
	(*pkeyPresstimer) = (*pkeyPressclock).getElapsedTime().asSeconds();
	if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && dir != 2 && dir != 0 && (*pkeyPresstimer) > .05)
		dir = 0, (*pkeyPressclock).restart();  // выбираем направление+ сбрасываем таймер для борьбы с ложным нажатием
	if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && dir != 3 && dir != 1 && (*pkeyPresstimer) > .05)
		dir = 1, (*pkeyPressclock).restart(); // выбираем направление+ сбрасываем таймер для борьбы с ложным нажатием
	if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && dir != 0 && dir != 2 && (*pkeyPresstimer) > .05)
		dir = 2, (*pkeyPressclock).restart(); // выбираем направление+ сбрасываем таймер для борьбы с ложным нажатием
	if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && dir != 1 && dir != 3 && (*pkeyPresstimer) > .05)
		dir = 3, (*pkeyPressclock).restart(); // выбираем направление+ сбрасываем таймер для борьбы с ложным нажатием
	return dir;
}
