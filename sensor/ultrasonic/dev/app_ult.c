#include<stdio.h>
#include<signal.h>

#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#define DEV_PATH "/dev/dev_ult"

static int fd=0;


int main(int argc, char *argv[]){
	char *buffer;
	if((fd =open(DEV_PATH, O_RDWR | O_NONBLOCK)) <0){
		perror("open()");
		printf("error\n");
		exit(1);
	}
	sleep(1);
	while(1){
		read(fd,buffer,10);
		printf("%s",buffer);
		sleep(2);
	}
	return 0;
}
