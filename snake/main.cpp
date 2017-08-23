
#include <stdio.h>
#include <windows.h>//для работы gotoxy
#include <conio.h>//ввод вывод с клавиатуры
#include <locale.h>//подключить русский язык
#include <time.h>//для рандома
#include <stdlib.h>//для рандома

#define FRAME_UP 2 //границы игрового поля
#define FRAME_DOWN 20
#define FRAME_LEFT 5
#define FRAME_RIGHT 74

#define ESC 27 //код рабочих клавиш
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define STUFF -32

#define BEGIN_SNAKE_SZ 5 //начальная длина змейки
#define MENU_SZ 4 //размер пунктов меню
#define SPEED 200 //скорость движения змейки
#define LEVEL_SPEED 3//скорость переключения уровней

char menu_items[MENU_SZ][16] = { " Начать  игру ", "  Управление  ", "   Описание   ", "    Выход     " };//разделы меню


void gotoxy(int x, int y);
void settextattr(WORD attr);

void food(int area[FRAME_RIGHT][FRAME_DOWN]);//ставит рандомно еду
void game();//игра
void control();//пункт меню "Управление"
void description();//пункт меню "Описание"

void border();//рисует бордюр
void menu(int menuPos);//меню
int xRand();//рандом x
int yRand();//рандом y

void main()
{
	setlocale(LC_ALL, "Russian");

	int quit = 0;
	int menuPos = 0;
	char key;


	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); //белый фон черные буквы
	system("cls");
	border();
	gotoxy(FRAME_LEFT, FRAME_UP);
	while (quit == 0)
	{
		menu(menuPos);
		key = _getch();
		if (key == STUFF)
		{
			key = _getch();
		}
		switch (key)
		{

		case ESC: quit = 1; break;
		case DOWN: menuPos = (menuPos + 1) % MENU_SZ; break;
		case UP: menuPos = (MENU_SZ + menuPos - 1) % MENU_SZ; break;
		case ENTER:
			switch (menuPos)
			{
			case 0: game(); break;
			case 1: control(); break;
			case 2: description(); break;
			case 3: quit = 1; break;
			}
		}
	}
	gotoxy(FRAME_LEFT, FRAME_DOWN + 1);
	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);//белый фон черные буквы
}



void game()
{
	//движение 1 - вправо, 2 - вниз, 3 - влево, 4 - вверх; 5 - еда
	int area[FRAME_RIGHT][FRAME_DOWN] = { { 0 },{ 0 } };
	int snakeLn = 0; // счетчик, показывает должно ли быть удлинение змеи
	int i;
	int score = 0;
	int level = 1;
	system("cls");
	border();
	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	gotoxy(FRAME_LEFT + 3, FRAME_DOWN + 1);
	printf("ESC - выход из игры");
	gotoxy(10, 1);
	printf("Уровень:", level);
	gotoxy(18, 1);
	printf("%2d", level);
	gotoxy(50, 1);
	printf("Cъедено печенек:", score);
	gotoxy(67, 1);
	printf("%4d", score);
	char key;
	int quit = 0;

	int xHead = BEGIN_SNAKE_SZ + FRAME_LEFT + 1;
	int yHead = (FRAME_DOWN + FRAME_UP) / 2;
	int xTail = xHead - BEGIN_SNAKE_SZ;
	int yTail = yHead;
	for (i = 0; i <= BEGIN_SNAKE_SZ; i++)
		area[xHead - i][yHead] = 1;


	food(area);


	for (i = xTail; i <xHead; i++)
	{
		gotoxy(i, yHead);
		printf("%c", 4);
	}
	gotoxy(xHead, yHead);
	printf("%c", 2);

	do
	{
		Sleep(SPEED - level * 20);
		if (_kbhit())
		{
			key = _getch();
			if (key == STUFF)
			{
				key = _getch();
			}
			switch (key)
			{
			case ESC: quit = 1; break;
			case RIGHT:
			{
				if (area[xHead][yHead] != 3)
					area[xHead][yHead] = 1;
				break;
			}
			case DOWN:
			{
				if (area[xHead][yHead] != 4)
					area[xHead][yHead] = 2;
				break;
			}
			case LEFT:
			{
				if (area[xHead][yHead] != 1)
					area[xHead][yHead] = 3;
				break;
			}
			case UP:
			{
				if (area[xHead][yHead] != 2)
					area[xHead][yHead] = 4;
				break;
			}
			default:
				break;
			}


		}

		switch (area[xHead][yHead])//движение головы
		{
		case 1:
		{
			gotoxy(xHead, yHead);
			printf("%c", 4);
			if (((area[xHead + 1][yHead] > 0) && (area[xHead + 1][yHead]) < 5) || (xHead + 1 == FRAME_RIGHT))
				quit = 1;
			if (area[xHead + 1][yHead] == 5)
				snakeLn++;
			xHead++;
			gotoxy(xHead, yHead);
			printf("%c", 2);
			area[xHead][yHead] = 1;
			break;
		}
		case 2:
		{
			gotoxy(xHead, yHead);
			printf("%c", 4);
			if (((area[xHead][yHead + 1] > 0) && (area[xHead][yHead + 1]) < 5) || (yHead + 1 == FRAME_DOWN))
				quit = 1;
			if (area[xHead][yHead + 1] == 5)
				snakeLn++;
			yHead++;
			gotoxy(xHead, yHead);
			printf("%c", 2);
			area[xHead][yHead] = 2;
			break;
		}
		case 3:
		{
			gotoxy(xHead, yHead);
			printf("%c", 4);
			if (((area[xHead - 1][yHead] > 0) && (area[xHead - 1][yHead]) < 5) || (xHead - 1 == FRAME_LEFT))
				quit = 1;
			if (area[xHead - 1][yHead] == 5)
				snakeLn++;
			xHead--;
			gotoxy(xHead, yHead);
			printf("%c", 2);
			area[xHead][yHead] = 3;
			break;
		}
		case 4:
		{
			gotoxy(xHead, yHead);
			printf("%c", 4);
			if (((area[xHead][yHead - 1] > 0) && (area[xHead][yHead - 1]) < 5) || (yHead - 1 == FRAME_UP))
				quit = 1;
			if (area[xHead][yHead - 1] == 5)
				snakeLn++;
			yHead--;
			gotoxy(xHead, yHead);
			printf("%c", 2);
			area[xHead][yHead] = 4;
			break;
		}
		default: printf("НЕ НЕ НЕ");
			break;
		}
		Sleep((SPEED - 20 * level) / 4);
		if (snakeLn == 0)
		{
			switch (area[xTail][yTail])//движение хвоста
			{
			case 1:
			{
				gotoxy(xTail, yTail);
				printf(" ");
				area[xTail][yTail] = 0;
				xTail++;
				break;
			}
			case 2:
			{
				gotoxy(xTail, yTail);
				printf(" ");
				area[xTail][yTail] = 0;
				yTail++;
				break;
			}
			case 3:
			{
				gotoxy(xTail, yTail);
				printf(" ");
				area[xTail][yTail] = 0;
				xTail--;
				break;
			}
			case 4:
			{
				gotoxy(xTail, yTail);
				printf(" ");
				area[xTail][yTail] = 0;
				yTail--;
				break;
			}
			default: printf("Ай Яй Яй");
				break;
			}

		}

		if (snakeLn > 0)
		{
			score++;
			gotoxy(67, 1);
			printf("%4d", score);
			food(area);
		}
		level = 1 + score / LEVEL_SPEED;
		gotoxy(18, 1);
		printf("%2d", level);
		snakeLn = 0;

	} while (quit == 0);
	Sleep(600);
	system("cls");
	border();
	gotoxy(10, 1);
	printf("Уровень:");
	gotoxy(18, 1);
	printf("%2d", level);
	gotoxy(50, 1);
	printf("Cъедено печенек:");
	gotoxy(67, 1);
	printf("%4d", score);
	gotoxy((((FRAME_LEFT + FRAME_RIGHT) / 2) - 7), (((FRAME_DOWN + FRAME_UP) / 2) + FRAME_UP));
	printf("Press any key");

	do
	{
		settextattr(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		gotoxy((((FRAME_LEFT + FRAME_RIGHT) / 2) - 5), ((FRAME_DOWN + FRAME_UP) / 2));
		printf("GAME OVER");
		Sleep(300);
		settextattr(BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE);
		gotoxy((((FRAME_LEFT + FRAME_RIGHT) / 2) - 5), ((FRAME_DOWN + FRAME_UP) / 2));
		printf("GAME OVER");
		Sleep(200);
	} while (!_kbhit());
	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	system("cls");
	border();

}


void food(int area[FRAME_RIGHT][FRAME_DOWN])
{
	int xFood = FRAME_LEFT + 1;
	int yFood = FRAME_UP + 1;
	do//ставит рандомно еду
	{
		int x, y;
		x = xRand();
		y = yRand();
		if (area[x][y] > 0 && area[x][y] < 5)
		{
			xFood = x;
			yFood = y;
		}
		if (area[x][y] == 0)
		{
			area[x][y] = 5;
			xFood = x;
			yFood = y;
		}
		if (area[x][y] == 5)
		{
			xFood = x;
			yFood = y;
			break;
		}
		Sleep(200);
	} while (area[xFood][yFood] < 5);
	gotoxy(xFood, yFood);
	printf("%c", 15);
}


int xRand()
{
	int xR;
	srand(time(NULL));
	xR = FRAME_LEFT + 2 + rand() % (FRAME_RIGHT - FRAME_LEFT - 4);
	return(xR);
}

int yRand()
{
	int yR;
	srand(time(NULL));
	yR = FRAME_UP + 2 + rand() % (FRAME_DOWN - FRAME_UP - 4);
	return(yR);
}


void control()
{
	system("cls");
	border();
	gotoxy(32, 4);
	printf("Управление:");
	gotoxy(27, 5);
	printf("ESC - выход из игры");
	gotoxy(20, 6);
	printf("стрелка вправо  %c  - движение вправо", 26);
	gotoxy(20, 7);
	printf(" стрелка влево  %c  - движение влево", 27);
	gotoxy(20, 8);
	printf(" стрелка вверх  %c  - движение вверх", 24);
	gotoxy(20, 9);
	printf("  стрелка вниз  %c  - движение вниз", 25);
	gotoxy(19, 18);
	printf("Для выхода в главное меню нажмите любую ");
	gotoxy(28, 19);
	printf("клавишу на клавиатуре.");
	_getch();
	system("cls");
	border();
}

void description()
{
	system("cls");
	border();
	gotoxy(32, 4);
	printf("Описание игры");
	gotoxy(32, 5);
	printf("Игра \"Змейка\".");
	gotoxy(17, 6);
	printf("	Суть игры состоит в том, чтобы змейка съела ");
	gotoxy(17, 7);
	printf("как можно больше печенек.");
	gotoxy(17, 8);
	printf("	При съедании определенного количества");
	gotoxy(17, 9);
	printf("печенек увеличивается уровень игры, а с ним ");
	gotoxy(17, 10);
	printf("увеличивается и скорость движения змейки. ");
	gotoxy(17, 11);
	printf("	Так как змея ядовитая, то при укусе самой себя ");
	gotoxy(17, 12);
	printf("она умирает (game over). Также голова змеи");
	gotoxy(17, 13);
	printf("ничем не защищена и при ударе об острые");
	gotoxy(17, 14);
	printf("выступы стен она умирает (game over).");
	gotoxy(32, 15);
	printf("Удачи в игре!");
	gotoxy(19, 18);
	printf("Для выхода в главное меню нажмите любую ");
	gotoxy(28, 19);
	printf("клавишу на клавиатуре.");
	_getch();
	system("cls");
	border();
}


void menu(int menuPos)
{
	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	gotoxy(FRAME_LEFT+3, FRAME_DOWN+1);
	printf("ESC - выход из игры");
	int i;
	for (i = 0; i < MENU_SZ; i++)
	{
		gotoxy(32, 9 + i);
		if (menuPos == i)
		{
			settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			gotoxy(30, 9 + i);
			printf("%c", 26);
			gotoxy(47, 9 + i);
			printf("%c", 27);
			gotoxy(32, 9 + i);
			settextattr(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		}
		else
		{
			settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); //белый фон черные буквы
			gotoxy(30, 9 + i);
			printf("%c", ' ');
			gotoxy(47, 9 + i);
			printf("%c", ' ');
			gotoxy(32, 9 + i);
		}
		printf("%s", menu_items[i]);
	}


}



void border()
{
	int i;
	for (i = FRAME_LEFT + 1; i < FRAME_RIGHT; i++)
	{
		gotoxy(i, FRAME_UP);
		printf("%c", 31);
		gotoxy(i, FRAME_DOWN);
		printf("%c", 30);
	}
	for (i = FRAME_UP; i < FRAME_DOWN + 1; i++)
	{
		gotoxy(FRAME_LEFT, i);
		printf("%c", 16);
		gotoxy(FRAME_RIGHT, i);
		printf("%c", 17);
	}
	gotoxy(FRAME_LEFT, FRAME_DOWN + 3);

}


void settextattr(WORD attr)
{
	HANDLE hs;

	hs = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hs, attr);
}


void gotoxy(int x, int y)
{
	HANDLE hs;
	COORD c = { x, y };

	hs = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hs, c);
}


