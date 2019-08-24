#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>



#include "intro.h"

void intro2()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\tPlay\n\n");
	printf("\t\t\t\t   > How to play <\n\n");
	printf("			Press E to select, S to move down, W to move up\n");
}

void howToPlay()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\n\n\n			Thua ngai!!!, co rat nhieu nguoi ngoai hanh tinh dang tan cong trai dat cua chung ta\n");
	printf("\n				xin nguoi hay dieu khien phi thuyen cua minh de tieu diet chung no.\n");
	printf("\n				 Ngai su dung cac phim mui ten de di chuyen va ban dan.\n");
	printf("\n					Up: ban laser, Left: sang trai, Right: sang phai \n");
	printf("\n			Duoc roi, ngai nhan Q de tro lai man hinh chinh hoac nhan ENTER de bat dau.\n");
	printf("\n\n\n					Chuc ngai may man!!!!!");
}

void mainscreen()
{
	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t\t\t      > Play <\n\n");
	printf("\t\t\t\t     How to play\n\n");
	printf("			Press E to select, S to move down, W to move up\n");
	int t = 0;
	char key = getch();
	if(key == 's')
	{
		intro2();
		key = getch();
		if(key == 'e')
		{
			howToPlay();
			key = getch();
			if(key == 'q')
			{
				mainscreen();
			}
		}
		else
		{
			mainscreen();
		}
	}
	
	else if(key == 'e')
	{
		return;
	}
	
	else
	{
		mainscreen();
	}
}

void intro()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
	printf("\n\n\n\n\n");
	printf("\n\n\n\t\t\tCUOC XAM LANG CUA NGUOI NGOAI HANH TINH\n\n");
	printf("\n\n\n			Nhan phim bat ki de bat dau!!!");
	
	getch();
	mainscreen();
	
}

