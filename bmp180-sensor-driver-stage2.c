/* BMP180 Sensor using I2C bus protocol
 *
 *in this program concentrated on  struct iio_dev members initialization
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>
#include <linux/printk.h>
#include <linux/iio/events.h>
#include <linux/iio/buffer.h>
#include <linux/iio/trigger.h>
#include <linux/iio/triggered_buffer.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/bitop.h>


#define BMP180_DRIVER_NAME  "bmp180-sensor-driver"
#define BMP180_CHIP_ID       0x55
#define STILL_NOT_COMPLETED   0

enum { AC1, AC2, AC3, AC4, AC5, AC6, B1, B2, MB, MC, MD }; // parameters of BMP180 //

struct bmp180_calib {
	s16 AC1;
	s16 AC2;
	s16 AC3;
	u16 AC4;
	u16 AC5;
	u16 AC6;
	s16 B1;
	s16 B2;
	s16 MB;
	s16 MC;
	s16 MD;
};

/*private structure to store the information*/
struct private_data {
	int a;
	char b;

};

/* read_raw function */

static int bmp180_read_raw(struct iio_dev *indio_dev,struct iio_chan_spec const *chan,int *val, int *val2, long mask)
{


	switch (mask) {

		case IIO_CHAN_INFO_PROCESSED:
			ret = mpl115_comp_pressure(data, val, val2);
			if (ret < 0)
			  return ret;
		        return IIO_VAL_INT_PLUS_MICRO;

	}



	return STILL_NOT_COMPLETE;

}

/* channels information */
static const struct iio_chan_spec bmp180_channels[] = {

	{
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),

	},

};

/* iio_info */
static const struct iio_info bmp180_info = {

	.read_raw = bmp180_read_raw,

};



/* i2c probe function */
static int bmp180_i2c_probe (struct i2c_client *client, const struct i2c_device_id *id)
{

	/* device structure representing the iio device */
	struct iio_dev *indio_dev=NULL;

	/*my private data structure */
	struct private_data *data = NULL;

	/* allocate iio_dev structure using devm_iio_device_allo ()
	 * @arg1: device to allocate iio_dev
	 * @arg2: size of private structure
	 * this function return Pointer to allocated iio_dev on success, NULL on failure
	 */
	indio_dev = devm_iio_device_alloc(&client->dev,sizeof(*data));
	if (!indio_dev) {
		pr_info("FAIL to allocate iio_dev structure\n");
		return -ENOMEM;
	}


	/* initialize struct iio_dev members */

	indio_dev->info = &bmp180_info;
	indio_dev->name = BMP180_DRIVER_NAME;
	indio_dev->channel = bmp180_channels;
	indio_dev->num_channels =ARRAY_SIZE(bmp180_channels);


	/* buffer setup using trigger */



	/* register the device with iio core */


	return STILL_NOT_COMPLETED;


}


/* i2c remove function */
static int bmp180_i2c_remove (struct i2c_client *client)
{


	/* de-allocate iio_dev structure */


	/* unregister with iio core */



	return STILL_NOT_COMPLETED;
}




/*
static int bmp180_i2c_detect(struct i2c_adapter *adapter, struct i2c_driver *driver)
{
		return STILL_NOT_COMPLETED;
}

*/

static const struct of_device_id bmp180_of_i2c_match[] = {
	{ .compatible = "bosch,bmp180", .data = (void *)BMP180_CHIP_ID },
	{ },
};

MODULE_DEVICE_TABLE(of, bmp180_of_i2c_match);

static const struct i2c_device_id bmp180_id[] = {
	{ BMP180_DRIVER_NAME, BMP180_CHIP_ID },
	{ },
};

MODULE_DEVICE_TABLE(i2c, bmp180_id);

/*
 * struct i2c_driver - represent an I2C device driver
 * @probe: Callback for device binding - soon to be deprecated
 * @remove: Callback for device unbinding
 * @driver: Device driver model driver
 * @id_table: List of I2C devices supported by this driver
 * @detect: Callback for device detection
 * @address_list: The I2C addresses to probe (for detect)
 * @owner:This field is used to prevent the module from being unloaded while its operations are in use
 */
static struct i2c_driver bmp180_i2c_driver = {
	.driver = {
		.name	= BMP180_DRIVER_NAME,
		.of_match_table = bmp180_of_i2c_match,
		.owner = THIS_MODULE,
		},
	.id_table	= bmp180_id,
	.probe		= bmp180_i2c_probe,
	.remove		= bmp180_i2c_remove,

	/*.detect		= bmp180_i2c_detect,*/
};

/* module init and exit functions present in the module_i2c_driver macro */
module_i2c_driver(bmp180_i2c_driver);

MODULE_DESCRIPTION("BMP180 Sensor driver");
MODULE_AUTHOR("Patil Rajesh Reddy");
MODULE_LICENSE("GPL");
