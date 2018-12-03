KERNELDIR = /lib/modules/$(shell uname -r)/build

obj-m := dev_ult.o

PWD := $(shell pwd)

default : 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean : 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean


