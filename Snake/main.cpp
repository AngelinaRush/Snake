#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "buttonOnClick.h"
#include "randomFood.h"
#include "menuObjects.h"
#include "KillSnake.h"
#include "snake.h"
#include "StructPoint.h" // содержит структуру, используемую в двух и более исполняемых файлов
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // отключаем консоль
#pragma warning(disable: 4996) // Disable deprecation

using namespace std; 
using namespace sf;



int main()
{
	// создаем переменные для загрузки
	Music menuMusic, gameMusic, overMusic;
	SoundBuffer SBeat, SBdie, SBselect, SBselected, SBbonusAppear, SBbonusTime;
	Font gothic, grobold; //шрифты 
	Texture Tbg, TsnakePng, TheadUp, TheadDown, TheadLeft, TheadRight, TbodyHorr, TbodyVert, TtailUp, TtailDown, TtailLeft, TtailRight, TleftUp,
		TleftDown, TrightUp, TrightDown, Tfood, TbonusFood, ThaaUp, ThaaDown, ThaaLeft, ThaaRight, TmenuBG, TsnakeCute, TsnakeBig,
		TmenuTitle, ToverBG, ThelpBG, TbeatBG, ThighBG, Tintro; // различные текстуры


		// грузим кучу всяких ненужных файлов
	Tbg.loadFromFile("resources/bgS");
	TheadRight.loadFromFile("resources/headRight.png");
	TheadLeft.loadFromFile("resources/headLeft.png");
	TheadUp.loadFromFile("resources/headUp.png");
	TheadDown.loadFromFile("resources/headDown.png");
	TbodyHorr.loadFromFile("resources/bodyHorr.png");
	TbodyVert.loadFromFile("resources/bodyVert.png");
	TheadRight.loadFromFile("resources/headRight.png");

	TtailRight.loadFromFile("resources/tailRight.png");
	TtailLeft.loadFromFile("resources/tailLeft.png");
	TtailUp.loadFromFile("resources/tailUp.png");
	TtailDown.loadFromFile("resources/tailDown.png");

	TleftUp.loadFromFile("resources/leftUp.png");
	TleftDown.loadFromFile("resources/leftDown.png");
	TrightUp.loadFromFile("resources/rightUp.png");
	TrightDown.loadFromFile("resources/rightDown.png");
	Tfood.loadFromFile("resources/food.png");
	ThaaUp.loadFromFile("resources/haaUp.png");
	ThaaDown.loadFromFile("resources/haaDown.png");
	ThaaLeft.loadFromFile("resources/haaLeft.png");
	ThaaRight.loadFromFile("resources/haaRight.png");
	TbonusFood.loadFromFile("resources/bonusFood.png");

	TmenuBG.loadFromFile("resources/bg");
	TsnakeCute.loadFromFile("resources/maus.png");
	TsnakeBig.loadFromFile("resources/CatBig.png");
	TmenuTitle.loadFromFile("resources/title.png");

	ToverBG.loadFromFile("resources/overBG.png");
	TbeatBG.loadFromFile("resources/overBeatBG.jpg");
	ThelpBG.loadFromFile("resources/help");
	ThighBG.loadFromFile("resources/highBG");

	gothic.loadFromFile("resources/gothic");
	grobold.loadFromFile("resources/grobold");

	SBeat.loadFromFile("resources/eat");
	SBdie.loadFromFile("resources/die");
	SBselect.loadFromFile("resources/select");
	SBselected.loadFromFile("resources/selected");
	SBbonusAppear.loadFromFile("resources/pop");
	SBbonusTime.loadFromFile("resources/bonusTime");

	menuMusic.openFromFile("resources/intro");
	gameMusic.openFromFile("resources/game.wav");
	overMusic.openFromFile("resources/over");
	// закончили грузить ненужные файлы
	gameMusic.setVolume(45); // устанавливаем громкость музыки 45%
	menuMusic.setVolume(60); // устанавливаем громкость музыки меню 60%
	overMusic.setVolume(60); // устанавливаем громкость музыки окончания игры 45%

	// делаем наши стандартные цвета заливки
	Color selected(85, 104, 42, 200), notSelected(121, 130, 59, 100), beat(200, 20, 20), dev(255, 255, 255, 100),Red(255, 0, 0),Yelow(255,255,0); // наши цвета для заливки
	//создаём спрайты (прямоугольник+ структура)
	Sprite  head(TheadRight), tail(TtailRight), body[500], food(Tfood), menuBG(TmenuBG), snakeCute(TsnakeCute),
		snakeBig(TsnakeBig), menuTitle(TmenuTitle), overBG(ToverBG), helpBG(ThelpBG), highBG(ThighBG), bgspr(Tbg);
	// звуки не забываем перегрузить из буффера
	Sound eat(SBeat), dieS(SBdie), bonusAppear(SBbonusAppear), bonusTime(SBbonusTime), selectS(SBselect), selectedS(SBselected);

	//переменные целочисленные
	int fps = 10, foodX = 16, foodY = 16, score = 0, snakeSize = 3, highscore = 0, foodCount=0, bonus = 600; ;
	int x, y;
	int startTextPosX, instructTextPosX, highscoreTextPosX, exitTextPosX = 1215;
	int sBigY = 240, sTreeX = -400, mTitleY = -200, sCuteX = 260; // переменные координат картинок в главном меню
	int dir = 1;/*
	___________DIRECTIONS (dir)______________
	# 0 = Вверх
	# 1 = Вправо
	# 2 = Вниз
	# 3 = Влево
	*/
	int gameState = 0;/*
	___________gameState__________________
	0 = главное менюs
	1 = начать игру
	2 = меню  пройгрыша
	3 = инструкция
	4 = рекорд
	*/
	//переменные логические
	bool startNow = true, startNow2 = false, menuStart = true, overStart = true, music = true;
	bool increaseLevel = false, bonusBool = true, bonusStart = true;
	//переменные безнаковый целочисленный
	unsigned int menuSelection = 0; // переменная выбора пункта меню

	//указатели целочисленные
	int *foodXX = &foodX, *foodYY = &foodY, *pscore = &score, *psnakeSize = &snakeSize, *pgameState = &gameState,*psBigY =&sBigY,*psTreeX=&sTreeX,*pmTitleY=&mTitleY,*psCuteX=&sCuteX,*structX,*StructY,*pfps=&fps,*px=&x, *py=&y, *pfoodCount= &foodCount, *pbonus = &bonus, *pdir=&dir;
	//указатели целочисленные безнаковые
	unsigned int *pmenuSelection = &menuSelection;
	//указатели логические
	bool *pstartNow = &startNow, *pmenuStart = &menuStart;
	bool *pincreaseLevel = &increaseLevel, *pbonusBool =&bonusBool, *pbonusStart = &bonusStart,*pstartNow2=&startNow2;
	//указатели сложных данных
	Color *pSelected, *pbeat= &beat;
	Texture *pTbonusFood = &TbonusFood, *pTbodyHorr = &TbodyHorr, *pTbodyVert = &TbodyVert, *pTheadUp = &TheadUp, *pTheadDown = &TheadDown, *pTheadLeft = &TheadLeft, *pTheadRight = &TheadRight, *pThaaUp = &ThaaUp, *pThaaDown = &ThaaDown, *pThaaLeft = &ThaaLeft, *pThaaRight = &ThaaRight; 
	Texture *pTtailUp = &TtailUp, *pTtailDown = &TtailDown, *pTtailLeft = &TtailLeft, *pTtailRight = &TtailRight, *pTrightUp = &TrightUp, *pTleftUp = &TleftUp, *pTrightDown = &TrightDown, *pTleftDown = &TleftDown;
	Sound *pbonusTime = &bonusTime,*peat=&eat,*pbonusAppear=&bonusAppear;
	Font *pgothic = &gothic;
	Sprite  *ptail = &tail;
	// переменная нашей структуры
	Point point[1500]; // массив не должен быть меньше максимальной длинны змейки

	

	RenderWindow win(VideoMode(960, 600), "CatDog"); // создаем окно размеров 960 на 600 c надписью CatDog в бардюре
	win.setFramerateLimit(20); // устанавливаем частоту кадров

	menuObjects menuObjects; // создаём объект класса объектов меню
	menuObjects.menuObjectsDefaultImageSet(psBigY, psTreeX, pmTitleY, psCuteX,&snakeBig,&menuTitle,&snakeCute, win);//вызываем метод устанавливки всех объектов в меню на нужные места

	srand(time(NULL)); // обновление базы для генератора псевдослучайных чисел на основании текущего времени



	while (win.isOpen())//пока открыто окно
	{
		buttonOnClick buttonOnClick; // создаём объект класса buttonOnClick
		buttonOnClick.crossExit(win); // если нажат крестик пока открыто окно
		
		
		/// MENU

		if (gameState == 0) { // даём программе понять, что нужно вернуться в гл меню
			win.clear(); // очистка окна
			win.draw(menuBG); // рисуем фон меню

			if (menuStart) { // если открыли основное меню
				freopen("resources/data", "r", stdin); // открываем блокнот
				cin >> highscore;// записываем наш рекорд
				fclose(stdin); // закрываем блокнот

				overMusic.stop();// отключение музыки о пройгрыше
				if (music) menuMusic.play(); // музыка играет или нет в зависимости от нашего последнего выбора
				menuStart = false; // если начальное меню закрыто ставим флажок
				menuMusic.setLoop(true);//зацикливание музыки

				startTextPosX = 965; // стандартные координаты х для старта
				instructTextPosX = 965; // стандартные координаты х для инструкции
				highscoreTextPosX = 1070; // стандартные координаты х для рекорда
				exitTextPosX = 1215; // стандартные координаты х для выхода
			}


			music = buttonOnClick.keyMusicOverMenu(win, music, menuMusic); // включение и отключение музыки на клавишу "M" в меню пройгрыша 
			menuObjects.menuObjectsDefaultImageSetAdjustment(psBigY, psTreeX, pmTitleY, psCuteX); // вызываем метод корректировки устанавливки картинок объектов в меню
			menuObjects.menuObjectsDefaultImageSet(psBigY, psTreeX, pmTitleY, psCuteX, &snakeBig, &menuTitle, &snakeCute, win);//вызываем метод устанавливки всех объектов в меню на нужные места
			menuObjects.menuText(&gothic, 25, win, "Developed by Angel", 350, 560, &dev); // вызываем метод вывод текста в окно
			buttonOnClick.MenuKeySelection(win, &menuSelection, &selectS, &selectedS, &menuMusic, pgameState); // вызываем метод управления кнопками меню

			// условия подсвечивания одной из кнопок меню в зависимсоти от выбора пользователя
			if ((menuSelection % 4) == 0) pSelected = &selected; else pSelected = &notSelected; // меняем цвет в зависимости от выбора или невыбора пункта
			menuObjects.menuActiveText(&grobold, &startTextPosX, pSelected, win, "START", 565, 140, true); // выводим активный текст 

			if ((menuSelection % 4) == 1) pSelected = &selected; else pSelected = &notSelected; // меняем цвет в зависимости от выбора или невыбора пункта
			menuObjects.menuActiveText(&grobold, &startTextPosX, pSelected, win, "INSTRUCTIONS", 485, 220, true);// выводим активный текст 

			if ((menuSelection % 4) == 2) pSelected = &selected; else pSelected = &notSelected; // меняем цвет в зависимости от выбора или невыбора пункта
			menuObjects.menuActiveText(&grobold, &startTextPosX, pSelected, win, "HIGHSCORE", 510, 300, true);// выводим активный текст 

			if ((menuSelection % 4) == 3) pSelected = &selected; else pSelected = &notSelected; // меняем цвет в зависимости от выбора или невыбора пункта
			menuObjects.menuActiveText(&grobold, &startTextPosX, pSelected, win, "EXIT", 575, 380, true);// выводим активный текст 


		}
		/// GAME LOOP
		if (gameState == 1) { // даём программе понять, что нужно начать игру
			win.clear();// очистить окно
			win.draw(bgspr);// заполнение фоном

			if (startNow) {
				fps = 10; // данные скорости обновления картинок (скорости змейки)
				win.setFramerateLimit(fps); // ограничиваем частоту обновления картинок

				if (music) // если музыка включена
				gameMusic.play();  // запускаем звук игры
				gameMusic.setLoop(true); // зацикливаем музыку игры

				point[0].x = 32; // начальная кордината тела х
				point[0].y = 32; // начальная кордината тела у
				dir = 1;
				x = 32;
				y = 32;

				tail.setPosition(16, 32);// местоположение хвоста при запуске
				body[1].setTexture(TbodyHorr); // ставим текстурку тела
				body[1].setPosition(32, 32);// местоположение тела при запуске

				randomFood randomFood; // создаём объект класса генерации фрукта
				randomFood.generationSetFood(foodXX, foodYY, food); // ставим фрукт 

				startNow = false;
				startNow2 = false;
				overStart = true; // ставим флаг что игра не окончена
			}

			music = buttonOnClick.keyMusicGame(win, music, gameMusic);// включение и отключение музыки на клавишу "M" 
			dir = buttonOnClick.GameControl(dir); // вызываем метод управления в игре

			snake snake; //создаём объект класса
			snake.snakeCreate(win, psnakeSize, px, py, point, foodXX, foodYY, pdir, pTbodyHorr, pTbodyVert, pTheadUp, pTheadRight, pTheadDown, 
				              pTheadLeft, pThaaUp, pThaaDown, pThaaRight, pThaaLeft, pTrightUp, pTleftUp, pTrightDown, 
				              pTleftDown, pTtailDown, pTtailUp, pTtailLeft, pTtailRight, ptail, body, &head, pstartNow2); // создаем нашую змейку и даём ей дар логики)

			randomFood randomFood; // создаём объект класса
			randomFood.generationFood(win, foodXX, foodYY, food, Tfood, pfps, pTbonusFood, px, py, psnakeSize, pscore, point, pbonusTime, peat, 
				                      pbonusAppear, pbeat, pgothic, pfoodCount, pbonus, pbonusStart, pincreaseLevel, pbonusBool); // вызываем метод проверки и посатновки фрукта

			menuObjects.menuText_plus_valuie(&gothic, 22, win, "Score:", 10, 565, &beat, score); // вывод текста и переменной с очками

			if (highscore <= score) {// если рекорд<= очки
				menuObjects.menuText_plus_valuie(&gothic, 22, win, "Best Score:", 800, 565, &Red, highscore); // вывод текста и переменной с очками
				highscore = score;// присваеваем рекорд
			}
			else menuObjects.menuText_plus_valuie(&gothic, 22, win, "Best Score:", 780, 565, &beat, highscore); // вывод текста и переменной с очками

			KillSnake KillSnake; // создаъем объект, убийца непослушной змейки
			KillSnake.KillSnakeS(psnakeSize, &dieS, pgameState, x, y, point); // если змейка непослушная убиваем её)

		}
		/// GAME OVER
		if (gameState == 2) {// если открыто меню пройгрыша
			win.clear();// очистка окна
			if (overStart) {// проверка условия конца игры

				freopen("resources/data", "w", stdout);// работаем с документом
				if (highscore <= score) cout << score << endl;// если рекород<=очкам
				else cout << highscore << endl; // вывод рекорда
				fclose(stdout); // закрываем его

				gameMusic.stop();// отключаем музыку игры
				if (music) overMusic.play();// если не играет другая музыка включаем грустную
				overStart = false; // ставим флаг об окончании игры
				overMusic.setLoop(true);// зацикливаем грустную музыку
				win.setFramerateLimit(20);// зацикливаем грустную музыку
			}
			music=buttonOnClick.keyMusic(win,music,overMusic); // включение и отключение музыки на клавишу "M" в 
			menuMusic.setVolume(100); //устанавливает уровень громкости меню на 100%

			if (score >= highscore) overBG.setTexture(TbeatBG); // ставим особый фон если побит рекрод
			else overBG.setTexture(ToverBG); // иначе ставим стандартный
			win.draw(overBG); // выводим наш фон в окно

			menuObjects.menuText_plus_valuie(&gothic, 40, win, "Your Score:", 340, 220, &Yelow, score); // вызываем метод вывода текста и переменной в окно
			buttonOnClick.MenuKeyBack(win, pscore, psnakeSize, pgameState, pstartNow, pmenuStart); //  вызываем метод управления кнопками enter,backspace,Escape
		}
		/// HELP PAGE
		if (gameState == 3) { // даём программе понять, что нужно открыть меню инструкции
			win.clear();// очистка окна
			win.draw(helpBG);// заполнение окна

			buttonOnClick.MenuKeyBackToolAndHighScore(pgameState);// вызываем метод выхода из инструкции и очков нажатием клавиши enter или esscape
		}
		/// HIGHSCORE PAGE
		if (gameState == 4) { // если открыто меню рекордов
			win.clear();// очистить окно
			win.draw(highBG); // заливаем фоном окно

			menuObjects.menuText_plus_valuie(&grobold, 40, win, "Highscore :", 350, 280, &beat, highscore); // выводим текст+ переменну.
			menuObjects.menuActiveText(&grobold, &startTextPosX, &selected, win, "BACK", 800, 450, false);// выводим активный текст 
			buttonOnClick.MenuKeyBackToolAndHighScore(pgameState);// вызываем метод выхода из инструкции и очков нажатием клавиши enter или esscape
		}

		win.display();// вывести отрисованное окно
	}
}

