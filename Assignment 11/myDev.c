#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

// module attributes
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Convert string to uppercase");
MODULE_AUTHOR("CSM20001");

static char msg[1024] = {0};
static int readPos = 0;
static int times = 0;

// file ops for opening a file
static int dev_open(struct inode *inod, struct file *fil)
{
    times++;
    printk(KERN_ALERT "Device opened %d times\n", times);
    return 0;
}

// file ops for reading a file
static ssize_t dev_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
    short count = 0;
    while (len && (msg[readPos] != 0))
    {
        put_user(msg[readPos], buff++);
        count++;
        len--;
        readPos++;
    }
    return count;
}

// file ops for writing to a file
static ssize_t dev_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
    short countB = 0;
    short countM = 0;
    short ch = 0;
    memset(msg, 0, 100);
    readPos = 0;

    // logic for converting a given string into a uppercase string
    while (countB < len)
    {
        ch = buff[countB];
        ch -= 32;
        msg[countM] = ch;
        ch = 0;
        countB++;
        countM++;
    }
    return countM;
}

// file ops for closing a file
static int dev_rls(struct inode *inod, struct file *fil)
{
    printk(KERN_ALERT "Device closed\n");
    return 0;
}

// Linux sys file operations structure
static struct file_operations fops =
    {
        .read = dev_read,
        .open = dev_open,
        .write = dev_write,
        .release = dev_rls,
};

// program execution point
int init_module(void)
{
    int t = register_chrdev(35, "myDev", &fops); // registering the character driver

    if (t < 0)
    {
        printk(KERN_ALERT "Device reg failed\n");
    }
    else
    {
        printk(KERN_ALERT "Device reg success\n");
    }
    return t;
}

void cleanup_module(void)
{
    unregister_chrdev(35, "myDev"); // unregistering the char driver
}
