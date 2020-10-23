#include <stdio.h>
#include <Windows.h>
#include<conio.h>
void draw_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf(" <-O-> ");
}
void erase_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("       ");
}
int main()
{
	char ch = ' ';
	int x = 38, y = 20;
	draw_ship(x, y);
	do {
		if (_kbhit()) 
		{
			ch = _getch();
			if (ch == 'a') 
			{ 
				if (x == 0)
				{
					draw_ship(x, y);
				}
				else
				{
					draw_ship(--x, y);
				} 
			}
			if (ch == 'd')
			{ 
				if (x == 80)
				{
					draw_ship(x, y);
				}
				else
				{
					draw_ship(++x, y);
				}
			}
			if (ch == 'w')
			{
				if (y == 0)
				{
					draw_ship(x, y);
				}
				else
				{
					erase_ship(x, y);
					draw_ship(x,-- y);
				}
			}
			if (ch == 's')
			{
					erase_ship(x, y);
					draw_ship(x, ++y);
			}
			fflush(stdin);
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
