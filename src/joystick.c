#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <stdio.h>

#include "../headers/joystick.h"
// #include "../headers/macros.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Joystick Module");

int init_joystick(void) {
  printf("Loading joystick module...");

  return 0;
}

void exit_joystick(void) {
  printf("Unloading joystick module...");

  return;
}

int load_unload() {
  module_init(init_joystick);
  module_exit(exit_joystick);
  return 0;
}
