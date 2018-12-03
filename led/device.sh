#!/bin/bash
sudo rm /dev/ledtest_dev
sudo rmmod ledtest_dev.ko
sudo insmod ledtest_dev.ko
sudo mknod -m 666 /dev/ledtest_dev c 242 0

