#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/kdev_t.h>
#include <pthread.h>

#define BTN_DEV_PATH "/dev/btn_dev"
#define MOTOR_DEV_PATH "/dev/motor_dev"
#define ULT_DEV_PATH "/dev/dev_ult"
#define LED_DEV_PATH "/dev/ledtest_dev"

static char receive[128];

static int check=0;
int f_door =0;
void read_door(){
	char buffer[10];
	memset(buffer,'\0',10);

		
	while(1){
		if((f_door=open("door.txt",O_RDWR | O_NONBLOCK)) < 0){
			perror("open()");
			exit(1);
		}
		read(f_door,buffer,5);
		
		if(strncmp(buffer,"open",5)==0)
			break;

		close(f_door);
	}
	check =1;
	return;
}
int main(int argc, char *argv[]){
	int fd_b = 0; //button
	int fd_m = 0; //motor
	int fd_l = 0; //led
	int fd_u = 0; //ultrasonic

	
	if((fd_b = open(BTN_DEV_PATH, O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}
	if((fd_m = open(MOTOR_DEV_PATH, O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}
	if((fd_l = open(LED_DEV_PATH, O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}
	if((fd_u = open(ULT_DEV_PATH, O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}
	

	printf("open success\n");

	char buffer[10];
	int distance=0;
	int ret;
	pthread_t proc_web;

	while(1){

	while(1){
		read(fd_u,buffer,9);
		printf("%s\n",buffer);
		distance=atoi(buffer);
		if(distance<15){
			write(fd_l,buffer,1);
			break;
		}else{
			read(fd_l,buffer,1);
		}
		usleep(500*1000);
	}
	if((f_door=open("door.txt",O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}		
	write(f_door,"",1);
	close(f_door);
	pthread_create(&proc_web, NULL, read_door,NULL);
	
	while(1){
		ret = read(fd_b, receive, 2);

		if(strcmp(receive, "o") == 0 || check == 1){
			printf("button pressed %s\n", receive);
			receive[0] = '0';
			pthread_cancel(proc_web);
			check=0;
			write(fd_m, "open", strlen("open"));
			break;
		}
		ret = 1;
		usleep(50*1000);
		
	}

	usleep(4000*1000);
	write(fd_m, "close", strlen("close"));
	if((f_door=open("door.txt",O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}		
	write(f_door,"",1);
	close(f_door);
	}
	int i = 0;

	printf("enter 1  close:");
	scanf("%d", &i);
	
	if(i == 1){
		printf("close\n");
		close(fd_b);
	}
	
	return 0;
}
