#!/bin/bash
./load.sh
dmesg | tail -n 5

./unload.sh
dmesg | tail -n 5
