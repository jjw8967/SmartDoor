#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>

#define MY_IOCTL_NUMBER 100
#define MY_IOCTL_READ		_IOR(MY_IOCTL_NUMBER, 0, int)
#define MY_IOCTL_WRITE		_IOW(MY_IOCTL_NUMBER, 1, int)
#define MY_IOCTL_STATUS		_IO(MY_IOCTL_NUMBER, 2)
#define MY_IOCTL_READ_WRITE	_IOWR( MY_IOCTL_NUMBER, 3, int)
#define MY_IOCTL_NR		4

#define MY_MAJOR 200
#define MY_MINOR 0
#define MY_DEV_COUNT 2

struct cdev my_cdev;
char *msg = NULL;
int major;
dev_t devno;

int ioctl_dev_open (struct inode *pinode, struct file *pfile){
	printk("Open simple char drv\n");
	return 0;
}

int ioctl_dev_close(struct inode *pinode, struct file *pfile){
	printk("Release simple char drv\n");
	return 0;
}

long char_dev_ioctl(struct file *pfile, unsigned int command, unsigned long arg){
	char rtn_buffer[10];
	switch(command){
		case MY_IOCTL_WRITE: //write
			printk("Write simple char drv\n");
			memset(msg, 0 , 32);
			if(copy_from_user((void*)msg, (const void*)arg, (ssize_t)strlen((char *)arg))){
				printk("Write error\n");
				return -1;
			}
			printk("copy_from_user : %s\n",msg);

			break;
		
		case MY_IOCTL_READ:
			printk("Read simple char drv\n");
			if(strcmp(msg, "test") ==0){
				sprintf(rtn_buffer, "%s", "GET TEST");
			}
			else{
				sprintf(rtn_buffer, "%s", "NOT TEST");
			}
			copy_to_user((void __user *)arg, (const void*)rtn_buffer, strlen(rtn_buffer)+1);
			break;

		default:
			printk("Not found command ..\n");

			break;
	}
	return 0;

}


struct file_operations fop={
	.open = ioctl_dev_open,
	.release = ioctl_dev_close,
	.unlocked_ioctl = char_dev_ioctl,
};

int __init init(void){
	unsigned int count = MY_DEV_COUNT;
	int err;

	if(major){
		devno = MKDEV(major, MY_MINOR);
		register_chrdev_region(devno, count, "Simple char drv");
	}
	else{
		alloc_chrdev_region(&devno, MY_MINOR, count, "Simple char drv");
		major = MAJOR(devno);
	}
	cdev_init(&my_cdev, &fop);
	my_cdev.owner = THIS_MODULE;
	err = cdev_add(&my_cdev, devno, count);

	if(err < 0){
		printk("Device add error\n");
		return -1;
	}
	printk("'sudo mknod -m 666 /dev/ioctl_dev c %d 0', \n", MAJOR(devno));

	msg = (char *)kmalloc(32, GFP_KERNEL);
	if(msg != NULL)
		printk("malloc allocator address: 0x%p\n", msg);
	return 0;
}

void __exit exit(void)
{
	printk("Goodbye\n");
	if(msg){
		kfree(msg);
	}
	unregister_chrdev_region(devno, MY_DEV_COUNT);
	cdev_del(&my_cdev);
}

module_init(init);
module_exit(exit);
