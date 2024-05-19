#include <linux/init.h>
#include <linux/input.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>


MODULE_LICENSE("H249");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Joystick Module");


static struct input_dev * joystick_device;


static int __init init_joystick(void) {
  pr_info("Attempting to load joystick module...");

  joystick_device = input_allocate_device();
  // handle ENOMEM
  if (!joystick_device) {
        printk(KERN_ERR "Insufficient Memory.\n");
        return -ENOMEM;
  }
  joystick_device->name = "Logitech 3D Pro Driver";
  joystick_device->id.bustype = BUS_HOST;

  printk(KERN_INFO"Joystick Device Registered.\n");
  return 0;
}


static void __exit exit_joystick(void) {
  pr_info("Attempting to unload joystick module...");
  input_unregister_device(joystick_device);
  return;
}


module_init(init_joystick);
module_exit(exit_joystick);
