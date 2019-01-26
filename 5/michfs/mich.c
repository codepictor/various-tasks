#include <linux/buffer_head.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/mount.h>
#include <linux/device.h>


#define FILE_SIZE            4096  // size of a single file
#define MAX_FILES_N          100   // max number of files in the michfs
#define MICHFS_MAX_NAME_LEN  255   // max length of a file's name in the michfs


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Artem");
MODULE_DESCRIPTION("michfs - a simple file systen");
MODULE_VERSION("0.1");



struct michfs_file
{
    char name[MICHFS_MAX_NAME_LEN + 1];
    char file[FILE_SIZE];
    struct inode* inode;
};


struct michfs
{
    struct michfs_file storage[MAX_FILES_N];
    int files_count;
};


static struct michfs michfs = {};
char tmp_buffer[FILE_SIZE] = {};


struct inode* michfs_make_inode(struct super_block* sb,
                                const struct inode* dir, umode_t mode);


/*
 * Open a file.  All we have to do here is to copy over a
 * copy of the counter pointer so it's easier to get at.
 */
/*static int michfs_open_file(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "!!! Opening file [%s] (inode = %lu)\n",
           filp->f_path.dentry->d_iname, inode->i_ino);
    filp->private_data = inode->i_private;
    return 0;
}*/



static ssize_t michfs_read_file(struct file *filp, char *buf,
                                size_t count, loff_t *offset)
{
    int i = 0;
    const char* file_name = filp->f_path.dentry->d_iname;
    printk(KERN_INFO "!!! read_file [%s] \n", file_name);

    for (i = 0; i < michfs.files_count; i++)
    {
        if (!strcmp(file_name, michfs.storage[i].name))
        {
            if (*offset + count >= FILE_SIZE)
            {
                count = FILE_SIZE - *offset;
            }
            if (count <= 0)
            {
                return 0;
            }

            if (copy_to_user(buf, michfs.storage[i].file + *offset, count))
            {
                return -EFAULT;
            }

            *offset += count;
            return count;
        }
    }

    return 0;
}



static ssize_t michfs_write_file(struct file *filp, const char *buf,
                                 size_t count, loff_t *offset)
{
    //char tmp_buffer[TMPSIZE] = {};
    int i = 0;
    const char* const file_name = filp->f_path.dentry->d_iname;
    printk(KERN_INFO "!!! write_file to [%s]\n", file_name);

    // Only write from the beginning.
    if (*offset != 0)
    {
        return -EINVAL;
    }

    if (count >= FILE_SIZE)
    {
        count = FILE_SIZE;
    }

    memset(tmp_buffer, 0, FILE_SIZE);
    if (copy_from_user(tmp_buffer, buf, count))
    {
        return -EFAULT;
    }

    for (i = 0; i < michfs.files_count; i++)
    {
        if (!strcmp(file_name, michfs.storage[i].name))
        {
            //printk(KERN_INFO "$$$ Writing {%s} to [%s]\n",
            //       tmp_buffer, file_name);
            memcpy(michfs.storage[i].file, tmp_buffer, count);
            return count;
        }
    }

    return -ENOENT;  // No such file
}



/*static int michfs_iterate(struct file *filp, struct dir_context *ctx)
{
    int i = 0;
    struct inode *inode = filp->f_path.dentry->d_inode;
    //struct buffer_head *bh = NULL;
    //struct super_block *sb = inode->i_sb;

    //printk(KERN_INFO "michfs DEBUG: !!! ls (file_inode = %lu) (root_inode = %lu)\n",
    //       michfs.storage[i].inode->i_ino, inode->i_ino);

    for (i = 0; i < michfs.files_count; i++)
    {
        dir_emit(ctx, michfs.storage[i].name, strlen(michfs.storage[i].name),
                 inode->i_ino, DT_UNKNOWN);
                 //record->inode_no, DT_UNKNOWN);
        ctx->pos += sizeof(struct dentry);

        printk(KERN_INFO "!!! ls: i = %d  [%s]\n", i, michfs.storage[i].name);
    }

    return 0;
}
*/


/*const struct file_operations michfs_dir_operations = {
    .owner = THIS_MODULE,
    .iterate = michfs_iterate,
};*/



const struct file_operations michfs_file_operations = {
//    .open = michfs_open_file,
    .read = michfs_read_file,
    .write = michfs_write_file,
};


//const struct inode_operations michfs_file_inode_operations = {};



static int michfs_create(struct inode* dir, struct dentry* dentry,
                         umode_t mode, bool excl)
{
    const char* const file_name = dentry->d_iname;

    struct inode* inode = michfs_make_inode(dir->i_sb, dir, mode);
    int error = -ENOSPC;
    printk(KERN_INFO "DEBUG: creating file [%s]\n", dentry->d_iname);

    if (inode)
    {
        d_instantiate(dentry, inode);
        dget(dentry);	// Extra count - pin the dentry in core
        error = 0;
        dir->i_mtime = dir->i_ctime = current_time(dir);
    }

    if (michfs.files_count >= MAX_FILES_N)
    {
        return -ENOSPC;
    }

    if (strlen(file_name) > MICHFS_MAX_NAME_LEN)
    {
        return -ENOSPC;
    }
    strcpy(michfs.storage[michfs.files_count].name, file_name);

    michfs.storage[michfs.files_count].inode = inode;

    michfs.files_count++;
    printk(KERN_INFO "DEBUG: created file [%s] with inode = %lu\n",
           file_name, inode->i_ino);
    return error;
}



/*struct dentry* michfs_lookup(struct inode *parent_inode,
                             struct dentry *child_dentry, unsigned int flags)
{
    // The lookup function is used for dentry association.
    struct inode* inode = NULL;
    int i = 0;
    printk(KERN_INFO "!!! lookup [%s] (parent_inode = %lu)\n",
           child_dentry->d_iname, parent_inode->i_ino);

    for (i = 0; i < michfs.files_count; i++)
    {
        if (!strcmp(michfs.storage[i].name, child_dentry->d_iname))
        {
            return child_dentry;
        }
    }

    inode = michfs_make_inode(
                parent_inode->i_sb, parent_inode, S_IFREG | 0777, 0);
    d_add(child_dentry, inode);

    return NULL;
}*/


static const struct inode_operations michfs_dir_inode_operations = {
    .create = michfs_create,
    .lookup = simple_lookup,
};





/* A magic number that uniquely identifies our filesystem type */
#define MICHFS_MAGIC 0x13051996



/* This function creates, configures and returns an inode,
 * for the asked file (or) directory (differentiated by the mode param),
 * under the directory specified by the dir param
 * on the device dev, managed by the superblock sb param) */
struct inode* michfs_make_inode(struct super_block* sb,
                                const struct inode* dir, umode_t mode)
{
    struct inode* inode = new_inode(sb);

    if (inode)
    {
        inode->i_ino = get_next_ino();
        inode_init_owner(inode, dir, mode);
        inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);

        switch (mode & S_IFMT)
        {
            case S_IFDIR:
                inode->i_op = &michfs_dir_inode_operations;
                //inode->i_fop = &michfs_dir_operations;
                inode->i_fop = &simple_dir_operations;

                /* directory inodes start off with i_nlink == 2 (for "." entry) */
                inc_nlink(inode);
                break;

            case S_IFREG:
                //inode->i_op = &michfs_file_inode_operations;
                inode->i_fop = &michfs_file_operations;
                break;

            case S_IFLNK:
            default:
                printk(KERN_ERR
                       "michfs can create an inode for only root directory\n");
                return NULL;
                break;
        }
    }

    return inode;
}



/* This function, as the name implies, makes the super_block valid and
 * fills filesystem specific information in the super block */
int michfs_fill_super(struct super_block* sb, void* data, int silent)
{
    struct inode* root_inode = NULL;

    sb->s_magic = MICHFS_MAGIC;
    sb->s_maxbytes		= MAX_LFS_FILESIZE;
    sb->s_blocksize		= PAGE_SIZE;
    sb->s_blocksize_bits	= PAGE_SHIFT;
    //sb->s_time_gran = 1;

    root_inode = michfs_make_inode(sb, NULL, S_IFDIR | 0755);
    //root_inode->i_private = &(sb_disk->root_inode);

    sb->s_root = d_make_root(root_inode);
    if (!sb->s_root)
    {
        return -ENOMEM;
    }

    //printk(KERN_INFO "!!! root inode = %lu\n", root_inode->i_ino);
    return 0;
}



static struct dentry* michfs_mount(struct file_system_type* fs_type, int flags,
                                   const char* dev_name, void* data)
{
    struct dentry* ret = mount_nodev(fs_type, flags,
                                     data, michfs_fill_super);
    if (IS_ERR(ret))
    {
        printk(KERN_ERR "Error mounting michfs");
    }
    else
    {
        printk(KERN_INFO "michfs is succesfully mounted on [%s]\n", dev_name);
    }

    return ret;
}



static void michfs_kill_superblock(struct super_block* sb)
{
    printk(KERN_INFO "michfs superblock is destroyed. Unmount succesful.\n");
}



struct file_system_type michfs_fs_type = {
    .owner = THIS_MODULE,
    .name = "michfs",
    .mount = michfs_mount,
    .kill_sb = michfs_kill_superblock,
    .fs_flags = FS_USERNS_MOUNT,
};



static int michfs_init(void)
{
    int ret = register_filesystem(&michfs_fs_type);
    if (ret == 0)
    {
        printk(KERN_INFO "Sucessfully registered michfs\n");
    }
    else
    {
        printk(KERN_ERR "Failed to register michfs. Error:[%d]", ret);
    }

    return ret;
}


static void michfs_exit(void)
{
    int ret = unregister_filesystem(&michfs_fs_type);

    if (ret == 0)
    {
        printk(KERN_INFO "Sucessfully unregistered michfs\n");
    }
    else
    {
        printk(KERN_ERR "Failed to unregister michfs. Error:[%d]", ret);
    }
}


module_init(michfs_init);
module_exit(michfs_exit);



