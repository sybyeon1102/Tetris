#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tetris.h"

int main()
{
        initSpace();
	nFalling = 0;
	nGameOver = 0;

	while(1)
	{	
		if (!nFalling)
		{
			setNewBlock();
			delFullLine();
		}
		if (nGameOver)
			break;
		dropBlock();
		getInput();
	}
	return 0;
}

