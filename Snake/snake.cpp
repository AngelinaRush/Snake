#include "snake.h"

void snake::snakeCreate(RenderWindow &win,int *psnakeSize, int *px, int *py, Point *point, int *foodXX, 
	                    int *foodYY, int *pdir, Texture *pTbodyHorr,Texture *pTbodyVert, Texture *pTheadUp, Texture *pTheadRight, 
	                    Texture *pTheadDown, Texture *pTheadLeft, Texture *pThaaUp, Texture *pThaaDown, Texture *pThaaRight, 
	                    Texture *pThaaLeft, Texture *pTrightUp, Texture *pTleftUp, Texture *pTrightDown, Texture *pTleftDown, Texture *pTtailDown, 
	                    Texture *pTtailUp, Texture *pTtailLeft, Texture *pTtailRight, Sprite *ptail, Sprite *body, Sprite *head, bool *pstartNow2
                        ) // ������� ����� ������ � ��� �� ��� ������)
{

	for (int i = (*psnakeSize) - 1; i >= 1; i--) { // ����������� ������ (����������)
		point[i].x = point[i - 1].x;// ������������ �� ���� �� �
		point[i].y = point[i - 1].y;// ������������ �� ���� �� �
		
		if (point[i].y == point[i - 1].y && point[i].y == point[i + 1].y)
			body[i].setTexture(*pTbodyHorr); // ���������� ����� �������������

		if (point[i].x == point[i - 1].x && point[i].x == point[i + 1].x)
			body[i].setTexture(*pTbodyVert); // ���������� ����� �����������

	}

	if ((*pdir) == 0) { //������� �����
		(*head).setTexture(*pTheadUp); // ������ �������� ������ �� �������
		(*py) -= 16; // ������ ������=���� �����  
		if ((*px) == (*foodXX) && (*py) < ((*foodYY) + 48) && (*py) >= (*foodYY)) (*head).setTexture(*pThaaUp);
	}
	if ((*pdir) == 1) { //������� ������
		(*head).setTexture(*pTheadRight); // ������ �������� ������ �� ������
		(*px) += 16; // ������ ������=���� ������
		if ((*py) == (*foodYY) && (*px) > ((*foodXX) - 48) && (*px) <= (*foodXX)) (*head).setTexture(*pThaaRight);
	}
	if ((*pdir) == 2) { //������� ����
		(*head).setTexture(*pTheadDown); // ������ �������� ������ �� ������
		(*py) += 16; // ������ ������=���� ����
		if ((*px) == (*foodXX) && (*py) > ((*foodYY) - 48) && (*py) <= (*foodYY)) (*head).setTexture(*pThaaDown);
	}
	if ((*pdir) == 3) { //������� �����
		(*head).setTexture(*pTheadLeft); // ������ �������� ������ �� �����
		(*px) -= 16; // ������ ������=���� �����
		if ((*py) == (*foodYY) && (*px) < ((*foodXX) + 48) && (*px) >= (*foodXX)) (*head).setTexture(*pThaaLeft);
	}
	(*head).setPosition((*px), (*py)); // ���������� �������� ������ (���������)
	win.draw(*head);// ���������� � ���� ������

	point[0].x = (*px); // ���������� � ����������� �������� ��� ������ ���������
	point[0].y = (*py); // ���������� � ����������� �������� ��� ������ ���������

	for (int i = 1; i < (*psnakeSize) - 1; i++) { // ������������ ��� ����������� �������� ���� �������(���������� �����������)
		if ((point[i].y > point[i - 1].y && point[i].x == point[i - 1].x && point[i].x > point[i + 1].x && point[i].y == point[i + 1].y)
			|| (point[i].y == point[i - 1].y && point[i].x > point[i - 1].x && point[i].x == point[i + 1].x && point[i].y > point[i + 1].y))
			body[i].setTexture(*pTrightUp);// ����������� ��� �������� �����-�����


		if ((point[i].y > point[i - 1].y && point[i].x == point[i - 1].x && point[i].x < point[i + 1].x && point[i].y == point[i + 1].y)
			|| (point[i].y == point[i - 1].y && point[i].x<point[i - 1].x && point[i].x == point[i + 1].x && point[i].y>point[i + 1].y))
			body[i].setTexture(*pTleftUp);// ����������� ��� �������� ����-�����


		if ((point[i].y<point[i - 1].y && point[i].x == point[i - 1].x && point[i].x>point[i + 1].x && point[i].y == point[i + 1].y)
			|| (point[i].y == point[i - 1].y && point[i].x > point[i - 1].x && point[i].x == point[i + 1].x && point[i].y < point[i + 1].y))
			body[i].setTexture(*pTrightDown);// ����������� ��� �������� �����-���


		if ((point[i].y < point[i - 1].y && point[i].x == point[i - 1].x && point[i].x < point[i + 1].x && point[i].y == point[i + 1].y)
			|| (point[i].y == point[i - 1].y && point[i].x < point[i - 1].x && point[i].x == point[i + 1].x && point[i].y < point[i + 1].y))
			body[i].setTexture(*pTleftDown); // ����������� ��� �������� ����-���


		if (i < (*psnakeSize) - 1) { // ���� ������� ������ ���������� ������ ���� 
			body[i].setPosition(point[i].x, point[i].y); // ����������� �������� �������
			win.draw(body[i]); // ��������� � ���� ���� ����
		}
	}


	if (point[(*psnakeSize) - 2].y > point[(*psnakeSize) - 1].y)
		(*ptail).setTexture(*pTtailDown); //���� ����������� ������ ������ ���������� �������� ������ �������

	if (point[(*psnakeSize) - 2].y < point[(*psnakeSize) - 1].y)
		(*ptail).setTexture(*pTtailUp); //���� ����������� ������ ������� ���������� �������� ������� �������

	if (point[(*psnakeSize) - 2].x < point[(*psnakeSize) - 1].x)
		(*ptail).setTexture(*pTtailLeft); //���� ����������� ������ ����� ���������� �������� ����� �������

	if (point[(*psnakeSize) - 2].x > point[(*psnakeSize) - 1].x) // ������ ���� �� ������, ��� ���������� ���������� ������ ��� �������. 
		(*ptail).setTexture(*pTtailRight);//���� ����������� ������ ������ ���������� �������� ������ �������


	if (*pstartNow2)
		(*ptail).setPosition(point[(*psnakeSize) - 1].x, point[(*psnakeSize) - 1].y); // �������� �� �������� ������(����������)
	(*pstartNow2) = true;
	win.draw(*ptail);// ���������� � ���� �����
};



