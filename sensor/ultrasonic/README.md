# Ultrasonic (WiringPi & device driver)
>  초음파 센서

## 작동 원리

1. TRIG OUTPUT이 1 -> 0 이 갈 때 초음파를 일으킨다.
2. 그 뒤 ECHO INPUT은 0이면, 그 때 마이크로 단위의 타이머를 시작하고.
3. ECHO INPUT이 1이 되면, 초음파가 도착했다는 의미 이며, 이 때 타이머의 시간을 멈춘다.
4. 거리는 = micro timer / 58 이된다. (여기서 58의 의미는 모름)

## Device Driver
* DEV_NUM 은 임시로 243을 설정하였으며, GPIO5(Trig)와 GPIO6(ECHO)를 할당하였다. 
* Timer는 do_gettimeofday() 함수를 통해 구현했다.
