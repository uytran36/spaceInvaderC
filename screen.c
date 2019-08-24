#include <stdio.h>
#include <windows.h>

#include "screen.h"

void hidecursorscr()
{
	// an con chay
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 1; cursor.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}


void prtscr(int score, int level, int sizey, int sizex, char world[][sizex])
{
	int y, x;
	XoaManHinh();
	printf("\n\n\n\n");
    printf("		   SCORE:    %d", score);
    printf("\n");
    
    for (y = 0; y < sizey; y++) 
	{
    	printf("		|");
        for (x = 0; x < sizex; x++) 
		{
            printf("%c", world[y][x]);
        }
        printf("|");
        printf("\n");
    }
    
	printf("Level %d", level);
}
