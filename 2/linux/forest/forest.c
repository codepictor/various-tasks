#include <stdio.h>
#include <assert.h>

#include "forest.h"


//const int xSize = 100;
//const int ySize = 100;

const int startWidth = 50;
const int burnTime = 12;
const int growTime = 2;
const int lightTime = 8;



void ProcessForest(struct Cell* const curr, struct Cell* const next)
{
	assert(curr);
	assert(next);

	int x = 0;
	int y = 0;
	int i = 0;
	int j = 0;
	int burnNeighbours = 0;

	for (y = 0; y < ySize; y++)
	{
		for (x = 0; x < xSize; x++)
		{
			for (j = y - 1; j <= y + 1; j++)
			{
				for (i = x - 1; i <= x + 1; i++)
				{
					if (j < 0 || j >= ySize || i < 0
					    || i >= xSize || i == x && j == y)
					{
						continue;
					}
					else
					{
						if ((curr + j * xSize + i)->type == STATUS_BURN)
						{
							burnNeighbours++;
						}
					}
				}
			}

			OperateCell(curr + y * xSize + x, next + y * xSize + x,
			            burnNeighbours);
			burnNeighbours = 0;
		}
	}

	CopyArray(next, curr);
}



void OperateCell(struct Cell* const currCell,
                 struct Cell* const nextCell, const int burnNeighbours)
{
	assert(currCell);
	assert(nextCell);
	assert(0 <= burnNeighbours && burnNeighbours <= 8);

	if (currCell->elapsedTime > 0)
	{
		switch (currCell->type)
		{
			case STATUS_NORM:
				nextCell->elapsedTime = currCell->elapsedTime - burnNeighbours;
				break;

			case STATUS_BURN:
				nextCell->elapsedTime = currCell->elapsedTime - 1;
				break;

			case STATUS_GROW:
				nextCell->elapsedTime = currCell->elapsedTime - 1;
				break;

			default:
				printf("ERROR. Unknown type '%d' of a cell in OperateCell.\n",
                       currCell->type);
		}
	}
	else
	{
		switch (currCell->type)
		{
			case STATUS_NORM:
				nextCell->type = STATUS_BURN;
				nextCell->elapsedTime = burnTime;
				break;

			case STATUS_BURN:
				nextCell->type = STATUS_GROW;
				nextCell->elapsedTime = growTime;
				break;

			case STATUS_GROW:
				nextCell->type = STATUS_NORM;
				nextCell->elapsedTime = lightTime;
				break;

			default:
				printf("ERROR. Unknown type '%d' of a cell in OperateCell.\n",
				       currCell->type);
		}
	}
}



void InitArray(struct Cell* const array)
{
	assert(array);

	int x = 0;
	int y = 0;
	for (y = 0; y < ySize; y++)
	{
		for (x = 0; x < xSize; x++)
		{
			assert (array + y * xSize + x);

			if (x >= startWidth && x <= xSize - startWidth && y == ySize / 2)
			{
				(array + y * xSize + x)->type = STATUS_BURN;
				(array + y * xSize + x)->elapsedTime = burnTime;
			}
			else
			{
				(array + y * xSize + x)->type = STATUS_NORM;
				(array + y * xSize + x)->elapsedTime = lightTime;

			}
		}
	}
}



void PrintArray(struct Cell* const array)
{
	assert(array);

	int x = 0;
	int y = 0;
	int i = 0;
	char str[xSize * ySize + ySize + 1] = {};

	for (y = 0; y < ySize; y++)
	{
		for (x = 0; x < xSize; x++)
		{
			assert (array + y * xSize + x);

			switch ((array + y * xSize + x)->type)
			{
				case STATUS_NORM:
				    str[i] = '|';
					break;

				case STATUS_BURN:
				    str[i] = '*';
					break;

				case STATUS_GROW:
				    str[i] = ' ';
					break;
				
				default:
				    printf("ERROR. Unknown type of a cell [%d][%d] in PrintArray.\n", x, y);
			}

			i++;
		}

		str[i] = '\n';
		i++;
	}

	str[i] = 0;
	printf("%s", str);
}



void CopyArray(struct Cell* const source, struct Cell* const destination)
{
	assert(source);
	assert(destination);

	int x = 0;
	int y = 0;
	for (y = 0; y < ySize; y++)
	{
		for (x = 0; x < xSize; x++)
		{
			assert(source + y * xSize + x);
			assert(destination + y * xSize + x);

			destination[y * xSize + x] = source[y * xSize + x];
		}
	}
}

