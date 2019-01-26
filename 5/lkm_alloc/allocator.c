#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define DEVICE_NAME "allocator"        // The device will appear at /dev/allocator
#define CLASS_NAME  "allocator_class"  // The device class
#define MAX_COMMAND_SIZE 256
//#define ALLOC_NUMBER 50000

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Artem");
MODULE_DESCRIPTION("A simple Linux char driver for the allocation memory");
MODULE_VERSION("0.1");

static int  major_number = 0;                   // Stores the device number -- determined automatically
static char command[MAX_COMMAND_SIZE] = {};     // Memory for the string that is passed from userspace
static int  opens_number = 0;                   // Counts the number of times the device is opened
static struct class*  allocator_class  = NULL;  // The device-driver class struct pointer
static struct device* allocator_device = NULL;  // The device-driver device struct pointer

//static void* pointers[ALLOC_NUMBER] = {};
static const char* const message_to_user = "Hello from allocator!";

//static int bytes_number_to_alloc = 0;
//module_param(bytes_number_to_alloc, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
//MODULE_PARM_DESC(bytes_number_to_alloc, "argument for passing to kmalloc and vmalloc");

// The prototype functions for the character driver -- must come before the struct definition
static int dev_open(struct inode* inodep, struct file* filep);
static ssize_t dev_read(struct file* filep, char* buffer, size_t len, loff_t* offset);
static ssize_t dev_write(struct file* filep, const char* buffer, size_t len, loff_t* offset);
static int dev_release(struct inode* inodep, struct file* filep);
 
/** @brief Devices are represented as file structure in the kernel.
 *  The file_operations structure from /linux/fs.h lists the callback functions
 *  that you wish to associated with your file operations
 *  using a C99 syntax structure.
 *  char devices usually implement open, read, write and release calls
 */
static struct file_operations fops =
{
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};


/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file.
 *  The __init macro means that for a built-in driver (not a LKM)
 *  the function is only used at initialization time and that it can be discarded
 *  and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init init_allocator(void)
{
    printk(KERN_INFO "allocator: Initializing the LKM\n");

    // Try to dynamically allocate a major number for the device
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0)
    {
        printk(KERN_ALERT "allocator failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "allocator: registered correctly with major number %d\n",
            major_number);
 
    // Register the device class
    allocator_class = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(allocator_class))  // Check for error and clean up if there is
    {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(allocator_class);  // Correct way to return an error on a pointer
    }
    printk(KERN_INFO "allocator: device class registered correctly\n");
 
    // Register the device driver
    allocator_device = device_create(
            allocator_class,
            NULL,
            MKDEV(major_number, 0),
            NULL,
            DEVICE_NAME);
    if (IS_ERR(allocator_device))  // Clean up if there is an error
    {
        class_destroy(allocator_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(allocator_device);
    }

    printk(KERN_INFO "allocator: device class created correctly\n");
    return 0;
}


/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static.
 *  The __exit macro notifies that if this code is used for a built-in driver
 *  (not a LKM) that this function is not required.
 */
static void __exit exit_allocator(void)
{
    //remove the device
    device_destroy(allocator_class, MKDEV(major_number, 0));

    //unregister the device class
    class_unregister(allocator_class);

    // remove the device class
    class_destroy(allocator_class);

    // unregister the major number
    unregister_chrdev(major_number, DEVICE_NAME);

    printk(KERN_INFO "allocator: Goodbye from the LKM!\n");
}


/** @brief This funstion is called each time the device is opened
 *  This will only increment the numberOpens counter in this case.
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_open(struct inode* inodep, struct file* filep)
{
    opens_number++;
    printk(KERN_INFO "allocator: *** the device has been opened %d time(s) ***\n",
            opens_number);
    return 0;
}


/** @brief This function is called whenever device is being read from user space
 *  i.e. data is being sent from the device to the user.
 *  In this case it uses the copy_to_user() function to
 *  send the string to the user and captures any errors.
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 *  @param buffer The pointer to the buffer to which this function writes the data
 *  @param len The length of the b
 *  @param offset The offset if required
 */
static ssize_t dev_read(struct file* filep, char* buffer,
                        size_t len, loff_t* offset)
{
    // copy_to_user has the format (*to, *from, size) and returns 0 on success
    int error_count = copy_to_user(buffer, message_to_user, strlen(message_to_user));

    if (error_count == 0)
    {
        printk(KERN_INFO "allocator: greeted a userspace program!\n");
        return 0;
    }
    else
    {
        printk(KERN_INFO "allocator: Failed to greet a userspace program\n");
        return -EFAULT;  // Failed -- return a bad address message (i.e. -14)
    }
}


/** @brief This function is used to find a number in a string
 *  @param command a pointer to a string (containing a command)
 */
int get_number_from_command(const char* const command)
{
    int number_begin = 0;
    int number_end = 0;
    int i = 0;
    int number = 0;

    while (!('0' <= command[number_begin] && command[number_begin] <= '9')
            && number_begin < MAX_COMMAND_SIZE)
    {
        number_begin++;
    }

    if (number_begin >= MAX_COMMAND_SIZE)
    {
        return -1;
    }
    number_end = number_begin;

    while ('0' <= command[number_end] && command[number_end] <= '9'
            && number_end < MAX_COMMAND_SIZE)
    {
        number_end++;
    }

    if (number_end - number_begin >= 11)
    {
        return -1;
    }
    for (i = number_begin; i < number_end; i++)
    {
        number = number * 10 + (command[i] - '0');
    }
    return number;
}


/** @brief This function tries to allocate bytes_number_to_alloc bytes
 *  using kmalloc(size_t size, int flags)
 *  @param bytes_number_to_alloc number of bytes required to be allocated
 *  @param flag can be equal to GFP_KERNEL, GFP_ATOMIC, etc.
 *  @return number of allocation fails
 */
int allocate_kmalloc(const int bytes_number_to_alloc, const int flag)
{
    //int i = 0;
    int alloc_fails_number = 0;
    void* ptr = kmalloc(bytes_number_to_alloc, flag);
    if (ptr)  // allocation was successful
    {
        printk(KERN_INFO "allocator: kmalloc allocated %d bytes using %d flag (ptr = %p)\n",
                bytes_number_to_alloc, flag, ptr);
    }
    else  // allocation failed
    {
        printk(KERN_INFO "allocator: kmalloc failed to allocate %d bytes using %d flag\n",
                bytes_number_to_alloc, flag);
        alloc_fails_number++;
    }
    kfree(ptr);

    // perform extremely large number of allocations
    /*printk(KERN_INFO "allocator: starting to perform extremely large number of allocations\n");
    for (i = 0; i < ALLOC_NUMBER; i++)
    {
        pointers[i] = kmalloc(bytes_number_to_alloc, flag);
        if (!pointers[i])
        {
            alloc_fails_number++;
        }
    }
    printk(KERN_INFO "allocator: allocated a lot of memory using kmalloc\n");
    for (i = 0; i < ALLOC_NUMBER; i++)
    {
        kfree(pointers[i]);
    }
    printk(KERN_INFO "allocator: finishing to perform extremely large number of allocations\n");*/

    return alloc_fails_number;
}


/** @brief This function tries to allocate bytes_number_to_alloc bytes
 *  using vmalloc(size_t size)
 *  @param bytes_number_to_alloc number of bytes required to be allocated
 *  @return number of allocation fails
 */
int allocate_vmalloc(const int bytes_number_to_alloc)
{
    //int i = 0;
    int alloc_fails_number = 0;
    void* ptr = vmalloc(bytes_number_to_alloc);
    if (ptr)  // allocation was successful
    {
        printk(KERN_INFO "allocator: vmalloc allocated %d bytes (ptr = %p)\n",
                bytes_number_to_alloc, ptr);
    }
    else  // allocation failed
    {
        printk(KERN_INFO "allocator: vmalloc failed to allocate %d bytes\n",
                bytes_number_to_alloc);
        alloc_fails_number++;
    }
    vfree(ptr);

    return alloc_fails_number;
}


/** @brief This function is called whenever the device is being written to
 *  from user space i.e. data is sent to the device from the user.
 *  The data is copied to the message[] array in this LKM
 *  using the sprintf() function along with the length of the string.
 *  @param filep A pointer to a file object
 *  @param buffer The buffer to that contains the string to write to the device
 *  @param len The length of the array of data that is being passed to buffer
 *  @param offset The offset if required
 */
static ssize_t dev_write(struct file* filep, const char* buffer,
                         size_t len, loff_t* offset)
{
    int bytes_number_to_alloc = 0;
    int kmalloc_kernel_fails_number = 0;
    int kmalloc_atomic_fails_number = 0;
    int vmalloc_fails_number = 0;

    if (len >= MAX_COMMAND_SIZE)
    {
        printk(KERN_INFO "allocator: recieved too long string (len = %zu), ignore it\n", len);
        return 0;
    }

    sprintf(command, "%s", buffer);
    printk(KERN_INFO "allocator: Received [%s] from the user\n", command);
    bytes_number_to_alloc = get_number_from_command(command);
    if (bytes_number_to_alloc < 0)
    {
        printk(KERN_INFO "allocator: Got incorrect number (%d) for allocation",
                bytes_number_to_alloc);
        return len;
    }

    kmalloc_kernel_fails_number += allocate_kmalloc(bytes_number_to_alloc, GFP_KERNEL);
    printk(KERN_INFO "kmalloc(GFP_KERNEL) fails: %d\n", kmalloc_kernel_fails_number);

    kmalloc_atomic_fails_number += allocate_kmalloc(bytes_number_to_alloc, GFP_ATOMIC);
    printk(KERN_INFO "kmalloc(GFP_ATOMIC) fails: %d\n", kmalloc_atomic_fails_number);

    vmalloc_fails_number += allocate_vmalloc(bytes_number_to_alloc);
    printk(KERN_INFO "vmalloc fails: %d\n", vmalloc_fails_number);
    
    return len;
}


/** @brief The device release function that is called
 *  whenever the device is closed/released by the userspace program
 *  @param inodep A pointer to an inode object (defined in linux/fs.h)
 *  @param filep A pointer to a file object (defined in linux/fs.h)
 */
static int dev_release(struct inode* inodep, struct file* filep)
{
    printk(KERN_INFO "allocator: *** the device successfully closed ***\n");
    return 0;
}


/** @brief A module must use the module_init() module_exit() macros from linux/init.h,
 *  which identify the initialization function at insertion time and the cleanup function
 *  (as listed above)
 */
module_init(init_allocator);
module_exit(exit_allocator);

