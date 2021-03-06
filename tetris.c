#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "event.h"

int nSpace[24][12];
int nBlock[7][4][4][4] = {0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0,
	0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,
	0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,0,
	0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,

	0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,
	0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,
	0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,
	0,0,0,0,0,2,2,0,0,2,2,0,0,0,0,0,

	0,0,0,0,0,2,0,0,0,2,2,2,0,0,0,0,
	0,0,0,0,0,2,2,0,0,2,0,0,0,2,0,0,
	0,0,0,0,2,2,2,0,0,0,2,0,0,0,0,0,
	0,0,2,0,0,0,2,0,0,2,2,0,0,0,0,0,

	0,0,0,0,0,0,2,0,2,2,2,0,0,0,0,0,
	0,2,0,0,0,2,0,0,0,2,2,0,0,0,0,0,
	0,0,0,0,0,2,2,2,0,2,0,0,0,0,0,0,
	0,0,0,0,0,2,2,0,0,0,2,0,0,0,2,0,

	0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0,
	0,2,0,0,0,2,2,0,0,0,2,0,0,0,0,0,
	0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0,
        0,2,0,0,0,2,2,0,0,0,2,0,0,0,0,0,

	0,2,0,0,0,2,2,0,0,2,0,0,0,0,0,0,
	0,0,0,0,0,2,2,2,0,0,2,0,0,0,0,0,
	0,0,2,0,0,2,2,0,0,0,2,0,0,0,0,0,
	0,0,0,0,0,0,2,0,0,2,2,2,0,0,0,0,

	0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0,
	0,0,2,0,0,2,2,0,0,2,0,0,0,0,0,0,
	0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0,
        0,0,2,0,0,2,2,0,0,2,0,0,0,0,0,0};
int nX, nY;
int nBlockNo = -1;
time_t tStart, tEnd;
int nFalling;
int nBlockRot;
int nGameOver = 0;

void initSpace()
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			nSpace[i][j] = 0;
		}
	}
	
	for (int i = 0; i < 24; i++)
	{
		nSpace[i][0] = 1;
		nSpace[i][11] = 1;
	}
	
	for (int j = 1; j < 11; j++)
	{
		nSpace[23][j] = 1;
	}
}

void drawAll()
{
	system("clear");
	for (int i = 3; i < 24; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (nSpace[i][j] == 2)
				printf("%s", "■ ");
			else if (nSpace[i][j] == 1)
				printf("%s", "□ ");
			else if (nSpace[i][j] == 0)
				printf("%s", "  ");
			else
			{
				printf("%2d", nSpace[i][j]);
			}
		}
		printf("\n");
	}
	printf("%d, %d \n", nX, nY);
}

void addBlock()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			nSpace[i + nX][j + nY] += nBlock[nBlockNo][nBlockRot][i][j];
		}
	}
}

void delBlock()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			nSpace[i + nX][j + nY] -= nBlock[nBlockNo][nBlockRot][i][j];
		}
	}
}

int isLineFull() //return full line idx or 0
{
	int full = 1;
	for (int i = 22; i > 4; i--)
	{
		for (int j = 1; j < 11; j++)
		{
			if (nSpace[i][j] == 0)
				full = 0;
		}
		if (full)
			return i;
		full = 1;
	}
						
}

void delFullLine()
{

	delBlock();

	int full = isLineFull();
	while (full)
	{
		//delete full-th line
		for (int i = full; i > 3; i--)
		{
			for (int j = 1; j < 11; j++)
			{
				nSpace[i][j] = nSpace[i-1][j];
			}
		}
		full = isLineFull();
	}


	addBlock();
	drawAll();
}
int isCrushing()
{
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                       if (nSpace[i + nX][j + nY] > 2)
                               return 1;
                }
        }

        return 0;
}


void setNewBlock()
{
	srand(time(NULL));
	nBlockNo = rand() % 7;
 		
       
	nBlockRot = 0;

        int sum = 0;
        for (int i = 3; i >= 0; i--)
        {
                for (int j = 0; j < 4; j++)
                {
                        sum += nBlock[nBlockNo][nBlockRot][i][j];
                }
                if (sum > 0)
                {
                        nX = 3 - i;
			nY = 4;
                	break;
		}
        }
        nFalling = 1;
        addBlock();
	if (isCrushing())
	{
		delBlock();
		nGameOver = 1;
	}
	drawAll();
	tStart = time(NULL);
}

void moveToLeft()
{
	delBlock();
	nY--;
	addBlock();
	if (isCrushing())
	{
		delBlock();
		nY++;
		nBlockRot--;
		if (nBlockRot < 0)
			nBlockRot = 4;
		addBlock();
	}
}

void moveToRight()
{
        delBlock();
        nY++;
        addBlock();
        if (isCrushing())
        {
                delBlock();
                nY--;
                nBlockRot--;
                if (nBlockRot < 0)
                        nBlockRot = 4;
                addBlock();
        }
}

void revertRot()
{
	delBlock();
	nBlockRot--;
	if (nBlockRot < 0)
		nBlockRot = 4;
	addBlock();
}

void avoidCrush()
{
	switch (nBlockNo)
	{	
		case 0:
			if (nBlockRot == 0 || nBlockRot == 2)
				revertRot();
			else // 1, 3
			{
				delBlock();
				nY++;
				addBlock();
				if (isCrushing())
				{
					delBlock();
					nY -= 3;
					addBlock();
					if (isCrushing())
					{
						delBlock();
						nY += 2;
						nBlockRot--;
						if (nBlockRot < 0)
							nBlockRot = 4;
						addBlock();
					}
				}
			}
			break;
		case 2:
			if (nBlockRot == 0)
				moveToLeft();
			else if (nBlockRot == 1)
				revertRot();
			else if (nBlockRot == 2)
				moveToRight();
			else 
				;
			break;
		case 3:
			if (nBlockRot == 0)
				moveToRight();
			else if (nBlockRot == 2)
				moveToLeft();
			else if (nBlockRot == 3)
				revertRot();
			else
				;
			break;
		case 4:
			if (nBlockRot == 0 || nBlockRot == 2)
				moveToRight();
			break;
		case 5:
			if (nBlockRot == 1 || nBlockRot == 3)
				moveToLeft();
			break;
		case 6:
		       	if (nBlockRot == 0 || nBlockRot == 2)
                                moveToRight();
                        break;
	}

}


void dropBlock()
{
	tEnd = time(NULL);
	if (tEnd - tStart >= 1)
	{
		delBlock();
		nX++;
		addBlock();
		if(isCrushing())
		{
			delBlock();
			nX--;
			addBlock();
			nFalling = 0;
		}
		drawAll();
		tStart = time(NULL);
	}
}

void getInput()
{
	init_keyboard();
	if (_kbhit())
	{
		int ch1 = _getch();
		if (ch1 == 27)
		{
			int ch2 = _getch();
			int ch3 = _getch();
			delBlock();
			switch (ch3)
			{
				case 68:
					nY--;
					break;
				case 67:
					nY++;
					break;
				case 66:
					nX++;
					break;
			}
			addBlock();
			if (isCrushing())
			{
				delBlock();
				switch (ch3)
				{
					case 68:
						nY++;
						break;
					case 67:
						nY--;
						break;
					case 66:
						nX--;
						nFalling = 0;
						break;
				}
				addBlock();
			}
			drawAll();
			tStart = time(NULL);
		}
		else if (ch1 == 32)
		{
			delBlock();
			nBlockRot++;
			if (nBlockRot > 3)
				nBlockRot = 0;
			addBlock();
			if (isCrushing())
			{
				avoidCrush();
			}
			drawAll();
		}
	}
	close_keyboard();
}

