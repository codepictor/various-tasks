#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>


void CheckRetValue(const int ret_value, const char* const error_description);
void PrintSingleProcessInfo(const unsigned long long pid);
void ProcessStatus();



int main()
{
    ProcessStatus();

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



void PrintSingleProcessInfo(const unsigned long long pid)
{
    char comm_file_path[30] = {};
    sprintf(comm_file_path, "/proc/%llu/comm", pid);
    
    int comm_file_desc = open(comm_file_path, O_RDONLY);
    CheckRetValue(comm_file_desc < 0, "ERROR. Can't open the 'comm' file for reading");

    char comm[50] = {};
    int ret_value = read(comm_file_desc, comm, 50);
    CheckRetValue(ret_value < 0, "ERROR. Can't read the 'comm' file");
    assert(!comm[49]);

    printf("%9llu   %s", pid, comm);

    ret_value = close(comm_file_desc);
    CheckRetValue(ret_value, "ERROR. Can't close the 'comm' file");
}



void ProcessStatus()
{
    DIR* proc_dir = opendir("/proc");
    CheckRetValue(!proc_dir, "Can't open the directory /proc");

    printf("      PID   CMD\n");
    struct dirent* proc_dir_entry = NULL;
    unsigned long long pid = 0;

    while ((proc_dir_entry = readdir(proc_dir)) != NULL)
    {
        pid = strtoull(proc_dir_entry->d_name, NULL, 10);
        if (pid)
        {
            PrintSingleProcessInfo(pid);
        }
    }

    int ret_value = closedir(proc_dir);
    CheckRetValue(ret_value, "ERROR. Can't close the directory /proc");
}


