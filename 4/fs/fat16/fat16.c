#pragma pack(push, 1)

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/kernel.h>
#include <linux/msdos_fs.h>
#include <assert.h>
#include <stdint.h>

const char fat_img_path[] = "fat.img";  // path to the file containing fat16 file system


void CheckRetValue       (const int ret_value, const char* const error_description);
int  CheckIsDirEntryEmpty(const char* const dir_entry);
void PrintFileName       (const uint8_t* const file_name, const int is_regular_file);
void PrintFileAttr       (const uint8_t attr);
void PrintFileSize       (const uint32_t file_size);
void PrintFileDate       (const uint16_t time, const uint16_t date);
void PrintClustersNum    (const uint16_t start_cluster, const uint16_t* const fat_table);
void PrintRootFileInfo   (struct msdos_dir_entry* dir_entry, const uint16_t* const fat_table);
void PrintRoot           (const int fat_fd);




int main()
{
    char error_desc[200] = {};

    int fat_fd = open(fat_img_path, O_RDONLY);
    sprintf(error_desc, "ERROR. Can't open the file '%s' with fat file system", fat_img_path);
    CheckRetValue(fat_fd < 0, error_desc);

    PrintRoot(fat_fd);

    int ret_value = close(fat_fd);
    sprintf(error_desc, "ERROR. Can't close the file '%s' with fat file system", fat_img_path);
    CheckRetValue(ret_value, error_desc);

    return 0;
}



void PrintRoot(const int fat_fd)
{
    assert(fat_fd >= 0);

    struct fat_boot_sector superblock = {};
    int ret_value = read(fat_fd, &superblock, sizeof(superblock));
    CheckRetValue(ret_value < 0, "ERROR. Can't read superblock");

    const uint16_t superblock_size = __le16_to_cpu(superblock.reserved);
    const uint16_t fat_size = __le16_to_cpu(superblock.fat_length);
    const uint16_t fats_number = superblock.fats;
    const uint16_t sector_size = superblock.sector_size[1] * 256 + superblock.sector_size[0];
    const uint16_t offset_to_root = (superblock_size + fats_number * fat_size) * sector_size;

    uint16_t* fat_table = calloc(fat_size * sector_size, sizeof(uint16_t));
    assert(fat_table);
    ret_value = pread(fat_fd, fat_table, fat_size * sector_size, superblock_size * sector_size);
    CheckRetValue(ret_value < 0, "ERROR. Can't read file allocation table");
    ret_value = lseek(fat_fd, offset_to_root, SEEK_SET);
    CheckRetValue(ret_value < 0, "ERROR. Can't fseek to root directory listing");

    printf("%6s %11s %20s %10s %5s\n", "attr", "size", "time", "clusters", "name");
    struct msdos_dir_entry dir_entry = {};
    int is_dir_entry_empty = 0;

    while (!is_dir_entry_empty)
    {
        ret_value = read(fat_fd, &dir_entry, sizeof(dir_entry));
        CheckRetValue(ret_value < 0, "ERROR. Can't read dir_entry");

        is_dir_entry_empty = CheckIsDirEntryEmpty((char*)&dir_entry);
        if (!is_dir_entry_empty)
        {
            PrintRootFileInfo(&dir_entry, fat_table);
        }
    }

    free(fat_table);
    fat_table = NULL;
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



int CheckIsDirEntryEmpty(const char* const dir_entry)
{
    assert(dir_entry);

    const int dir_entry_size = sizeof(struct msdos_dir_entry);
    int i = 0;

    for (i = 0; i < dir_entry_size; i++)
    {
        if (dir_entry[i])
        {
            return 0;
        }
    }

    return 1;
}



void PrintFileName(const uint8_t* const file_name, const int is_regular_file)
{
    assert(file_name);

    int space_counter = 0;
    int i = 0;

    for (i = 0; i < MSDOS_NAME; i++)
    {
        if (is_regular_file && i == 7)
        {
            printf(".");
        }
        else if (file_name[i] == 0x20u)
        {
            space_counter++;
            continue;
        }
        else
        {
            printf("%c", file_name[i]);
        }
    }
}



void PrintFileAttr(const uint8_t attr)
{
    const uint8_t read_only_mask = 0x01;
    const uint8_t hidden_mask    = 0x02;
    const uint8_t system_mask    = 0x04;
    const uint8_t vol_label_mask = 0x08;
    const uint8_t directory_mask = 0x10;
    const uint8_t archieve_mask  = 0x20;

    printf("%c%c%c%c%c%c ",
        (attr & read_only_mask) ? 'R' : '-',
        (attr & hidden_mask)    ? 'H' : '-',
        (attr & system_mask)    ? 'S' : '-',
        (attr & vol_label_mask) ? 'V' : '-',
        (attr & directory_mask) ? 'D' : '-',
        (attr & archieve_mask)  ? 'A' : '-'
    );
}



void PrintFileSize(const uint32_t file_size)
{
    printf(" %10u ", file_size);
}



void PrintFileDate(const uint16_t time, const uint16_t date)
{
    const uint16_t hour_mask   = 0xf800;
    const uint16_t minute_mask = 0x07e0;
    const uint16_t second_mask = 0x001f;

    printf(" %02u:%02u:%02u",
        (time & hour_mask) >> 11,
        (time & minute_mask) >> 5,
        (time & second_mask) * 2
    );

    const uint16_t day_mask   = 0x001f;
    const uint16_t month_mask = 0x01e0;
    const uint16_t year_mask  = 0xfe00;

    printf(" %02u.%02u.%4u ",
        (date & day_mask),
        (date & month_mask) >> 5,
        ((date & year_mask) >> 9) + 1980
    );
}



void PrintClustersNum(const uint16_t start_cluster, const uint16_t* const fat_table)
{
    assert(fat_table);

    uint16_t current_cluster = start_cluster;
    int clusters_counter = 0;

    while (current_cluster < 0xfff8u)
    {
        current_cluster = fat_table[current_cluster];
        clusters_counter++;
    }

    printf("  %8d  ", clusters_counter);
}



void PrintRootFileInfo(struct msdos_dir_entry* dir_entry, const uint16_t* const fat_table)
{
    assert(dir_entry && fat_table);

    const uint8_t attr_dir_mask = 0x10;
    const uint8_t delete_label = 0xe5;
    const uint8_t reserved_fields_mask = 0x03;

    if (dir_entry->name[0] == delete_label || (dir_entry->attr & reserved_fields_mask))
    {
        return;
    }

    PrintFileAttr(dir_entry->attr);
    PrintFileSize(__le32_to_cpu(dir_entry->size));
    PrintFileDate(__le16_to_cpu(dir_entry->time), __le16_to_cpu(dir_entry->date));
    PrintClustersNum(__le16_to_cpu(dir_entry->start), fat_table);
    PrintFileName(dir_entry->name, !(dir_entry->attr & attr_dir_mask));
    
    printf("\n");
}


