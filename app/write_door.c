#include<stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
	int f_door=0;
	if((f_door=open("/home/pi/Desktop/servo-motor/SmartDoor/app/door.txt",O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}
	write(f_door,"open",5);
	close(f_door);
	return 0;
}

