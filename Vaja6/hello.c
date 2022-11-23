/*  
 *  hello.c - Demonstrates module documentation.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */

static int __init init_modul(void)
{
	printk(KERN_INFO "Hello, world 4\n");
	return 0;
}

static void __exit cleanup_modul(void)
{
	printk(KERN_INFO "Goodbye, world 4\n");
}

module_init(init_modul);
module_exit(cleanup_modul);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author Name");	/* Who wrote this module? */
MODULE_DESCRIPTION("Demo modul");	/* What does this module do */
