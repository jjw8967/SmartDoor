#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>


#define GPIO5 24
#define GPIO6 25
#define DEV_NAME "dev_ult"
#define DEV_NUM 243

MODULE_LICENSE("GPL");
static long startTime=0;
static long travelTime =0;
static char distance[10];

int ult_open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "OPEN dev_ult\n");
	gpio_request(GPIO5, "GPIO5");
	gpio_request(GPIO6, "GPIO6");
	return 0;
}

int ult_close(struct inode *pinode, struct file *pfile){
	gpio_direction_output(GPIO5,0);
	gpio_direction_output(GPIO6,0);
	printk(KERN_ALERT "RELEASE dev_ult\n");
	return 0;
}
int ult_read(struct file *pfile, char *buffer, size_t size, loff_t *ppos){
	gpio_direction_output(GPIO5,1);
	udelay(20);
	gpio_direction_output(GPIO5,0);
	
	while(gpio_get_value(GPIO6)==0);
	//startTime = jiffies;

	while(gpio_get_value(GPIO6)==1);
	//travelTime = (jiffies - startTime)/HZ*1000;

	memset(distance,0,10);
	sprintf(distance,"%d",(int)(travelTime / 58));
	//copy_to_user(buffer,distance,strlen(distance+1));

	printk(KERN_ALERT "distance = %s\n",distance);
	return 0;	
}

int ult_write(struct file *pfile, const char *buffer, size_t size, loff_t *ppos){
	return 0;
}
struct file_operations fop={
	.owner = THIS_MODULE,
	.open = ult_open,
	.read = ult_read,
	.write = ult_write,
	.release = ult_close,
};

int __init utl_init(void){
	printk(KERN_ALERT "INIT dev_ult\n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);
	return 0;
}

void __exit utl_exit(void){
	printk(KERN_ALERT "EXIT dev_ult\n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}

module_init(utl_init);
module_exit(utl_exit);


