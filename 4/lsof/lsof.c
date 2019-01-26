#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

const int BUF_SIZE = 4096;


void CheckRetValue   (const int ret_value, const char* const error_description);
void PrintMappedFiles(const unsigned long long pid);
void PrintOpenFiles  (const unsigned long long pid);
void ListOpenFiles   ();




int main()
{
    ListOpenFiles();

    return 0;
}



void CheckRetValue(const int ret_value, const char* const error_description)
{
    if (ret_value)
    {
        perror(error_description);
        printf("Exiting ...\n");
        exit(1);
    }
}



void PrintMappedFiles(const unsigned long long pid)
{
    char maps_file_path[30] = {};
    sprintf(maps_file_path, "/proc/%llu/maps", pid);
    
    int maps_file_desc = open(maps_file_path, O_RDONLY);
    CheckRetValue(maps_file_desc < 0, "ERROR. Can't open the 'maps' file for reading");

    char* maps_buf = calloc(BUF_SIZE, sizeof(char));
    assert(maps_buf);
    const int stdout_fd = 1;
    int ret_value = 0;

    while (ret_value = read(maps_file_desc, maps_buf, BUF_SIZE))
    {
        CheckRetValue(ret_value < 0, "ERROR. Can't read the 'maps' file");
        ret_value = write(stdout_fd, maps_buf, ret_value);
        CheckRetValue(ret_value < 0, "ERROR. Can't write to stdout");
    }

    free(maps_buf);
    maps_buf = NULL;
    ret_value = close(maps_file_desc);
    CheckRetValue(ret_value, "ERROR. Can't close the 'maps' file");
}



void PrintOpenFiles(const unsigned long long pid)
{
    char fd_dir_path[30] = {};
    sprintf(fd_dir_path, "/proc/%llu/fd", pid);
    DIR* fd_dir = opendir(fd_dir_path);
    char error_desc[50] = {};
    sprintf(error_desc, "ERROR. Can't open /proc/%llu/fd", pid);
    CheckRetValue(!fd_dir, error_desc);

    char* link_buf = calloc(BUF_SIZE, sizeof(char));
    assert(link_buf);
    struct dirent* fd_dir_entry = NULL;

    while ((fd_dir_entry = readdir(fd_dir)) != NULL)
    {
        char link_path[300] = {};
        strcat(link_path, fd_dir_path);
        strcat(link_path, "/");
        strcat(link_path, fd_dir_entry->d_name);

        if (readlink(link_path, link_buf, BUF_SIZE) < 0)
        {
            continue;
        }
        link_buf[BUF_SIZE - 1] = 0;
        printf("%10llu     %s\n", pid, link_buf);
    }

    int ret_value = closedir(fd_dir);
    sprintf(error_desc, "ERROR. Can't close /proc/%llu/fd", pid);
    CheckRetValue(ret_value, error_desc);
}



void ListOpenFiles()
{
    DIR* proc_dir = opendir("/proc");
    CheckRetValue(!proc_dir, "ERROR. Can't open the directory /proc");

    struct dirent* proc_dir_entry = NULL;
    unsigned long long pid = 0;

    while ((proc_dir_entry = readdir(proc_dir)) != NULL)
    {
        pid = strtoull(proc_dir_entry->d_name, NULL, 10);
        if (pid)
        {
            printf("\n--------------------------------------------------\n");
            printf("PID = %llu\n", pid);

            printf("MAPPED FILES:\n");
            PrintMappedFiles(pid);
            printf("OPENED FILES:\n");
            PrintOpenFiles(pid);

            printf("--------------------------------------------------\n");
        }
    }

    int ret_value = closedir(proc_dir);
    CheckRetValue(ret_value, "ERROR. Can't close the directory /proc");
}


