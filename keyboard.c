#include <conio.h>


#include "keyboard.h"

int keypressed()
{
	return kbhit();
}

int getkey()
{
	int c = getch();
	if(c == 0xE0)
	{
		int code = getch();
		switch(code)
		{
			case 0x4b: return KEY_LEFT;
			case 0x4d: return KEY_RIGHT;
			case 0x50: return KEY_DOWN;
			case 0x48: return KEY_UP;
		}
	}
	
	else
	{
		int code = getch();
		switch(code)
		{
			case 0x20: return KEY_SPACE;
			case 0xd: return KEY_ENTER;
			case 0x1b: return KEY_ESC;
		}
	
	}

	return 0;
}
