#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>
int main(void){
	int pirPin =1;
	int readPir =0;

	if(wiringPiSetup() == -1)
		exit(1);
	
	pinMode(pirPin, INPUT);
	while(1){
		readPir = digitalRead(pirPin);
		printf("%d",readPir);
		if(readPir==1) printf("Yeah\n");
		else printf("Non\n");
	}
	return 0;

}
