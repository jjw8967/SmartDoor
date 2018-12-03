#!/bin/bash
sudo rm /dev/motor_dev
sudo rmmod motor_dev.ko
sudo insmod motor_dev.ko
sudo mknod -m 666 /dev/motor_dev c 240 0

