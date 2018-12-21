#include "snake.h"

void snake::snakeCreate(RenderWindow &win,int *psnakeSize, int *px, int *py, Point *point, int *foodXX, 
	                    int *foodYY, int *pdir, Texture *pTbodyHorr,Texture *pTbodyVert, Texture *pTheadUp, Texture *pTheadRight, 
	                    Texture *pTheadDown, Texture *pTheadLeft, Texture *pThaaUp, Texture *pThaaDown, Texture *pThaaRight, 
	                    Texture *pThaaLeft, Texture *pTrightUp, Texture *pTleftUp, Texture *pTrightDown, Texture *pTleftDown, Texture *pTtailDown, 
	                    Texture *pTtailUp, Texture *pTtailLeft, Texture *pTtailRight, Sprite *ptail, Sprite *body, Sprite *head, bool *pstartNow2
                        ) // создаем нашую змейку и даём ей дар логики)
{

	for (int i = (*psnakeSize) - 1; i >= 1; i--) { // перемещение хвоста (визуальное)
		point[i].x = point[i - 1].x;// запаздывание от тела по х
		point[i].y = point[i - 1].y;// запаздывание от тела по у
		
		if (point[i].y == point[i - 1].y && point[i].y == point[i + 1].y)
			body[i].setTexture(*pTbodyHorr); // отображаем хвост горизонтально

		if (point[i].x == point[i - 1].x && point[i].x == point[i + 1].x)
			body[i].setTexture(*pTbodyVert); // отображаем хвост вертикально

	}

	if ((*pdir) == 0) { //клавиша вверх
		(*head).setTexture(*pTheadUp); // меняем текстуру головы на верхнюю
		(*py) -= 16; // размер клетки=шагу вверх  
		if ((*px) == (*foodXX) && (*py) < ((*foodYY) + 48) && (*py) >= (*foodYY)) (*head).setTexture(*pThaaUp);
	}
	if ((*pdir) == 1) { //клавиша вправо
		(*head).setTexture(*pTheadRight); // меняем текстуру головы на правую
		(*px) += 16; // размер клетки=шагу вправо
		if ((*py) == (*foodYY) && (*px) > ((*foodXX) - 48) && (*px) <= (*foodXX)) (*head).setTexture(*pThaaRight);
	}
	if ((*pdir) == 2) { //клавиша вниз
		(*head).setTexture(*pTheadDown); // меняем текстуру головы на нижнюю
		(*py) += 16; // размер клетки=шагу вниз
		if ((*px) == (*foodXX) && (*py) > ((*foodYY) - 48) && (*py) <= (*foodYY)) (*head).setTexture(*pThaaDown);
	}
	if ((*pdir) == 3) { //клавиша влево
		(*head).setTexture(*pTheadLeft); // меняем текстуру головы на левую
		(*px) -= 16; // размер клетки=шагу влево
		if ((*py) == (*foodYY) && (*px) < ((*foodXX) + 48) && (*px) >= (*foodXX)) (*head).setTexture(*pThaaLeft);
	}
	(*head).setPosition((*px), (*py)); // показываем текстуру головы (визуально)
	win.draw(*head);// нарисовать в окне голову

	point[0].x = (*px); // координата х направления движения для хвоста физически
	point[0].y = (*py); // координата у направления движения для хвоста физически

	for (int i = 1; i < (*psnakeSize) - 1; i++) { // используется для перемещения текстуры тела котопса(визуальное перемещение)
		if ((point[i].y > point[i - 1].y && point[i].x == point[i - 1].x && point[i].x > point[i + 1].x && point[i].y == point[i + 1].y)
			|| (point[i].y == point[i - 1].y && point[i].x > point[i - 1].x && point[i].x == point[i + 1].x && point[i].y > point[i + 1].y))
			body[i].setTexture(*pTrightUp);// отображение при повороте право-вверх


		if ((point[i].y > point[i - 1].y && point[i].x == point[i - 1].x && point[i].x < point[i + 1].x && point[i].y == point[i + 1].y)
			|| (point[i].y == point[i - 1].y && point[i].x<point[i - 1].x && point[i].x == point[i + 1].x && point[i].y>point[i + 1].y))
			body[i].setTexture(*pTleftUp);// отображение при повороте лево-вверх


		if ((point[i].y<point[i - 1].y && point[i].x == point[i - 1].x && point[i].x>point[i + 1].x && point[i].y == point[i + 1].y)
			|| (point[i].y == point[i - 1].y && point[i].x > point[i - 1].x && point[i].x == point[i + 1].x && point[i].y < point[i + 1].y))
			body[i].setTexture(*pTrightDown);// отображение при повороте право-низ


		if ((point[i].y < point[i - 1].y && point[i].x == point[i - 1].x && point[i].x < point[i + 1].x && point[i].y == point[i + 1].y)
			|| (point[i].y == point[i - 1].y && point[i].x < point[i - 1].x && point[i].x == point[i + 1].x && point[i].y < point[i + 1].y))
			body[i].setTexture(*pTleftDown); // отображение при повороте лево-низ


		if (i < (*psnakeSize) - 1) { // если котопес сменил координаты своего тела 
			body[i].setPosition(point[i].x, point[i].y); // передвигаем текстуру котопса
			win.draw(body[i]); // обновляем в окне наше тело
		}
	}


	if (point[(*psnakeSize) - 2].y > point[(*psnakeSize) - 1].y)
		(*ptail).setTexture(*pTtailDown); //если направление хвоста нижнее показываем картинку нижней стороны

	if (point[(*psnakeSize) - 2].y < point[(*psnakeSize) - 1].y)
		(*ptail).setTexture(*pTtailUp); //если направление хвоста верхнее показываем картинку верхней стороны

	if (point[(*psnakeSize) - 2].x < point[(*psnakeSize) - 1].x)
		(*ptail).setTexture(*pTtailLeft); //если направление хвоста левое показываем картинку левой стороны

	if (point[(*psnakeSize) - 2].x > point[(*psnakeSize) - 1].x) // должно быть не первым, для правильной ориентации хвоста при запуске. 
		(*ptail).setTexture(*pTtailRight);//если направление хвоста правое показываем картинку правой стороны


	if (*pstartNow2)
		(*ptail).setPosition(point[(*psnakeSize) - 1].x, point[(*psnakeSize) - 1].y); // отвечает за движение хвоста(визуальное)
	(*pstartNow2) = true;
	win.draw(*ptail);// нарисовать в окне хвост
};



