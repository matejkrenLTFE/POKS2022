/*  hello.c: Creates char device for test read (cat) and write (echo) */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>  /* for put_user */

/*  Prototypes - this would normally go in a .h file */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
int device_ioctl( struct inode *inode, struct file *file, unsigned int ioctl_num, unsigned long ioctl_param); 

#define SUCCESS 0
#define DEVICE_NAME "chardev"  /* Dev name as it appears in /proc/devices   */
#define BUF_LEN 100   /* Max length of the message from the device */

/*  Global variables are declared as static, so are global within the file. */
static int Major;  /* Major number assigned to our device driver */
static int ReadCount=2;
static char msgR[BUF_LEN]="Text from KERNEL\n\0";  /* The msg the device will give when read */
static char msgW[BUF_LEN];  /* The msg buffer for write */

static struct file_operations fops = {
  .read = device_read,
  .write = device_write,
  .open = device_open,
  .release = device_release,
//  .ioctl = device_ioctl
};

/* This function is called when the module is loaded */
static int __init init_modul(void)
{
   Major = register_chrdev(0, DEVICE_NAME, &fops);

  if (Major < 0) {
    printk(KERN_ALERT "Registering char device failed with %d\n", Major);
    return Major;
  }

  printk(KERN_INFO "\nI was assigned major number %d \n", Major);
  printk(KERN_INFO "To talk to the driver, create a dev file with\n");
  printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
  printk(KERN_INFO "Try to cat and echo to the device file.\n");
  printk(KERN_INFO "Remove the device file and module when done.\n");

  return SUCCESS;
}

/* This function is called when the module is unloaded */
static void __exit cleanup_modul(void)
{
  printk(KERN_INFO "Goodbye Major=%d\n", Major);
  unregister_chrdev(Major, DEVICE_NAME);
}

/* Methods */

/* Called when a process tries to open the device file, like * "cat /dev/chardev" */
static int device_open(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "device_open Major=%d\n", Major);
  ReadCount=2;
  return SUCCESS;
}

/* Called when a process closes the device file. */
static int device_release(struct inode *inode, struct file *file)
{
  printk(KERN_INFO "device_release Major=%d\n", Major);
  return SUCCESS;
}

/* Called when a process, which already opened the dev file, attempts to read from it. */
static ssize_t device_read(struct file *filp,  /* see include/linux/fs.h   */
         char *buffer,	/* buffer to fill with data */
         size_t length,	/* length of the buffer     */
         loff_t * offset)
{
  /* Number of bytes actually written to the buffer; return 0 signifying end of file */
  int bytes_read = 0;

  /* Transfering data to user space */ 
  if (ReadCount--)
  {
    bytes_read=strlen(msgR);
    printk(KERN_INFO "device_read. %s", msgR);
    raw_copy_to_user(buffer, msgR, bytes_read);
  }
  else
  {
    bytes_read=0;
    printk(KERN_INFO "device_read bytes_read=0");
  }
  return bytes_read;
}

/* Called when a process writes to dev file: echo "hi" > /dev/chardev  */
static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * offset)
{
  raw_copy_from_user(msgW,buff,len);
  printk(KERN_INFO "device_write. %s\n",msgW);
  msgR = msgW;
  return len;
}

module_init(init_modul);
module_exit(cleanup_modul);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DRIVER_AUTHOR");	/* Who wrote this module? */
MODULE_DESCRIPTION("vaja chardev");	/* What does this module do */
MODULE_SUPPORTED_DEVICE("test");
