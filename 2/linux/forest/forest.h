#define xSize 100
#define ySize 35


enum TreeStatus
{
	STATUS_NORM = 0,
	STATUS_BURN = 1,
	STATUS_GROW = 2
};


struct Cell
{
	int type;
	int elapsedTime;
};



void InitArray(struct Cell* const array);
void ProcessForest(struct Cell* const curr, struct Cell* const next);
void OperateCell(struct Cell* const currCell, struct Cell* const nextCell,
                 const int burnNeighbours);

void PrintArray(struct Cell* const array);
void CopyArray(struct Cell* const source, struct Cell* const destination);

