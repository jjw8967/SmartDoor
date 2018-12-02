#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<linux/kdev_t.h>
#include<string.h>

#define DEV_PATH "/dev/dev_pir"

int main(int argc, char *argv[]){
	int fd =0;
	char *buffer = (char*)malloc(sizeof(char)*10);

	if((fd = open(DEV_PATH, O_RDWR | O_NONBLOCK))<0){
		perror("open()");
		exit(1);
	}

	printf("open success!\n");

	while(1){
		read(fd,buffer,1);
		printf("%s",buffer);
		if(strcmp(buffer,"1")==0)
			printf("yeah\n");
		else
			printf("None\n");
		
	}
	return 0;
}
