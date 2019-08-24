#include <windows.h>
#include <MMSystem.h>

#include "board.h"
#include "keyboard.h"
#include "screen.h"
#include "setting.h"
#include "intro.h"

int sizey = 30;
int sizex = 15;

char player = 'A';
char playerLaser = '|';
char enemy = 'M';
char enemyShielded = 'T';
char enemyLaser = 186;
char explosion = 177;    

int laserReady = 1;

int direction = LEFT;								//setup huong di chuyen cua enemy ban dau sang ben trai

int initboard(int sizey, int sizex, char world[][sizex])
{
	int x, y;
	int totalEnemies = 0;

	for (x = 0; x < sizex; x++) 
	{
        for (y = 0; y < sizey; y++) 
		{
            if ((y + 1)%2 == 0 && y < 7 && x > 4
            && x < sizex - 5 && x%2 == 0) 
			{
                world[y][x] = enemy;
                totalEnemies++;
            }
            else if ((y + 1)%2 == 0 && y >= 7 && y < 9 && x > 4
            && x < sizex - 5 && x%2 == 0)
			{
                world[y][x] = enemyShielded;
                totalEnemies += 2;
            }
            else 
			{
                world[y][x] = ' ';
            }
        }
    }
    
    world[sizey - 1][sizex/2] = player;
    return totalEnemies;
}

int rules(char world[][sizex], int victory)
{
	int x, t = 0;		//su dung bien t de kiem tra con player o tren board hay khong
	
	for(x = 0; x < sizex; x++)
	{
		if(world[sizey - 1][x] != player)
		{
			t++;
		}
	}
	
	if(t == sizex)
	{
		victory = 0;
	}
	
	for (x = 0; x < sizex; x++) 
	{
		//neu enemy cham vach nguoi choi thi thua
        if (world[sizey - 1][x] == enemy || world[sizey - 1][x] == enemyShielded) 
		{ 
            victory = 0;
        }
    }
    
	return victory;
}

int setupEnemyLaser(char world[][sizex], long i, int currentEnemies, int score)
{
	int y, x, yi;
	int enemyReady = 0;
	laserReady++;//
	for (x = 0; x < sizex; x++) 
	{
        for (y = sizey - 1; y >= 0; y--)
		{
            if (world[y][x] == enemyLaser
            && (world[y + 1][x] != enemy & world[y + 1][x] != enemyShielded))		//neu enemyLaser khong co enemy o phia truoc thi di chuyen enemyLaser xuong 1 hang
			{
	            world[y + 1][x] = enemyLaser;
	            world[y][x] = ' ';
            }
            else if (world[y][x] == enemyLaser
            && (world[y + 1][x] == enemy | world[y + 1][x] == enemyShielded))		//neu enemyLaser co enemy o phia truoc thi xoa enemyLaser
			{
                world[y][x] = ' ';
            }
        }
    }
    
    for (x = 0; x < sizex; x++) 
	{
        for (y = 0; y < sizey; y++) 
		{
			//su dung bien i de setup thoi gian ra enemyLaser cu moi lan i%3 == 0 thi cho ra enemyLaser
			
			//neu tai vi tri world[x][y] la dia bay va phia truoc khong co enemyLaser thi cho ra 1 enemyLaser
            if ((i%3) == 0 && (world[y][x] == enemyShielded	
            	| world[y][x] == enemy) && (rand()%15) > 8 		//rand()%15 > 13 de giam tan suat cua enemyLaser muon tang tan suat thi de rand()%10 > 8
            		&& world[y + 1][x] != playerLaser) 
			{
//                for (yi = y + 1; yi < sizey; yi++) 			//duyet tu vi tri co dia bay xuong tung hang 
//				{
//                    if (world[yi][x] == enemy | world[yi][x] == enemyShielded) 		//neu co dia bay khac o phia truoc thi khong cho ra enemyLaser
//					{
//                        enemyReady = 0;
//                        break;
//                    }
                    enemyReady = 1;							
//                }
                if (enemyReady) 							//neu khong thi cho ra enemyLaser
				{
                    world[y + 1][x] = enemyLaser;
                }
            }
            
		    //neu playerLaser ban trung enemy
		    if (world[y][x] == playerLaser && world[y - 1][x] == enemy) 		
			{
		        world[y][x] = ' ';											//xoa playerLaser	
		        world[y - 1][x] = explosion;								//cho no enemy
		        score += 50;
		    }
		    
		    //neu playerLaser nam ben phai enemy va enemy di sang trai
		    else if(world[y][x] == playerLaser && world[y][x + 1] == enemy && direction == LEFT)
		    {
		    	world[y][x] = ' ';										//xoa playerLaser	
		        world[y][x + 1] = explosion;								//cho no enemy
		        score += 50;
			}
			//neu playerLaser nam ben trai enemy va enemy di sang phai
			else if(world[y][x] == playerLaser && world[y][x - 1] == enemy && direction == RIGHT)
			{
				world[y][x] = ' ';										//xoa playerLaser	
		        world[y][x - 1] = explosion;								//cho no enemy
		        score += 50;
			}
			//neu playerLaser nam cheo ben phai enemy va enemy di sang trai
			else if(world[y][x] == playerLaser && world[y - 1][x + 1] == enemy && direction == LEFT)
			{
				world[y][x] = ' ';										//xoa playerLaser	
		        world[y - 1][x + 1] = explosion;								//cho no enemy
		        score += 50;
			}
			//neu playerLaser nam cheo ben trai enemy va enemy di sang phai
			else if(world[y][x] == playerLaser && world[y - 1][x - 1] == enemy && direction == RIGHT)
			{
				world[y][x] = ' ';										//xoa playerLaser	
		        world[y - 1][x - 1] = explosion;								//cho no enemy
		        score += 50;
			}
		    else if (world[y][x] == playerLaser && world[y - 1][x] == enemyShielded) 
			{
		        world[y][x] = ' ';
		        world[y - 1][x] = enemy;
		        score += 50;
		    }
		    
		    //neu playerLaser nam ben phai enemyShielded va enemyshielded di sang trai
		    else if(world[y][x] == playerLaser && world[y][x + 1] == enemyShielded && direction == LEFT)
		  
		    {
		    	world[y][x] = ' ';
		        world[y][x + 1] = enemy;
		        score += 50;
			}
			
			//neu playerLaser nam ben trai enemyShielded va enemyshielded di sang phai
			else if(world[y][x] == playerLaser && world[y][x - 1] == enemyShielded && direction == RIGHT)
			{
				world[y][x] = ' ';
		        world[y][x - 1] = enemy;
		        score += 50;
			}
			//neu playerLaser nam cheo ben phai enemy va enemyShielded di sang trai
			else if(world[y][x] == playerLaser && world[y - 1][x + 1] == enemyShielded && direction == LEFT)
			{
				world[y][x] = ' ';
		        world[y - 1][x + 1] = enemy;
		        score += 50;
			}
			//neu playerLaser nam cheo ben trai enemy va enemyShielded di sang phai
			else if(world[y][x] == playerLaser && world[y - 1][x - 1] == enemyShielded && direction == RIGHT)
			{
				world[y][x] = ' ';
		        world[y - 1][x - 1] = enemy;
		        score += 50;
			}
		    else if (world[y][x] == playerLaser		//neu enemyLaser o tren playerLaser thi xoa ki tu playerLaser
		    && world[y - 1][x] == enemyLaser) 
			{
		        world[y][x] = ' ';
		    }
		    
		    else if (world[y][x] == explosion) 
			{
		        world[y][x] = ' ';
		    }
		    
			else if (world[y][x] == playerLaser && world[y - 1][x] != enemyLaser)
			{
	            world[y][x] = ' ';
	            world[y - 1][x] = playerLaser;
		    }   
        }
    }
    
    return score;
}

void updateBoard(char world[][sizex], long i, int enemySpeed, int drop, int victory)
{
	int y, x;
	
	for (y = 0; y < sizey; y++) 			//duyet 2 bien trai va phai
	{
	    if (world[y][0] == enemy) 				
		{
	        direction = RIGHT;					//neu enemy cham bien trai thi di chuyen enemy sang phai
	        drop = 1;
	        break;
	    }
	    
	    if (world[y][sizex - 1] == enemy)		//neu enemy cham bien phai thi di chuyen enemy sang trai
		{
	        direction = LEFT; 
	        drop = 1;
	        break;
	    }
	}
	
	if (i%enemySpeed == 0) 			//su dung bien i de dieu chinh toc do cua enemy, neu enemySpeed cang nho thi toc do cang nhanh
	{
	    if (direction == LEFT) 			//direction ban dau = left 
		{
	        for (x = 0; x < sizex - 1; x++) 
			{
	            for (y = 0; y < sizey; y++) 
				{
					//neu drop = 1 va enemy o vi tri bien phai thi di chuyen enemy xuong va di qua trai
	                if (drop && (world[y - 1][x + 1] == enemy						//drop ban dau = 0
	                    || world[y - 1][x + 1] == enemyShielded))	
					{
                    	world[y][x] = world[y - 1][x + 1];
                   		world[y - 1][x + 1] = ' ';
                	}
	                else if (!drop && (world[y][x + 1] == enemy		//drop = 0 thi di chuyen enemy qua trai
	                    || world[y][x + 1] == enemyShielded)) 
					{
                    	world[y][x] = world[y][x + 1];
                    	world[y][x + 1] = ' ';
                	}
	            }
	        }
	    }
	    
	    else 
		{
	        for (x = sizex - 1; x > 0; x--) 
			{
	            for (y = 0; y < sizey; y++) 
				{
					//neu drop = 1 va enemy o vi tri bien trai thi di chuyen enemy xuong va di qua phai
	                if (drop && (world[y - 1][x - 1] == enemy		
	                    || world[y - 1][x - 1] == enemyShielded)) 
					{
                	    world[y][x] = world[y - 1][x - 1];
                    	world[y - 1][x - 1] = ' ';
              		}
	                else if (!drop && (world[y][x - 1] == enemy		//neu drop = 0 thi di chuyen enemy qua phai
	                    || world[y][x - 1] == enemyShielded)) 
					{
                    	world[y][x] = world[y][x - 1];
                    	world[y][x - 1] = ' ';
                	}
	            }
	        }
	    }   
	}
}

void playerMovement(char world[][sizex], int victory)
{
	int keyPress;
	int y, x;
	if(keypressed())
	{
	    keyPress = getkey();
	}
	
	else								//neu khong nhan gi thi cho keyPress = ' ' de tranh lap lai di chuyen 
	{	
	    keyPress = ' ';											
	}
	
	if (keyPress == KEY_LEFT) 										//di chuyen player sang trai neu nhan LEFT
	{
	    for (x = 0; x < sizex; x = x + 1) 
		{
	        if (world[sizey - 1][x + 1] == player) 
			{
				if(world[sizey - 1][x] == enemyLaser)
				{
					victory = 0;
				}
				
				else
				{
					world[sizey - 1][x] = player;
	            	world[sizey - 1][x + 1] = ' ';
				}
	            
	        }
	    }
	}
	
	if (keyPress == KEY_RIGHT) 										//di chuyen player sang ben phai neu nhan RIGHT
	{
	    for (x = sizex - 1; x > 0; x = x - 1) 
		{
	        if ( world[sizey - 1][x - 1] == player)
			{
				if(world[sizey - 1][x] == enemyLaser)
				{
					victory = 0;
				}
				else
				{
					world[sizey - 1][x] = player;
	           		world[sizey - 1][x - 1] = ' ';
				}
	            
	        }
	    }
	}
	
	if (keyPress == KEY_UP && laserReady > 10) 						//ban ra playerLaser neu nhan UP
	{			
		//laserReady dung de dan cach dan, khong cho dan ban lien tuc
	    for (x = 0; x < sizex; x++) 							
		{
	        if (world[sizey - 1][x] == player) 
			{
	            world[sizey - 2][x] = playerLaser;
	            laserReady = 0;
	        }
	    }
	}
}

int countEnemies(int sizey, int sizex, char world[][sizex])
{
	int count = 0, y, x;
	for(x = 0; x < sizex; x++)
	{
		for(y = 0; y < sizey; y++)
		{
			if(world[y][x] == enemy)
			{
				count++;
			}
			if(world[y][x] == enemyShielded)
			{
				count += 2;
			}
		}
	}
	
	return count;
}

void game(int level, int victory, int score)
{
	long i = 0;
	
	//setup board
	char world[sizey][sizex];
	int totalEnemies = initboard(sizey, sizex, world);
    int currentEnemies = totalEnemies;
    
	while(currentEnemies > 0 && victory)
	{
		hidecursorscr();
        int drop = 0;								//setup mac dinh huong di chuyen cua enemy KHONG xuong hang
        
        int enemySpeed;
		enemySpeed = 1 + 10 * currentEnemies/totalEnemies;
    	//laserReady ban dau = 1

        /*display world*/
		prtscr(score, level, sizey, sizex, world);
		
		/*setup enemyLaser*/
		score = setupEnemyLaser(world, i, currentEnemies, score);
		
        /*update enemy direction and update board*/
        updateBoard(world, i, enemySpeed, drop, victory);
		
		/*count enemies on board*/
		currentEnemies = countEnemies(sizey, sizex, world);
		
        /*control player*/
        playerMovement(world, victory);
        
        i++;      
		Sleep(10);  
        victory = rules(world, victory);
    }
    
    if (victory != 0) 
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 + level);
		level++;
		sizex += 5;
		i = 0;
        game(level, victory, score);
    }
    
    else 
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        printf("\n \n \n \n \n \n               Ban da thua.");
        Sleep(1000);
        printf("\n \n \n \n \n \n               Game over.");
        Sleep(1000);
        highScore(score, "high score.txt");
        Sleep(1000);
        printf("\n \n               Final Score: %d", score);
        getch();
    }
}

