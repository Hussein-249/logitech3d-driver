#!/bin/bash
echo Unloading Logitech joystick kernel module
if sudo rmmod joystick.ko; then
  echo Joystick module successfully unloaded
fi
