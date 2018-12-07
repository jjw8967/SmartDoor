all : 
	make motor
	make ult
	make button
	make led

led : 
	sudo insmod led/ledtest_dev.ko
	sudo mknod -m 666 /dev/ledtest_dev c 242 0

motor :
	sudo insmod motor_dev/motor_dev.ko
	sudo mknod -m 666 /dev/motor_dev c 240 0

button :
	sudo insmod button_dev/btn_dev.ko
	sudo mknod -m 666 /dev/btn_dev c 241 0

ult :
	sudo insmod ultrasonic/dev/dev_ult.ko
	sudo mknod -m 666 /dev/dev_ult c 243 0

clean : 
	make rmult
	make rmbtn
	make rmmotor
	make rmled

rmult :  /dev/dev_ult
	sudo rmmod ultrasonic/dev/dev_ult.ko
	sudo rm /dev/dev_ult

rmbtn :	 /dev/btn_dev 
	sudo rmmod button_dev/btn_dev.ko
	sudo rm /dev/btn_dev

rmmotor : /dev/motor_dev
	sudo rmmod motor_dev/motor_dev.ko
	sudo rm /dev/motor_dev

rmled : /dev/ledtest_dev	
	sudo rmmod led/ledtest_dev.ko
	sudo rm /dev/ledtest_dev

