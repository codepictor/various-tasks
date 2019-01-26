#include <stdio.h>
#include <assert.h>

#include "forest.h"



int main ()
{
    struct Cell curr[xSize * ySize] = {};
    struct Cell next[xSize * ySize] = {};
    InitArray(curr);
    CopyArray(curr, next);

    int i = 0;
    char h = 0;
    while (1)
    {
        //h++;
        //if (h == 5)
        //{
            //system("clear");
            PrintArray(curr);
        //	h = 0;
        //}
        //sleep (1);
        //for (i = 0; i < 10000000; i++);
        scanf("%c", &h);
        ProcessForest(curr, next);
    }

    return 0;
}

