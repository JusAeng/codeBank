#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

void setcolor(int,int);
void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x,y);
	setcolor (7,3);
	printf(" <-O-> ");
}
void erase_ship(int x, int y)
{
	gotoxy(x,y);
	setcolor(7,0);
	printf("       ");
}
void bullet_draw(int x, int y)
{
	gotoxy(x,y);
	setcolor(7,7);
	printf(" ");
}
void bullet_delete(int x, int y)
{
	gotoxy(x,y);
	setcolor(7,0);
	printf(" ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console,&lpCursor);
}
void setcolor(int fg,int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg*16+fg);
}
char cursor(int x, int y)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = {x,y}; DWORD num_read;
	if(
	!ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) )
	
	return '\0';
	else
	return buf[0];
}
void score(int sc)
{
	gotoxy(90,0);
	setcolor(7,0);
	printf("          ");
	setcolor (7,3);
	printf("Score : %d",sc);
}


int main()
{
	setcursor(0);
	//enemy
	int loop,xe,ye;
	srand( time( NULL ) );
	for (loop=1;loop<=20;loop++)
	{
		xe=rand()%60+10;
		ye=rand()%5+1;
		gotoxy(xe,ye);
		printf("*");
		
	}

	
	//
	char st,ch = ' ';
	int x = 38, y = 28,bullet[5]={0,0,0,0,0},move=0,x1[5],y1[5],bcount=-1,nbullet=5,i,sc=0;
	draw_ship(x, y);
	
	
	
	
	do {	
//Switch
		if (_kbhit()) 
		{
			ch = _getch();
			if (ch == 'a') 
			{ 
				move=-1;
			}
			else if (ch == 'd')
			{ 	
				move=1;
			}
			else if (ch == 's')
			{ 	
				move=0;
			}
			else if (ch == ' ')
			{
				if(nbullet>0)
				{
					bcount+=1;
					if(bcount==5)
					{
						bcount=0;
					}
					if (move==1)
					{
						x1[bcount]=x+4;
					}
					else if (move==-1)
					{
						x1[bcount]=x+2;
					}
					else if (move==0)
					{
						x1[bcount]=x+3;
					}
					y1[bcount]=y;
					bullet[bcount]=1;
					nbullet-=1;
				
				}
			}
			fflush(stdin);
		}
		
		
		
//Movement
		if (move==1)
		{
			if(x<74)
			{
				erase_ship(x,y);
				draw_ship(++x,y);
			}
			else
			{
				move=0;
			}
		}
		else if (move == -1)
		{
			if(x>0)
			{
				erase_ship(x,y);
				draw_ship(--x,y);
			}
			else
			{
				move=0;
			}
		}
		else if (move==0)
		{
			draw_ship(x,y);
		}

//Bullet shoot
		for(i=0;i<=4;i++)
		{
			if(bullet[i] == 1)
			{
				bullet_delete(x1[i],y1[i]);
				bullet_draw(x1[i],--y1[i]);
				if(y1[i]==0)
				{
					bullet_delete(x1[i],y1[i]);
					bullet[i]=0;
					nbullet+=1;
				}
				else if(cursor(x1[i],y1[i]-1)=='*')
				{
					bullet_delete(x1[i],y1[i]);
					bullet_draw(x1[i],y1[i]-1);
					Sleep(20);
					bullet_delete(x1[i],y1[i]-1);
					bullet[i]=0;
					nbullet+=1;
					sc+=1;
					xe=rand()%60+10;
					ye=rand()%5+1;
					gotoxy(xe,ye);
					setcolor(7,0);
					printf("*");
				}					
			}
		}	
				
	score(sc);
	Sleep(100);
		
///////
	} while (ch != 'x');
	setcolor(7,0);
	return 0;
}
