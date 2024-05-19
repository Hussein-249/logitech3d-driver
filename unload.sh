#!/bin/bash
echo Unloading Logitech joystick kernel module
if sudo rmmod src/joystick.ko; then
  echo Joystick module successfully unloaded
fi
