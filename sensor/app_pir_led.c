#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<linux/kdev_t.h>
#include<string.h>

#define PIR_PATH "/dev/dev_pir"
#define LED_PATH "/dev/ledtest_dev"

int main(int argc, char *argv[]){
	int fd_pir =0;
	int fd_led =0;
	char *buffer = (char*)malloc(sizeof(char)*10);

	if((fd_pir = open(PIR_PATH, O_RDWR | O_NONBLOCK))<0){
		perror("open()");
		exit(1);
	}
	if((fd_led = open(LED_PATH, O_RDWR | O_NONBLOCK))<0){
		perror("open()");
		exit(1);
	}

	printf("open success!\n");

	while(1){
		read(fd_pir,buffer,1);
		printf("%s\n",buffer);
		if(strcmp(buffer,"1")==0){
			printf("yeah\n");
			write(fd_led,buffer,1);
		}
		else{
			printf("None\n");
			read(fd_led,buffer,1);
		}
		usleep(200*1000);
		
	}
	return 0;
}
