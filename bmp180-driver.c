// BMP180 PRESSURE SENSOR DRIVER //

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>		// If sysfs is used //
#include <linux/iio/events.h>		// Manage events of IIO //
#include <linux/iio/buffer.h>		// Manage buffer //
#include <linux/iio/trigger.h>		// If we use trigger //

enum { AC1, AC2, AC3, AC4, AC5, AC6, B1, B2, MB, MC, MD };

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

struct bmp180_chip_info {

	const int *oversampling_press_avail;
	int num_oversampling_press_avail;

	int (*chip_config)(struct bmp180_data *);
	int (*read_press)(struct bmp180_data *, int *, int *);

};


static const struct iio_chan_spec bmp180_channels[] = {
	{
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	};

	static const struct iio_info bmp180_info = {
		.read_raw = &bmp180_read_raw,
		//.read_avail = &bmp280_read_avail,// Need to check
		.write_raw = &bmp180_write_raw,
	};


	static int bmp280_read_raw(struct iio_dev *indio_dev,
                           struct iio_chan_spec const *chan,
                           int *val, int *val2, long mask)

		{
				return 0;
		}



int bmp180_probe(struct device *dev, const char *name, const struct bmp180_ops *ops)
{

				struct bmp180 *data;
				struct iio_dev *iio_device;
				int ret;
				iio_device = devm_iio_device_alloc(dev, sizeof(*data));

					if(!ii0_device){
						return -ENOMEM;

				iio_device->name = bmp180;
	      iio_device->channels = bmp180_channels;
	      iio_device->info = &bmp180_info;
	      iio_device->modes = INDIO_DIRECT_MODE;

				iio_device->dev.parent = dev;
				iio_device->name = name;
				iio_device->channel = bmp180_channels
				iio_device->num_channels = ARRAY_SIZE(bmp180_channels);
				iio_device->modes =(INDIO_DIRECT_MODE | INDIO_BUFFER_SOFTWARE);   // Need to check which mode is suitable //
				iio_device->info = &bmp180_info;

/*
				switch (chip) {
        case BMP180_CHIP_ID:
                indio_dev->num_channels = 2;
                data->chip_info = &bmp180_chip_info;
                data->oversampling_press = ilog2(8);
                data->oversampling_temp = ilog2(1);
                data->start_up_time = 10000;
                break;

								return -EINVAL
							}
*/

					}
			};
