#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>

#define GPIO1 18
#define GPIO2 27
#define DEV_NAME "ledtest_dev"
#define DEV_NUM 240

MODULE_LICENSE("GPL");

int ledtest_open(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "OPEN ledtest_dev\n");
	gpio_request(GPIO1, "GPIO1");
	gpio_request(GPIO2, "GPIO2");
	gpio_direction_output(GPIO2, 0);
	gpio_direction_output(GPIO1, 0);
	return 0;
}

int ledtest_close(struct inode *pinode, struct file *pfile){
	gpio_set_value(GPIO2,0);
	gpio_set_value(GPIO1,0);
	printk(KERN_ALERT "RELEASE ledtets_dev\n");
	return 0;
}
int ledtest_on(struct file *pfile, char *buffer, size_t size, loff_t *ppos){
	gpio_set_value(GPIO2,0);
	gpio_set_value(GPIO1,1);
	return 0;	
}
int ledtest_off(struct file *pfile, const char *buffer, size_t size, loff_t *ppos){
	gpio_set_value(GPIO1,0);
	gpio_set_value(GPIO2,1);
	return 0;
}
struct file_operations fop={
	.owner = THIS_MODULE,
	.open = ledtest_open,
	.read = ledtest_on,
	.write = ledtest_off,
	.release = ledtest_close,
};

int __init ledtest_init(void){
	printk(KERN_ALERT "INIT ledtest\n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);
	return 0;
}

void __exit ledtest_exit(void){
	printk(KERN_ALERT "EXIT ledtest_dev\n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}

module_init(ledtest_init);
module_exit(ledtest_exit);


