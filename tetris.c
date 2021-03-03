#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
int nBlockNo;
time_t tStart, tEnd;
int nFalling;
int nBlockRot;

void initSpace()
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			nSpace[i][j] = 0;
		}
	}
	
	for (int i = 3; i < 24; i++)
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
			else
				printf("%s", "  ");
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

void setNewBlock()
{
        nBlockNo = 4;
        nBlockRot = 1;

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
	drawAll();
	tStart = time(NULL);
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






