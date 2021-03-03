#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int nSpace[24][12];

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

	//**********test***********
	//nSpace[2][5] = 2;
	//nSpace[3][5] = 2;
	//nSpace[4][5] = 2;
	//nSpace[3][6] = 2;
	//*************************	
}

void drawAll()
{
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
}

int main()
{
	initSpace();

	int y = 3;
	while(1)
	{
	system("clear");
	nSpace[y][5] = 2;
	drawAll();
	sleep(1);
	nSpace[y][5] = 0;
	y++;
	}

	return 0;
}
