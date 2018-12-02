# RGB LED (WiringPi & device driver)

> 삼색 LED

## 작동 원리
> gpio_set_value() or gpio_direction_output()
* 각 GPIO 핀에 __HIGH__(output value)를 주면 그거와 매칭된 led를 켜준다.

## Device Driver

* DEV_NUM은 임시로 240으로 설정하였으며, GPIO1(RED)와 GPIO2(GREEN)을 할당하였다.
