#include "randomFood.h"

void randomFood::generationSetFood(int *foodXX, int *foodYY, sf::Sprite &food) { // метод генерации случайного расположения фрукта
	(*foodXX) = (rand() % 928) + 16; // генерируем случайную координату по х
	(*foodXX) -= (*foodXX % 16); // дробные клетки нас не интересуют х
	(*foodYY) = (rand() % 528) + 16; // генерируем случайную координату по у
	(*foodYY) -= (*foodYY % 16); // дробные клетки нас не интересуют у
	food.setPosition(*foodXX, *foodYY); // ставим фрут в сгенерированные выше координаты
}

void randomFood::generationFood(RenderWindow &win, int *foodXX, int *foodYY, sf::Sprite &food, Texture &Tfood, int *pfps, Texture *pTbonusFood, int *px, int *py, int *psnakeSize, int *pscore, Point *point, Sound *pbonusTime, Sound *peat, Sound *pbonusAppear, Color *pbeat, Font *pgothic, int *pfoodCount, int *pbonus, bool *pbonusStart, bool *pincreaseLevel, bool *pbonusBool) {//  метод проверки и посатновки фрукта
	
	if ((*pfoodCount) % 10 == 0 && (*pincreaseLevel)) // если делиться на 10 без остатка и увеличен уровень(съели фрукт)
		(*pfps)++, (*pincreaseLevel) = false, win.setFramerateLimit((*pfps)); // добавляем скороть обновления кадров+ снимаем флаг увеличения уровня+ обновляем скорость обновления кадров

	if ((*pfoodCount) % 5 == 0 && (*pfoodCount) != 0 && (*pbonusBool)) { // если делиться на 5 без остатка + съели хотя бы один фрукт+ бонус доступен
		if (*pbonusStart) {
			food.setTexture(*pTbonusFood); // ставим бонусную текстуру фрукта
			(*pbonusAppear).play(); // включаем звук появления бонуса
			(*pbonusTime).play(); // включаем музыку бонусного время
			*pbonusStart = false; //ставим флажок о том, что бонус уже был
			(*pbonus) = (*pfps) * 50; // время действия бонуса
		}
		if ((*pbonus) > 1) { // если время бонуса не истекло
			if ((*px) == (*foodXX) && (*py) == (*foodYY)) { // если съели фрукт
				(*pbonusAppear).play(); // включаем звук исчезнавения бонуса
				(*pbonusTime).stop(); // отключаем музыку бонусного время
				randomFood randomFood;// создаём объект класса генерации фрукта
				randomFood.generationSetFood(foodXX, foodYY, food); // ставим фрукт по этим координатам
				(*psnakeSize)++; // добавить к размерам змейки +1
				(*pfoodCount)++; // добавить в счётчик еды +1
				(*pscore) += (*pbonus); // добавить бонус к очкам
				(*pincreaseLevel) = true; // ставим флаг о том, что съели фрукт
			}
			menuObjects menuObjects;// создаём объект класса
			menuObjects.menuText_plus_valuie(pgothic, 22, win, "Hurry Up :", 380, 565, pbeat, *pbonus); // вывод текста и переменной с временем бонус


			(*pbonus) -= 10; // отнимаем 10 очков от бонуса
		}
		if ((*pbonus) == 0) // если бонус равен 0
			(*pbonusBool) = false, food.setTexture(Tfood), (*pbonusAppear).play();  // ставим обычную текстуру еди и музыку съедания
	}
	else {
		food.setTexture(Tfood); // ставим текстуру обычного фрукта
		(*pbonusStart) = true; // ставим флажок доступности бонуса
		if ((*px) == (*foodXX) && (*py) == (*foodYY)) { // если съели фрукт
			(*peat).play(); // чавкаем
			(*pscore) += ((*pfps) - 9); // добовляем очки по формуле fps-9
			randomFood randomFood;// создаём объект класса генерации фрукта
			randomFood.generationSetFood(foodXX, foodYY, food); // ставим фрукт 

			(*psnakeSize)++; // добавляем клетку к размерам змеи
			(*pfoodCount)++; // считаем фруктик
			(*pbonusBool) = true; // включаем что мы можем получить бонус при другом условие
			(*pincreaseLevel) = true; // ставим флаг о том, что съели фрукт
		}
	}


	for (int i = 1; i < (*psnakeSize) - 1; i++) {
		while ((*foodXX) == point[i].x && (*foodYY) == point[i].y) { // цикл генераци фрукта если он съеден
			randomFood randomFood;// создаём объект класса
			randomFood.generationSetFood(foodXX, foodYY, food); // ставим фрукт 
		}
	}
	win.draw(food);// нарисовать в окне еду
}