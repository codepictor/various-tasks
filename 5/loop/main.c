#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Please, specify a path to a directory as an argument\n");
        return 0;
    }

    DIR* dir = opendir(argv[1]);
    if (!dir)
    {
        perror("Can't open the specified directory");
        return 0;
    }

    struct dirent* dp = NULL;
    while ((dp = readdir(dir)) != NULL)
    {
        printf("%s\n", dp->d_name);
    }

    closedir(dir);
    return 0;
}

