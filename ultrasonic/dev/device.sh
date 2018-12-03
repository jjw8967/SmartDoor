#!/bin/bash
sudo rm /dev/dev_ult
sudo rmmod dev_ult.ko
sudo insmod dev_ult.ko
sudo mknod -m 666 /dev/dev_ult c 243 0

