#!/bin/bash

BINPATH=$1

if [ -z "$BINPATH" ]; then echo "Provide PATH of rpiws281x binary"; exit 1; fi

sudo usermod -aG kmem lukasz
sudo chmod g+wr /dev/mem
sudo setcap cap_sys_rawio+ep $BINPATH

echo "Done"

