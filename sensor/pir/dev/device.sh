#!/bin/bash
sudo rm /dev/dev_pir
sudo rmmod dev_pir.ko
sudo insmod dev_pir.ko
sudo mknod -m 666 /dev/dev_pir c 241 0

