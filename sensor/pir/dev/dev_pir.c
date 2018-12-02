#include<linux/gpio.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/delay.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>


#define GPIO4 23
#define DEV_NAME "pir_dev"
#define DEV_NUM 241

MODULE_LICENSE("GPL");
static char *msg = NULL;

int open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "OPEN pir_dev\n");
	gpio_request(GPIO4,"GPIO4");

	return 0;
}

ssize_t read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	int value;
	printk(KERN_ALERT "Read pir dev\n");
	
	value=gpio_get_value(GPIO4);
	if(value==0)
		copy_to_user(buffer,"0",1);
	else
		copy_to_user(buffer,"1",1);
	printk("%d\n",value);
	return 0;
}

int close(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "RELEASE pir_dev\n");
	gpio_free(GPIO4);
	return 0;
}

struct file_operations fop={
	.owner = THIS_MODULE,
	.open = open,
	.release = close,
	.read =read,
};

int __init dev_init(void){
	msg=(char*)kmalloc(32,GFP_KERNEL);
	printk(KERN_ALERT "INIT pir_dev\n");
	register_chrdev(DEV_NUM,DEV_NAME, &fop);
	return 0;
}
void __exit dev_exit(void){
	kfree(msg);
	printk(KERN_ALERT "EXIT pir_dev\n");
	unregister_chrdev(DEV_NUM,DEV_NAME);
}

module_init(dev_init);
module_exit(dev_exit);

