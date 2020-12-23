// i2c probe for BMP180 //

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/i2c.h>

// module to detect i2c device by bus id and can change according to the hardware */

#define	I2C_BUS_MAX	4

// device probing addreses need to change according to hardware //
static const unsigned short probe_i2c_addrs[] = I2C_ADDRS(0x55, 0x56);

static struct i2c_board_info bmp085_i2c_info[] = {

	{
		I2C_BOARD_INFO("bmp180", 0x55),
	}
};

static int __init bmp180_probe_init(void)
{
	int nr;
	printk(KERN_INFO "%s probing bus max %d\n", __FUNCTION__, I2C_BUS_MAX);

	for (nr =0; nr < I2C_BUS_MAX; nr++) {

		struct i2c_adapter * adap = i2c_get_adapter(nr);

		if (adap) {
			struct i2c_client *i2c = i2c_new_probed_device(adap, bmp180_i2c_info, probe_i2c_addrs, NULL);

			if (i2c) {
				printk("Found i2c dev %s addr 0x%x\n", i2c->name, i2c->addr);
			}
		}
	}

	return 0;
}

static void __exit bmp180_probe_exit(void)
{
	printk(KERN_INFO "%s\n", __FUNCTION__);
}

module_init(bmp180_probe_init);
module_exit(bmp180_probe_exit);

MODULE_AUTHOR("chaitanya");
MODULE_DESCRIPTION("bmp180 init procedure");
MODULE_LICENSE("GPL");
