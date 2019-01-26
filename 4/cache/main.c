#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int offset = 4 * 1024 * 1024;     // amount of ints
const int dataSize = 16 * 1024;         // amount of ints
const int maxPiecesNum = 32;


static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi = 0, lo = 0;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}


void InitArray(int array[], int pieces)
{
    assert(array);
    assert(pieces > 0);

    const int pieceSize = dataSize / pieces;
    const int bigArraySize = offset * maxPiecesNum;
    int i = 0, j = 0;
    for (i = 0; i < bigArraySize; i++)
    {
        array[i] = -1;
    }

    for (i = 0; i < pieces; i++)
    {
        for (j = 0; j < pieceSize; j++)
        {
            array[i * offset + j] = (i == pieces - 1)? j + 1 : (i + 1) * offset + j;
        }
    }
    array[(i - 1) * offset + j - 1] = 0;
}


int main()
{
    int* array = (int*) calloc(offset * maxPiecesNum, sizeof(int));
    assert(("Can't allocate memory for the array", array));

    FILE* fh = fopen("output.csv", "a");
    assert(("Can't open file for writing the results", fh));

    int pieces = 1;
    for (pieces = 1; pieces <= maxPiecesNum; pieces++)
    {
        InitArray(array, pieces);
        unsigned long long start = 0, end = 0;

        int nextIndex = 1;
        start = rdtsc();
        while (nextIndex)
        {
            nextIndex = array[nextIndex];
        }
        end = rdtsc();

        double averageTime = ((double) (end - start)) / dataSize;
        printf("pieces = %02d, averageTime = %02.2lf\n", pieces, averageTime);
        //fprintf(fh, "%d, \"%.2lf\"\n", pieces, averageTime);
    }
    
    //int i = 0; for (i = 0; i < offset * maxPiecesNum; i++) printf("array[%d] = %d\n", i, array[i]);

    fclose(fh);
    free(array);
    array = NULL;
    return 0;
}

