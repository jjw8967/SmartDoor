#!/bin/bash
sudo rm /dev/ioctl_app_dev
sudo rmmod ioctl_app_dev.ko
sudo insmod ioctl_app_dev.ko
sudo mknod -m 666 /dev/dev_pir c 200 0

