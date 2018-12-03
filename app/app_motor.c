#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/kdev_t.h>

#define MOTOR_DEV_PATH "/dev/motor_dev"


int main(int argc, char *argv[]){
	int fd = 0;


	if((fd = open(MOTOR_DEV_PATH, O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}

	printf("open success\n");

	printf("open the door!\n");

	write(fd, "open", strlen("open"));
	
	return 0;
}
