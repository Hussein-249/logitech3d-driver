#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <linux/input.h>

#define LOGITECH_VID 0x046d

#define LOGITECH_3DPRO_PID 0xc215

static int init_joystick(void);

static int joystick_selector(struct input_handle *handle);

static void exit_joystick(void);

#endif
