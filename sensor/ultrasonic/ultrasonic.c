#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

#define TRIG 5
#define ECHO 6

void setup(){
	wiringPiSetup();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	digitalWrite(TRIG,LOW);
	delay(30);
}
int getCM(){
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(20);
	digitalWrite(TRIG, LOW);
	while(digitalRead(ECHO) == LOW);
	long startTime = micros();
	while(digitalRead(ECHO) == HIGH);
	long travelTime = micros() - startTime;

	int distance = travelTime / 50;

	return distance;
}

int main(void){
	while(1){
	setup();

	printf("Distance: %dcm\n", getCM());
	delay(1000);
	}
	return 0;
}
