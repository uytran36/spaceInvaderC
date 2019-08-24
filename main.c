#include <time.h>

#include "board.h"

int main()
{
	srand(time(NULL));
	
	intro();
	system("cls");
	
	int level = 1;
	int victory = 1;
	int score = 0;
	
    game(level, victory, score); 
	
	return 0;

}
