#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_COMMAND_SIZE 256


int is_number(const char* const str)
{
    const char* symb = str;
    while (*symb)
    {
        if (!('0' <= *symb && *symb <= '9'))
        {
            return 0;
        }
        symb++;
    }
    return 1;
}


int main(int argc, char** argv)
{
    if (argc != 2 || !is_number(argv[1]))
    {
        printf("You should specify exactly one command line argument\n");
        printf("The argument must be a non-negative number\n");
        return 0;
    }
    char command[MAX_COMMAND_SIZE] = {};
    sprintf(command, "alloc(%s)", argv[1]);

    const int fd = open("/dev/allocator", O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open the device...");
        return 0;
    }

    const clock_t start = clock();
    printf("Writing command [%s] to the device...\n", command);
    if (write(fd, command, strlen(command)) < 0)
    {
        perror("Failed to write command to the device.");
        return 0;
    }

    //printf("Press ENTER to read back from the device...\n");
    //getchar();

    printf("Reading from the device...\n");
    char response[256] = {};
    if (read(fd, response, 256) < 0)
    {
        perror("Failed to read a response from the device.");
        return 0;
    }
    printf("Response from the LKM: [%s]\n", response);

    const clock_t end = clock();
    printf("End of the program (time = %lf seconds)\n",
            ((double)(end - start)) / CLOCKS_PER_SEC);

    close(fd);
    return 0;
}

