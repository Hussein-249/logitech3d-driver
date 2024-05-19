#!/bin/bash
echo Loading Logitech joystick kernel module
if sudo insmod src/joystick.ko; then
  echo joystick loaded
fi
