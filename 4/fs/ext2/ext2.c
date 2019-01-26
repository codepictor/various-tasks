#pragma pack(push, 1)

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/kernel.h>
#include <linux/msdos_fs.h>
//#include "/usr/src/linux/fs/ext2/ext2.h"
//#include "/usr/src/linux/include/linux/ext2_fs.h"
#include "auxext2.h"
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define OFFSET_TO_SUPERBLOCK 1024
#define SUPERBLOCK_SIZE      1024



const char     ext2_img_path[] = "ext2.img";  // path to the file containing ext2 file system
const uint32_t inode = 12;


void     CheckRetValue     (const int ret_value, const char* const error_description);
void     PrintEntryViaInode(const uint32_t inode, const int ext2_fd);
void     FillInodeInfo     (struct ext2_inode* inode_info, struct ext2_super_block* superblock,
                            const uint32_t inode, const int ext2_fd);

void     PrintRegFile      (struct ext2_inode* inode_info, const uint32_t block_size, const int ext2_fd);
uint32_t PrintRegFileBlock (const uint32_t block_num, const uint32_t block_size, const int i_block_index,
                            const int out_fd, const int ext2_fd,
                            const uint32_t file_size, uint32_t written_bytes);

void     PrintDir          (struct ext2_inode* inode_info, const uint32_t block_size, const int ext2_fd);
void     PrintDirBlock     (const uint32_t block_num, const uint32_t block_size, const int i_block_index,
                            const int ext2_fd);




int main()
{
    char error_desc[200] = {};
    const int ext2_fd = open(ext2_img_path, O_RDONLY);
    sprintf(error_desc, "ERROR. Can't open file '%s' with ext2 file system", ext2_img_path);
    CheckRetValue(ext2_fd < 0, error_desc);

    PrintEntryViaInode(inode, ext2_fd);

    int ret_value = close(ext2_fd);
    sprintf(error_desc, "ERROR. Can't close file '%s' with ext2 file system", ext2_img_path);
    CheckRetValue(ret_value, error_desc);

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



void PrintEntryViaInode(const uint32_t inode, const int ext2_fd)
{
    assert(ext2_fd >= 0);

    struct ext2_super_block superblock = {};
    int ret_value = pread(ext2_fd, &superblock, sizeof(superblock), OFFSET_TO_SUPERBLOCK);
    CheckRetValue(ret_value < 0, "ERROR. Can't read superblock");
    const uint32_t block_size = pow(2, 10 + superblock.s_log_block_size);

    struct ext2_inode inode_info = {};
    FillInodeInfo(&inode_info, &superblock, inode, ext2_fd);

    const uint16_t fifo        = 0x1000;
    const uint16_t char_dev    = 0x2000;
    const uint16_t dir         = 0x4000;
    const uint16_t block_dev   = 0x6000;
    const uint16_t reg_file    = 0x8000;
    const uint16_t sym_link    = 0xa000;
    const uint16_t unix_socket = 0xc000;

    const uint16_t file_mode = __le16_to_cpu(inode_info.i_mode) & 0xf000;
    if (file_mode == reg_file)
    {
        PrintRegFile(&inode_info, block_size, ext2_fd);
    }
    else if (file_mode == dir)
    {
        PrintDir(&inode_info, block_size, ext2_fd);
    }
    else
    {
        printf("The type %u of entry is not implemented.\n", file_mode);
        printf("The program can work with regular files or directories.\n");
    }
}



void FillInodeInfo(struct ext2_inode* inode_info, struct ext2_super_block* superblock,
                   const uint32_t inode, const int ext2_fd)
{
    assert(inode_info && superblock && ext2_fd >= 0);

    if (superblock->s_inodes_count % superblock->s_inodes_per_group)
    {
        printf("inodes_count isn't divided by inodes_per_group\nExiting ...\n");
        exit(1);
    }

    const uint32_t groups_count = superblock->s_inodes_count / superblock->s_inodes_per_group;
    const uint32_t block_size = pow(2, 10 + superblock->s_log_block_size);
    const uint32_t inode_group = (inode - 1) / superblock->s_inodes_per_group;
    const uint32_t inode_index = (inode - 1) % superblock->s_inodes_per_group;

    struct ext2_group_desc inode_group_desc = {};
    int ret_value = pread(ext2_fd, &inode_group_desc, sizeof(inode_group_desc),
                          OFFSET_TO_SUPERBLOCK + SUPERBLOCK_SIZE + inode_group * sizeof(inode_group_desc));
    char error_desc[200] = {};
    sprintf(error_desc, "ERROR. Can't read group descriptor %u", inode_group);
    CheckRetValue(ret_value < 0, error_desc);

    const uint32_t inode_table = __le32_to_cpu(inode_group_desc.bg_inode_table);
    ret_value = pread(ext2_fd, inode_info, sizeof(struct ext2_inode),
                      inode_table * block_size + inode_index * sizeof(struct ext2_inode));
    sprintf(error_desc, "ERROR. Can't read info about inode %u", inode);
    CheckRetValue(ret_value < 0, error_desc);
}



void PrintRegFile(struct ext2_inode* inode_info, const uint32_t block_size, const int ext2_fd)
{
    assert(inode_info && block_size >= 1024 && ext2_fd >= 0);

    int out_fd = open("output.txt", O_WRONLY | O_CREAT, 0666);
    CheckRetValue(out_fd < 0, "ERROR. Can't open output.txt file for writing results");

    const uint32_t file_size = __le32_to_cpu(inode_info->i_size);
    printf("Writing to output.txt (file size = %u) ...\n", file_size);
    int written_bytes = 0;

    uint32_t block_num = 0;
    int ret_value = 0;
    int i = 0;
    for (i = 0; i < EXT2_N_BLOCKS; i++)
    {
        block_num = __le32_to_cpu(inode_info->i_block[i]);
        if (!block_num)
        {
            break;
        }

        written_bytes = PrintRegFileBlock(block_num, block_size, i, out_fd, ext2_fd, file_size, written_bytes);
    }

    ret_value = close(out_fd);
    CheckRetValue(ret_value, "ERROR. Can't close output.txt file");
}



uint32_t PrintRegFileBlock(const uint32_t block_num, const uint32_t block_size, const int i_block_index,
                           const int out_fd, const int ext2_fd,
                           const uint32_t file_size, uint32_t written_bytes)
{
    assert(0 <= i_block_index && i_block_index < EXT2_N_BLOCKS);
    assert(out_fd >= 0 && ext2_fd >= 0);
    assert(written_bytes <= file_size);

    __le32* block_buf = calloc(block_size, sizeof(char));
    assert(block_buf);
    int ret_value = 0;
    char error_desc[200] = {};

    if (i_block_index < EXT2_NDIR_BLOCKS)
    {
        ret_value = pread(ext2_fd, block_buf, block_size, block_num * block_size);
        sprintf(error_desc, "ERROR. Can't read file block (block = %u)", block_num);
        CheckRetValue(ret_value != block_size, error_desc);
        const uint32_t bytes_to_write = (written_bytes + block_size <= file_size) ?
                                         block_size : file_size - written_bytes;
        ret_value = write(out_fd, block_buf, bytes_to_write);
        sprintf(error_desc, "ERROR. Can't write file block (block = %u) to output file", block_num);
        CheckRetValue(ret_value != bytes_to_write, error_desc);
        written_bytes += ret_value;
    }
    else
    {
        ret_value = pread(ext2_fd, block_buf, block_size, block_num * block_size);
        sprintf(error_desc, "ERROR. Can't read indirect file block (block = %u)", block_num);
        CheckRetValue(ret_value < 0, error_desc);

        const uint32_t i_block_count = block_size / sizeof(uint32_t);
        uint32_t i = 0;
        for (i = 0; i < i_block_count; i++)
        {
            written_bytes = PrintRegFileBlock(__le32_to_cpu(block_buf[i]), block_size, i_block_index - 1,
                                              out_fd, ext2_fd, file_size, written_bytes);
        }
    }

    free(block_buf);
    block_buf = NULL;
    return written_bytes;
}



void PrintDir(struct ext2_inode* inode_info, const uint32_t block_size, const int ext2_fd)
{
    assert(inode_info && block_size >= 1024 && ext2_fd >= 0);

    uint32_t block_num = 0;
    int i = 0;

    for (i = 0; i < EXT2_N_BLOCKS; i++)
    {
        block_num = __le32_to_cpu(inode_info->i_block[i]);
        if (!block_num)
        {
            break;
        }

        PrintDirBlock(block_num, block_size, i, ext2_fd);
    }
}



void PrintDirBlock(const uint32_t block_num, const uint32_t block_size, const int i_block_index,
                   const int ext2_fd)
{
    assert(0 <= i_block_index && i_block_index < EXT2_N_BLOCKS);
    assert(ext2_fd >= 0);

    char file_name[EXT2_NAME_LEN + 1] = {};
    void* buf = calloc(block_size, sizeof(char));
    assert(buf);
    int ret_value = 0;
    char error_desc[200] = {};

    if (i_block_index < EXT2_NDIR_BLOCKS)
    {
        struct ext2_dir_entry_2* dir_entry = buf;
        ret_value = pread(ext2_fd, buf, block_size, block_size * block_num);
        sprintf(error_desc, "ERROR. Can't read dir_entry (block = %u)", block_num);
        CheckRetValue(ret_value < 0, error_desc);
        uint32_t offset_from_start = 0;

        while (dir_entry->inode && offset_from_start < block_size)
        {
            memcpy(file_name, dir_entry->name, dir_entry->name_len);
            file_name[dir_entry->name_len] = 0;
            printf("%6u  %s\n", __le32_to_cpu(dir_entry->inode), file_name);
            dir_entry = (void*)dir_entry + __le16_to_cpu(dir_entry->rec_len);
            offset_from_start += __le16_to_cpu(dir_entry->rec_len);
        }
    }
    else
    {
        __le32* block_buf =  buf;
        ret_value = pread(ext2_fd, block_buf, block_size, block_num * block_size);
        sprintf(error_desc, "ERROR. Can't read indirect dir block (block = %u)", block_num);
        CheckRetValue(ret_value < 0, error_desc);

        const uint32_t ind_blocks_count = block_size / sizeof(uint32_t);
        uint32_t i = 0;
        for (i = 0; i < ind_blocks_count; i++)
        {
            PrintDirBlock(__le32_to_cpu(block_buf[i]), block_size, i_block_index - 1, ext2_fd);
        }
    }

    free(buf);
    buf = NULL;
}


