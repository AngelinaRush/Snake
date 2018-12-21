#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include "buttonOnClick.h"
#include "randomFood.h"
#include "menuObjects.h"
#include "KillSnake.h"
#include "snake.h"
#include "StructPoint.h" // �������� ���������, ������������ � ���� � ����� ����������� ������
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // ��������� �������
#pragma warning(disable: 4996) // Disable deprecation

using namespace std; 
using namespace sf;



int main()
{
	// ������� ���������� ��� ��������
	Music menuMusic, gameMusic, overMusic;
	SoundBuffer SBeat, SBdie, SBselect, SBselected, SBbonusAppear, SBbonusTime;
	Font gothic, grobold; //������ 
	Texture Tbg, TsnakePng, TheadUp, TheadDown, TheadLeft, TheadRight, TbodyHorr, TbodyVert, TtailUp, TtailDown, TtailLeft, TtailRight, TleftUp,
		TleftDown, TrightUp, TrightDown, Tfood, TbonusFood, ThaaUp, ThaaDown, ThaaLeft, ThaaRight, TmenuBG, TsnakeCute, TsnakeBig,
		TmenuTitle, ToverBG, ThelpBG, TbeatBG, ThighBG, Tintro; // ��������� ��������


		// ������ ���� ������ �������� ������
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
	// ��������� ������� �������� �����
	gameMusic.setVolume(45); // ������������� ��������� ������ 45%
	menuMusic.setVolume(60); // ������������� ��������� ������ ���� 60%
	overMusic.setVolume(60); // ������������� ��������� ������ ��������� ���� 45%

	// ������ ���� ����������� ����� �������
	Color selected(85, 104, 42, 200), notSelected(121, 130, 59, 100), beat(200, 20, 20), dev(255, 255, 255, 100),Red(255, 0, 0),Yelow(255,255,0); // ���� ����� ��� �������
	//������ ������� (�������������+ ���������)
	Sprite  head(TheadRight), tail(TtailRight), body[500], food(Tfood), menuBG(TmenuBG), snakeCute(TsnakeCute),
		snakeBig(TsnakeBig), menuTitle(TmenuTitle), overBG(ToverBG), helpBG(ThelpBG), highBG(ThighBG), bgspr(Tbg);
	// ����� �� �������� ����������� �� �������
	Sound eat(SBeat), dieS(SBdie), bonusAppear(SBbonusAppear), bonusTime(SBbonusTime), selectS(SBselect), selectedS(SBselected);

	//���������� �������������
	int fps = 10, foodX = 16, foodY = 16, score = 0, snakeSize = 3, highscore = 0, foodCount=0, bonus = 600; ;
	int x, y;
	int startTextPosX, instructTextPosX, highscoreTextPosX, exitTextPosX = 1215;
	int sBigY = 240, sTreeX = -400, mTitleY = -200, sCuteX = 260; // ���������� ��������� �������� � ������� ����
	int dir = 1;/*
	___________DIRECTIONS (dir)______________
	# 0 = �����
	# 1 = ������
	# 2 = ����
	# 3 = �����
	*/
	int gameState = 0;/*
	___________gameState__________________
	0 = ������� ����s
	1 = ������ ����
	2 = ����  ���������
	3 = ����������
	4 = ������
	*/
	//���������� ����������
	bool startNow = true, startNow2 = false, menuStart = true, overStart = true, music = true;
	bool increaseLevel = false, bonusBool = true, bonusStart = true;
	//���������� ���������� �������������
	unsigned int menuSelection = 0; // ���������� ������ ������ ����

	//��������� �������������
	int *foodXX = &foodX, *foodYY = &foodY, *pscore = &score, *psnakeSize = &snakeSize, *pgameState = &gameState,*psBigY =&sBigY,*psTreeX=&sTreeX,*pmTitleY=&mTitleY,*psCuteX=&sCuteX,*structX,*StructY,*pfps=&fps,*px=&x, *py=&y, *pfoodCount= &foodCount, *pbonus = &bonus, *pdir=&dir;
	//��������� ������������� ����������
	unsigned int *pmenuSelection = &menuSelection;
	//��������� ����������
	bool *pstartNow = &startNow, *pmenuStart = &menuStart;
	bool *pincreaseLevel = &increaseLevel, *pbonusBool =&bonusBool, *pbonusStart = &bonusStart,*pstartNow2=&startNow2;
	//��������� ������� ������
	Color *pSelected, *pbeat= &beat;
	Texture *pTbonusFood = &TbonusFood, *pTbodyHorr = &TbodyHorr, *pTbodyVert = &TbodyVert, *pTheadUp = &TheadUp, *pTheadDown = &TheadDown, *pTheadLeft = &TheadLeft, *pTheadRight = &TheadRight, *pThaaUp = &ThaaUp, *pThaaDown = &ThaaDown, *pThaaLeft = &ThaaLeft, *pThaaRight = &ThaaRight; 
	Texture *pTtailUp = &TtailUp, *pTtailDown = &TtailDown, *pTtailLeft = &TtailLeft, *pTtailRight = &TtailRight, *pTrightUp = &TrightUp, *pTleftUp = &TleftUp, *pTrightDown = &TrightDown, *pTleftDown = &TleftDown;
	Sound *pbonusTime = &bonusTime,*peat=&eat,*pbonusAppear=&bonusAppear;
	Font *pgothic = &gothic;
	Sprite  *ptail = &tail;
	// ���������� ����� ���������
	Point point[1500]; // ������ �� ������ ���� ������ ������������ ������ ������

	

	RenderWindow win(VideoMode(960, 600), "CatDog"); // ������� ���� �������� 960 �� 600 c �������� CatDog � �������
	win.setFramerateLimit(20); // ������������� ������� ������

	menuObjects menuObjects; // ������ ������ ������ �������� ����
	menuObjects.menuObjectsDefaultImageSet(psBigY, psTreeX, pmTitleY, psCuteX,&snakeBig,&menuTitle,&snakeCute, win);//�������� ����� ������������ ���� �������� � ���� �� ������ �����

	srand(time(NULL)); // ���������� ���� ��� ���������� ��������������� ����� �� ��������� �������� �������



	while (win.isOpen())//���� ������� ����
	{
		buttonOnClick buttonOnClick; // ������ ������ ������ buttonOnClick
		buttonOnClick.crossExit(win); // ���� ����� ������� ���� ������� ����
		
		
		/// MENU

		if (gameState == 0) { // ��� ��������� ������, ��� ����� ��������� � �� ����
			win.clear(); // ������� ����
			win.draw(menuBG); // ������ ��� ����

			if (menuStart) { // ���� ������� �������� ����
				freopen("resources/data", "r", stdin); // ��������� �������
				cin >> highscore;// ���������� ��� ������
				fclose(stdin); // ��������� �������

				overMusic.stop();// ���������� ������ � ���������
				if (music) menuMusic.play(); // ������ ������ ��� ��� � ����������� �� ������ ���������� ������
				menuStart = false; // ���� ��������� ���� ������� ������ ������
				menuMusic.setLoop(true);//������������ ������

				startTextPosX = 965; // ����������� ���������� � ��� ������
				instructTextPosX = 965; // ����������� ���������� � ��� ����������
				highscoreTextPosX = 1070; // ����������� ���������� � ��� �������
				exitTextPosX = 1215; // ����������� ���������� � ��� ������
			}


			music = buttonOnClick.keyMusicOverMenu(win, music, menuMusic); // ��������� � ���������� ������ �� ������� "M" � ���� ��������� 
			menuObjects.menuObjectsDefaultImageSetAdjustment(psBigY, psTreeX, pmTitleY, psCuteX); // �������� ����� ������������� ������������ �������� �������� � ����
			menuObjects.menuObjectsDefaultImageSet(psBigY, psTreeX, pmTitleY, psCuteX, &snakeBig, &menuTitle, &snakeCute, win);//�������� ����� ������������ ���� �������� � ���� �� ������ �����
			menuObjects.menuText(&gothic, 25, win, "Developed by Angel", 350, 560, &dev); // �������� ����� ����� ������ � ����
			buttonOnClick.MenuKeySelection(win, &menuSelection, &selectS, &selectedS, &menuMusic, pgameState); // �������� ����� ���������� �������� ����

			// ������� ������������� ����� �� ������ ���� � ����������� �� ������ ������������
			if ((menuSelection % 4) == 0) pSelected = &selected; else pSelected = &notSelected; // ������ ���� � ����������� �� ������ ��� �������� ������
			menuObjects.menuActiveText(&grobold, &startTextPosX, pSelected, win, "START", 565, 140, true); // ������� �������� ����� 

			if ((menuSelection % 4) == 1) pSelected = &selected; else pSelected = &notSelected; // ������ ���� � ����������� �� ������ ��� �������� ������
			menuObjects.menuActiveText(&grobold, &startTextPosX, pSelected, win, "INSTRUCTIONS", 485, 220, true);// ������� �������� ����� 

			if ((menuSelection % 4) == 2) pSelected = &selected; else pSelected = &notSelected; // ������ ���� � ����������� �� ������ ��� �������� ������
			menuObjects.menuActiveText(&grobold, &startTextPosX, pSelected, win, "HIGHSCORE", 510, 300, true);// ������� �������� ����� 

			if ((menuSelection % 4) == 3) pSelected = &selected; else pSelected = &notSelected; // ������ ���� � ����������� �� ������ ��� �������� ������
			menuObjects.menuActiveText(&grobold, &startTextPosX, pSelected, win, "EXIT", 575, 380, true);// ������� �������� ����� 


		}
		/// GAME LOOP
		if (gameState == 1) { // ��� ��������� ������, ��� ����� ������ ����
			win.clear();// �������� ����
			win.draw(bgspr);// ���������� �����

			if (startNow) {
				fps = 10; // ������ �������� ���������� �������� (�������� ������)
				win.setFramerateLimit(fps); // ������������ ������� ���������� ��������

				if (music) // ���� ������ ��������
				gameMusic.play();  // ��������� ���� ����
				gameMusic.setLoop(true); // ����������� ������ ����

				point[0].x = 32; // ��������� ��������� ���� �
				point[0].y = 32; // ��������� ��������� ���� �
				dir = 1;
				x = 32;
				y = 32;

				tail.setPosition(16, 32);// �������������� ������ ��� �������
				body[1].setTexture(TbodyHorr); // ������ ��������� ����
				body[1].setPosition(32, 32);// �������������� ���� ��� �������

				randomFood randomFood; // ������ ������ ������ ��������� ������
				randomFood.generationSetFood(foodXX, foodYY, food); // ������ ����� 

				startNow = false;
				startNow2 = false;
				overStart = true; // ������ ���� ��� ���� �� ��������
			}

			music = buttonOnClick.keyMusicGame(win, music, gameMusic);// ��������� � ���������� ������ �� ������� "M" 
			dir = buttonOnClick.GameControl(dir); // �������� ����� ���������� � ����

			snake snake; //������ ������ ������
			snake.snakeCreate(win, psnakeSize, px, py, point, foodXX, foodYY, pdir, pTbodyHorr, pTbodyVert, pTheadUp, pTheadRight, pTheadDown, 
				              pTheadLeft, pThaaUp, pThaaDown, pThaaRight, pThaaLeft, pTrightUp, pTleftUp, pTrightDown, 
				              pTleftDown, pTtailDown, pTtailUp, pTtailLeft, pTtailRight, ptail, body, &head, pstartNow2); // ������� ����� ������ � ��� �� ��� ������)

			randomFood randomFood; // ������ ������ ������
			randomFood.generationFood(win, foodXX, foodYY, food, Tfood, pfps, pTbonusFood, px, py, psnakeSize, pscore, point, pbonusTime, peat, 
				                      pbonusAppear, pbeat, pgothic, pfoodCount, pbonus, pbonusStart, pincreaseLevel, pbonusBool); // �������� ����� �������� � ���������� ������

			menuObjects.menuText_plus_valuie(&gothic, 22, win, "Score:", 10, 565, &beat, score); // ����� ������ � ���������� � ������

			if (highscore <= score) {// ���� ������<= ����
				menuObjects.menuText_plus_valuie(&gothic, 22, win, "Best Score:", 800, 565, &Red, highscore); // ����� ������ � ���������� � ������
				highscore = score;// ����������� ������
			}
			else menuObjects.menuText_plus_valuie(&gothic, 22, win, "Best Score:", 780, 565, &beat, highscore); // ����� ������ � ���������� � ������

			KillSnake KillSnake; // �������� ������, ������ ����������� ������
			KillSnake.KillSnakeS(psnakeSize, &dieS, pgameState, x, y, point); // ���� ������ ����������� ������� �)

		}
		/// GAME OVER
		if (gameState == 2) {// ���� ������� ���� ���������
			win.clear();// ������� ����
			if (overStart) {// �������� ������� ����� ����

				freopen("resources/data", "w", stdout);// �������� � ����������
				if (highscore <= score) cout << score << endl;// ���� �������<=�����
				else cout << highscore << endl; // ����� �������
				fclose(stdout); // ��������� ���

				gameMusic.stop();// ��������� ������ ����
				if (music) overMusic.play();// ���� �� ������ ������ ������ �������� ��������
				overStart = false; // ������ ���� �� ��������� ����
				overMusic.setLoop(true);// ����������� �������� ������
				win.setFramerateLimit(20);// ����������� �������� ������
			}
			music=buttonOnClick.keyMusic(win,music,overMusic); // ��������� � ���������� ������ �� ������� "M" � 
			menuMusic.setVolume(100); //������������� ������� ��������� ���� �� 100%

			if (score >= highscore) overBG.setTexture(TbeatBG); // ������ ������ ��� ���� ����� ������
			else overBG.setTexture(ToverBG); // ����� ������ �����������
			win.draw(overBG); // ������� ��� ��� � ����

			menuObjects.menuText_plus_valuie(&gothic, 40, win, "Your Score:", 340, 220, &Yelow, score); // �������� ����� ������ ������ � ���������� � ����
			buttonOnClick.MenuKeyBack(win, pscore, psnakeSize, pgameState, pstartNow, pmenuStart); //  �������� ����� ���������� �������� enter,backspace,Escape
		}
		/// HELP PAGE
		if (gameState == 3) { // ��� ��������� ������, ��� ����� ������� ���� ����������
			win.clear();// ������� ����
			win.draw(helpBG);// ���������� ����

			buttonOnClick.MenuKeyBackToolAndHighScore(pgameState);// �������� ����� ������ �� ���������� � ����� �������� ������� enter ��� esscape
		}
		/// HIGHSCORE PAGE
		if (gameState == 4) { // ���� ������� ���� ��������
			win.clear();// �������� ����
			win.draw(highBG); // �������� ����� ����

			menuObjects.menuText_plus_valuie(&grobold, 40, win, "Highscore :", 350, 280, &beat, highscore); // ������� �����+ ���������.
			menuObjects.menuActiveText(&grobold, &startTextPosX, &selected, win, "BACK", 800, 450, false);// ������� �������� ����� 
			buttonOnClick.MenuKeyBackToolAndHighScore(pgameState);// �������� ����� ������ �� ���������� � ����� �������� ������� enter ��� esscape
		}

		win.display();// ������� ������������ ����
	}
}

