#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/kdev_t.h>

#define DEV_PATH "/dev/btn_dev"

static char receive[128];

int main(int argc, char *argv[]){
	int fd = 0;
	if((fd = open(DEV_PATH, O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}

	printf("open success\n");

	int ret = read(fd, receive, 2);

	while(1){
		int ret = read(fd, receive, 2);

		if(strcmp(receive, "o") == 0){
			printf("button pressed %s\n", receive);
			receive[0] = '0';
			break;
		}
	}
	
	int i = 0;

	printf("enter 1  close:");
	scanf("%d", &i);
	
	if(i == 1){
		printf("close\n");
		close(fd);
	}
	
	return 0;
}
