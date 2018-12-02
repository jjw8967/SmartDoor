#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define BUFFER_LENGTH 256

#define MY_IOCTL_NUMBER 100
#define MY_IOCTL_READ	_IOR( MY_IOCTL_NUMBER, 0, int)
#define MY_IOCTL_WRITE	_IOW( MY_IOCTL_NUMBER, 1, int)
#define MY_IOCTL_STATUS	_IO( MY_IOCTL_NUMBER, 2 )
#define MY_IOCTL_READ_WRITE _IOWR(MY_IOCTL_NUMBER, 3, int)
#define MY_IOCTL_NR	4

int main(){
	int ret,fd;
	char stringToSend[BUFFER_LENGTH];
	char receive[BUFFER_LENGTH];
	fd = open("/dev/ioctl_dev", O_RDWR);

	if(fd <0){
		perror("Failed to open the device...");
		return errno;
	}

	printf("Type in a short string to send to the kernel module: \n");
	scanf("%[^\n]%*c", stringToSend);
	printf("Writing message to the device [%s].\n", stringToSend);

	ioctl(fd, MY_IOCTL_WRITE, stringToSend);

	printf("Reading from the device ...\n");

	char *temp;
	ioctl(fd, MY_IOCTL_READ, receive);

	printf("The received message is : [%s]\n", receive);
	printf("End of the program\n");

	return 0;
}
