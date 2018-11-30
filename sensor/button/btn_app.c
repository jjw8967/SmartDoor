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
	
	int i = 0;

		int ret = read(fd, receive, 2);


//		printf("enter 1 -> close :");
//		scanf("%d", &i);

//		int ret = read(fd, receive, 128);
//
		while(1){
		int ret = read(fd, receive, 2);
//		printf("button %s\n", receive);

			if(strcmp(receive, "1") == 0){
				printf("hihi\n");
			}else if(strcmp(receive, "k") == 0){
				printf("button pressed %s\n", receive);
				receive[0] = '3';
				continue;
			}
		}

		printf("enter 1  close:");
		scanf("%d", &i);

		if(i == 1){
			printf("close\n");
			close(fd);
		}
	
	return 0;
}
