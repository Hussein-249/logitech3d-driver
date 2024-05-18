#!/bin/bash
echo Loading Logitech joystick kernel module
if sudo insmod joystick.ko; then
  echo joystick loaded
fi
