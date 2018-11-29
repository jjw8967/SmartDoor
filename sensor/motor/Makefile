KERNELDIR = /lib/modules/$(shell uname -r)/build

obj-m := motortest_dev.o

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
