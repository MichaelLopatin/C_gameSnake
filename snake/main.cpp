
#include <stdio.h>
#include <windows.h>//��� ������ gotoxy
#include <conio.h>//���� ����� � ����������
#include <locale.h>//���������� ������� ����
#include <time.h>//��� �������
#include <stdlib.h>//��� �������

#define FRAME_UP 2 //������� �������� ����
#define FRAME_DOWN 20
#define FRAME_LEFT 5
#define FRAME_RIGHT 74

#define ESC 27 //��� ������� ������
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define STUFF -32

#define BEGIN_SNAKE_SZ 5 //��������� ����� ������
#define MENU_SZ 4 //������ ������� ����
#define SPEED 200 //�������� �������� ������
#define LEVEL_SPEED 3//�������� ������������ �������

char menu_items[MENU_SZ][16] = { " ������  ���� ", "  ����������  ", "   ��������   ", "    �����     " };//������� ����


void gotoxy(int x, int y);
void settextattr(WORD attr);

void food(int area[FRAME_RIGHT][FRAME_DOWN]);//������ �������� ���
void game();//����
void control();//����� ���� "����������"
void description();//����� ���� "��������"

void border();//������ ������
void menu(int menuPos);//����
int xRand();//������ x
int yRand();//������ y

void main()
{
	setlocale(LC_ALL, "Russian");

	int quit = 0;
	int menuPos = 0;
	char key;


	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); //����� ��� ������ �����
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
	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);//����� ��� ������ �����
}



void game()
{
	//�������� 1 - ������, 2 - ����, 3 - �����, 4 - �����; 5 - ���
	int area[FRAME_RIGHT][FRAME_DOWN] = { { 0 },{ 0 } };
	int snakeLn = 0; // �������, ���������� ������ �� ���� ��������� ����
	int i;
	int score = 0;
	int level = 1;
	system("cls");
	border();
	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	gotoxy(FRAME_LEFT + 3, FRAME_DOWN + 1);
	printf("ESC - ����� �� ����");
	gotoxy(10, 1);
	printf("�������:", level);
	gotoxy(18, 1);
	printf("%2d", level);
	gotoxy(50, 1);
	printf("C������ �������:", score);
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

		switch (area[xHead][yHead])//�������� ������
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
		default: printf("�� �� ��");
			break;
		}
		Sleep((SPEED - 20 * level) / 4);
		if (snakeLn == 0)
		{
			switch (area[xTail][yTail])//�������� ������
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
			default: printf("�� �� ��");
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
	printf("�������:");
	gotoxy(18, 1);
	printf("%2d", level);
	gotoxy(50, 1);
	printf("C������ �������:");
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
	do//������ �������� ���
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
	printf("����������:");
	gotoxy(27, 5);
	printf("ESC - ����� �� ����");
	gotoxy(20, 6);
	printf("������� ������  %c  - �������� ������", 26);
	gotoxy(20, 7);
	printf(" ������� �����  %c  - �������� �����", 27);
	gotoxy(20, 8);
	printf(" ������� �����  %c  - �������� �����", 24);
	gotoxy(20, 9);
	printf("  ������� ����  %c  - �������� ����", 25);
	gotoxy(19, 18);
	printf("��� ������ � ������� ���� ������� ����� ");
	gotoxy(28, 19);
	printf("������� �� ����������.");
	_getch();
	system("cls");
	border();
}

void description()
{
	system("cls");
	border();
	gotoxy(32, 4);
	printf("�������� ����");
	gotoxy(32, 5);
	printf("���� \"������\".");
	gotoxy(17, 6);
	printf("	���� ���� ������� � ���, ����� ������ ����� ");
	gotoxy(17, 7);
	printf("��� ����� ������ �������.");
	gotoxy(17, 8);
	printf("	��� �������� ������������� ����������");
	gotoxy(17, 9);
	printf("������� ������������� ������� ����, � � ��� ");
	gotoxy(17, 10);
	printf("������������� � �������� �������� ������. ");
	gotoxy(17, 11);
	printf("	��� ��� ���� ��������, �� ��� ����� ����� ���� ");
	gotoxy(17, 12);
	printf("��� ������� (game over). ����� ������ ����");
	gotoxy(17, 13);
	printf("����� �� �������� � ��� ����� �� ������");
	gotoxy(17, 14);
	printf("������� ���� ��� ������� (game over).");
	gotoxy(32, 15);
	printf("����� � ����!");
	gotoxy(19, 18);
	printf("��� ������ � ������� ���� ������� ����� ");
	gotoxy(28, 19);
	printf("������� �� ����������.");
	_getch();
	system("cls");
	border();
}


void menu(int menuPos)
{
	settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	gotoxy(FRAME_LEFT+3, FRAME_DOWN+1);
	printf("ESC - ����� �� ����");
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
			settextattr(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY); //����� ��� ������ �����
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


