#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<linux/kdev_t.h>

#define DEV_PATH "/dev/ledtest_dev"

int main(int argc, char *argv[]){
	int fd =0;
	char *buffer;
	if((fd =open(DEV_PATH, O_RDWR | O_NONBLOCK)) <0){
		perror("open()");
		exit(1);
	}

	printf("open success!\n");
	sleep(2);
	
	read(fd,buffer,1);
	printf("read success!\n");
	sleep(2);
	write(fd,buffer,1);
	printf("write success!\n");
	sleep(2);
	close(fd);
	printf("close success!\n");
	sleep(2);
	return 0;
}
