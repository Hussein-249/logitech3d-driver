#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>

#include "../headers/joystick.h"


static struct input_dev * joystick_device;


static int __init init_joystick(void) {
  pr_info("Attempting to load joystick module...");

  joystick_device = input_allocate_device();
  // handle ENOMEM
  if (!joystick_device) {
        printk(KERN_ERR "Insufficient Memory.\n");
        // ENOMEM is int, hence - making it subzero
        return -ENOMEM;
  }
  joystick_device->name = "Logitech 3D Pro Driver";
  joystick_device->id.bustype = BUS_HOST;

  // condition subzero if failed
  if (input_register_device(joystick_device)) {
    input_free_device(joystick_device);
    return -ENODEV;
  }

  printk(KERN_INFO"Joystick device registered.\n");
  return 0;
}


// ensures that driver only listens to inputs from the specified joystick.
static int joystick_selector(struct input_handle *handle) {
    if (handle->dev->id.vendor == LOGITECH_VID && handle->dev->id.product == LOGITECH_3DPRO_PID) {
        printk(KERN_INFO"Joystick device recognized.\n");
        return 0;
    }
    // reject unmatching devices
    return -ENODEV;
}


static void __exit exit_joystick(void) {
  pr_info("Attempting to unload joystick module...");
  input_unregister_device(joystick_device);
  return;
}


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Joystick Module");


module_init(init_joystick);
module_exit(exit_joystick);
