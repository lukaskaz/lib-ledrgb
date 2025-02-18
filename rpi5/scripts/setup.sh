#!/bin/bash

LIBPATH=$1
PWMCHANNEL=2
GPIOPIN=18
PINCTRL=a3

if [ -z "$LIBPATH" ]; then echo "Provide PATH of rpiws281x library"; exit 1; fi

cd $LIBPATH/rp1_ws281x_pwm
make
./dts.sh
sudo insmod ./rp1_ws281x_pwm.ko pwm_channel=$PWMCHANNEL
sudo dtoverlay -d . rp1_ws281x_pwm
sudo pinctrl set $GPIOPIN $PINCTRL pn
sudo chmod a+rw /dev/ws281x_pwm

echo "Done"

