#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/uaccess.h>

#define GPIO 17
#define DEV_NAME "btn_dev"
#define DEV_NUM 241

MODULE_LICENSE("GPL");

static unsigned int irqnum;
static unsigned int count = 0;
static unsigned int hi = 0;
static unsigned int result;
static irq_handler_t  ebbgpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);

//char k[2];
//char __user *buf;

int btn_open(struct inode *pinode, struct file *pile){
	printk(KERN_ALERT "OPEN btn_dev\n");
	gpio_request(GPIO, "GPIO");
	gpio_direction_input(GPIO);
	gpio_direction_output(GPIO , 1);
	printk(KERN_ALERT "gpio state : %d\n", gpio_get_value(GPIO));
	gpio_set_debounce(GPIO, 100);
	printk(KERN_ALERT "gpio input : %d\n", gpio_direction_input(GPIO));
	irqnum = gpio_to_irq(GPIO);
	printk(KERN_INFO "GPIO_TEST: The button is mapped to IRQ: %d\n", gpio_to_irq(GPIO));
	irq_set_irq_type(irqnum, IRQ_TYPE_EDGE_RISING);

	result = request_irq(irqnum, (irq_handler_t) ebbgpio_irq_handler, IRQF_TRIGGER_RISING, "ebb_gpio_handler", NULL);


//	result = request_irq(irqnum, gpio_int, 0, GPIO , NULL);
	printk(KERN_INFO "GPIO_TEST: The interrupt request result is: %d\n", result);

	return 0;
}

ssize_t btn_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset){
	printk(KERN_ALERT "BUTTON TEST TEST TEST %d\n", result);
//	buf = buffer;
//	irqnum = gpio_to_irq(GPIO);
	
//		result = request_irq(irqnum, (irq_handler_t) ebbgpio_irq_handler, IRQF_TRIGGER_RISING, "ebb_gpio_handler", NULL);
		if(hi > 0){
//			k[0] = "k"; k[1] = NULL;
			copy_to_user(buffer, "k", length);
			hi = 0;
//			k[0] = NULL; k[1] = NULL;
			printk(KERN_ALERT "GPIO TEST RESULT : %d\n", result);

//			break;
		}

}


int btn_close(struct inode *pinode, struct file *pfile){
	printk(KERN_ALERT "RELEASE btn_dev\n");
	free_irq(irqnum, NULL);
	count = 0;
	hi = 0;
//	k[0] = NULL; k[1] = NULL;
	gpio_unexport(GPIO);
	gpio_free(GPIO);
	return 0;
}

static irq_handler_t ebbgpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs){
	printk(KERN_INFO "GPIO_TEST: Interrupt! (button state is %d)\n", gpio_get_value(GPIO));

	if(gpio_get_value(GPIO)){
		printk(KERN_INFO "PRESSED BUUTON %d\n", count++);
//		copy_to_user(buf,"k",2);
		hi = 10;
	}
	return (irq_handler_t) IRQ_HANDLED;
}

struct file_operations fop = {
	.owner = THIS_MODULE,
	.open = btn_open,
	.read = btn_read,
	.release = btn_close,
};

int __init btn_init(void){
	printk(KERN_ALERT "INIT btn test \n");
	register_chrdev(DEV_NUM, DEV_NAME, &fop);
	return 0;
}

void __exit btn_exit(void){
	printk(KERN_ALERT "exit btn test \n");
	unregister_chrdev(DEV_NUM, DEV_NAME);
}

module_init(btn_init);
module_exit(btn_exit);
