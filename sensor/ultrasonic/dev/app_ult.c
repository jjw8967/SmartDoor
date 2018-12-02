#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define DEV_PATH "/dev/dev_ult"

static int fd=0;


int main(int argc, char *argv[]){
	char buffer[10];
	if((fd =open(DEV_PATH, O_RDWR | O_NONBLOCK)) <0){
		perror("open()");
		printf("error\n");
		exit(1);
	}
	sleep(1);
	while(1){
		read(fd,buffer,10);
		
		printf("%s\n",buffer);
		strcpy(buffer,"");
		sleep(1);
	}
	return 0;
}
