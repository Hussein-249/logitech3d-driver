#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/input.h>

// #include "../headers/joystick.h"

// using the header to include this for some reason breaks this module,
// and I don't know how to fix it except by including the code here
#define LOGITECH_VID 0x046d
#define LOGITECH_3DPRO_PID 0xc215
static bool joystick_selector(struct input_handler *handler, struct input_dev * dev);
static int joystick_connect(struct input_handler *handler, struct input_dev *dev, const struct input_device_id *id);
static void joystick_disconnect(struct input_handle *handle);
static void joystick_event(struct input_handle *handler, unsigned int type, unsigned int code, int value);


// to recognize the logitech joystick
static const struct input_device_id joystick_ids[] = {
    { .flags = INPUT_DEVICE_ID_MATCH_VENDOR | INPUT_DEVICE_ID_MATCH_PRODUCT,
     .vendor = LOGITECH_VID, .product = LOGITECH_3DPRO_PID },
    { }
};

MODULE_DEVICE_TABLE(input, joystick_ids);

static struct input_dev * joystick_device;
// needed as a common interface for input devices
// has callbacks for an event, a match, etc.
// id_table used when targeting only specific input devices
static struct input_handler joystick_handler = {
    .event = joystick_event,
    .match = joystick_selector,
    .connect = joystick_connect,
    .disconnect = joystick_disconnect,
    .name = "Logitech 3D Pro",
    .id_table = joystick_ids,
};


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
  
  // 3-axis joystick
  set_bit(ABS_X, joystick_device->absbit);
  set_bit(ABS_Y, joystick_device->absbit);
  set_bit(ABS_Z, joystick_device->absbit);
  set_bit(EV_ABS, joystick_device->evbit);
  set_bit(EV_KEY, joystick_device->evbit);
  set_bit(BTN_1, joystick_device->keybit);
  set_bit(BTN_1, joystick_device->keybit);
  
  // setting ranges
  input_set_abs_params(joystick_device, ABS_X, -32767, 32767, 0, 0);
  input_set_abs_params(joystick_device, ABS_Y, -32767, 32767, 0, 0);
  input_set_abs_params(joystick_device, ABS_Z, -32767, 32767, 0, 0);

  // condition subzero if failed
  if (input_register_device(joystick_device)) {
    input_free_device(joystick_device);
    return -ENODEV;
  }
  
  // if device registered, register its input handler
  if (input_register_handler(&joystick_handler)) {
	  input_free_device(joystick_device);
	  return -ENODEV;
	}
	  
  printk(KERN_INFO"Joystick device registered.\n");
  return 0;
}


// ensures that driver only listens to inputs from the specified joystick.
static bool joystick_selector(struct input_handler *handler, struct input_dev * dev) {
	printk(KERN_INFO"Device inserted.\n");
	pr_info("Vendor ID: %04x", dev->id.vendor);
    pr_info("Product ID: %04x", dev->id.product);
    
    if (dev->id.vendor == LOGITECH_VID && dev->id.product == LOGITECH_3DPRO_PID) {
        printk(KERN_INFO"Joystick device recognized.\n");
        return true;
    }
    // reject unmatching devices
    return false;
}


static void joystick_event(struct input_handle *handler, unsigned int type, unsigned int code, int value) {
	
	printk(KERN_INFO"Joystick event recognized.\n");
	if (type == EV_KEY) {
        switch (code) {
            case BTN_TRIGGER:
                if (value == 1) {
                    printk(KERN_INFO "Joystick trigger button pressed\n");
                } else {
                    printk(KERN_INFO "Joystick trigger button released\n");
                }
                break;
            case BTN_THUMB:
                if (value == 1) {
      
                    printk(KERN_INFO "Joystick thumb button pressed\n");
                } else {

                    printk(KERN_INFO "Joystick thumb button released\n");
                }
                break;
        }
    }
	return;
}


static int joystick_connect(struct input_handler *handler, struct input_dev *dev, const struct input_device_id *id) {
  // placeholder
    return 0; 
}


static void joystick_disconnect(struct input_handle *handle) {
  // placeholder
    return;
}


static void __exit exit_joystick(void) {
  printk(KERN_INFO"Unloading joystick module.\n");
  input_unregister_handler(&joystick_handler);
  input_unregister_device(joystick_device);
  return;
}


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Joystick Module");

module_init(init_joystick);
module_exit(exit_joystick);
