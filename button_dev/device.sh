#!/bin/bash
sudo rm /dev/btn_dev
sudo rmmod btn_dev.ko
sudo insmod btn_dev.ko
sudo mknod -m 666 /dev/btn_dev c 241 0

