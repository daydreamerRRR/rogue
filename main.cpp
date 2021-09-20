#include <ncurses.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;

//#TODO: структуру LEVELS переделать в класс;
//#TODO: 4 переменных под положение двери в комнате это ненормальо;
//#TODO: Комнаты (двумерные массивы char[][]) должны располагаться на разных этажах (возможно, массив структур);
//#TODO: генерация комнат на этаже (и дорожек к ним). Возможно, стоит создавать  этаж (массив) 100x100 (или больше)
//       а потом генерировать в нём комнаты;


struct coordinates {
	coordinates (int x, int y) : x(x), y(y) {}
	int x;
	int y;
};

struct LEVELS { 
};



void roomGen(char ** level, int n, int m) {
	//Создание стен, пола, углов
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (j == 0 || i == 0 || j == m - 1 || i == n - 1) {
				*(level[i] + j) = '#';
			}
			else {
				*(level[i] + j) = '.';
			}
		}
	}

	bool isDoorPlcd = false;
	
	if (rand() % 2 == 1) {				 //ВЕРХНЯЯ СТЕНА
		*(level[0] + rand() % 6) = 'T';
		isDoorPlcd = true;
	}
	else if (rand() % 2 == 1) {          //НИЖНЯЯ СТЕНА
		*(level[n - 1] + rand() % 6) = 'T';
		isDoorPlcd = true;
	}
	else if (rand() % 2 == 1) {          //ЛЕВАЯ СТЕНА
		*(level[rand() % 6]) = 'T';
		isDoorPlcd = true;
	}
	else if (rand() % 2 == 1) {          // ПРАВАЯ СТЕНА
		*(level[rand() % 6] + m - 1) = 'T';
		isDoorPlcd = true;
	}
	if (isDoorPlcd == false) {
		*(level[rand() % 6] + m - 1) = 'T';
	}

}

int main() {
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	srand(time(NULL));

	int n, m;

	do {
		n = 6 + rand() % 18;
		m = 6 + rand() % 18;
	} while (n > 17 || n < 7 || m > 17 || m < 7);

	char ** level1 = new char * [100];
	level1[0] = new char [100 * 100];
	for (int i = 1; i != 100; i++) {
		level1[i] = level1[i - 1] + 100;
	}
	roomGen(level1, n, m);
	coordinates pos(4, 4);
	level1[pos.y][pos.x] = 'H'; 

	while (true) {
		clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				printw("%c", level1[i][j]);

			}
			printw("\n");
		}

		//Управление
		switch(getch()) {

			case KEY_UP:
			case 'w':
				if (level1[pos.y - 1][pos.x] == '#') { continue; }
				else if (level1[pos.y - 1][pos.x] == 'T') {
					swap(level1[pos.y - 1][pos.x], level1[pos.y][pos.x]);
					level1[pos.y][pos.x] = '.';
					pos.y--;
				}
				else if (level1[pos.y][pos.x + 1] == '#' && level1[pos.y][pos.x - 1] == '#') {
					swap(level1[pos.y - 1][pos.x], level1[pos.y][pos.x]);
					level1[pos.y][pos.x] = 'T';
					pos.y--;
				}
				else {
					swap(level1[pos.y][pos.x], level1[pos.y - 1][pos.x]);
					pos.y--;
				}
				break;

			case KEY_DOWN:
			case 's':
				if (level1[pos.y + 1][pos.x] == '#') { continue; }
				else if (level1[pos.y + 1][pos.x] == 'T') {
					swap(level1[pos.y + 1][pos.x], level1[pos.y][pos.x]);
					level1[pos.y][pos.x] = '.';
					pos.y++;
				}
				else if (level1[pos.y][pos.x + 1] == '#' && level1[pos.y][pos.x - 1] == '#') {
					swap(level1[pos.y + 1][pos.x], level1[pos.y][pos.x]);
					level1[pos.y][pos.x] = 'T';
					pos.y++;
				}
				else {
					swap(level1[pos.y][pos.x], level1[pos.y + 1][pos.x]);
					pos.y++;
				}
				break;

			case KEY_LEFT:
			case 'a':
				if (level1[pos.y][pos.x - 1] == '#') { continue; }
				else if (level1[pos.y][pos.x - 1] == 'T') {
					swap(level1[pos.y][pos.x - 1], level1[pos.y][pos.x]);
					level1[pos.y][pos.x] = '.';
					pos.x--;
				}
				else if (level1[pos.y + 1][pos.x] == '#' && level1[pos.y - 1][pos.x] == '#') {
					swap(level1[pos.y][pos.x - 1], level1[pos.y][pos.x]);
					level1[pos.y][pos.x] = 'T';
					pos.x--;
				}
				else {
					swap(level1[pos.y][pos.x - 1], level1[pos.y][pos.x]);
					pos.x--;
				}
				break;

			case KEY_RIGHT:
			case 'd':
				if (level1[pos.y][pos.x + 1] == '#') { continue; }
				else if (level1[pos.y][pos.x + 1] == 'T') {
					swap(level1[pos.y][pos.x + 1], level1[pos.y][pos.x]);
					level1[pos.y][pos.x] = '.';
					pos.x++;
				}
				else if (level1[pos.y + 1][pos.x] == '#' && level1[pos.y - 1][pos.x] == '#') {
					swap(level1[pos.y][pos.x + 1], level1[pos.y][pos.x]);
					level1[pos.y][pos.x] = 'T';
					pos.x++;
				}
				else {
					swap(level1[pos.y][pos.x], level1[pos.y][pos.x + 1]);
					pos.x++;
				}
				break;

			case 27:
				endwin();
				system("clear");
				return 0;
				break;	
		}
	
	}
    endwin();
    return 0;
	
}
