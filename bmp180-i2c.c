// IIO Trigger //

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/err.h>


static const unsigned short normal_i2c[] = { BMP180_I2C_ADDRESS, I2C_CLIENT_END };

static int bmp180_i2c_detect(struct i2c_client *client,
			     struct i2c_board_info *info)
{
	if (client->addr != BMP085_I2C_ADDRESS)
		return -ENODEV;

	return bmp180_detect(&client->dev);
}

static int bmp180_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int err;
	struct regmap *regmap = devm_regmap_init_i2c(client, &bmp180_regmap_config);

	if (IS_ERR(regmap)) {
		err = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to init regmap: %d\n", err);
		return err;
	}

	return bmp180_probe(&client->dev, regmap, client->irq);
}

static int bmp180_i2c_remove(struct i2c_client *client)
{
	return bmp180_remove(&client->dev);
}

static const struct i2c_device_id bmp085_id[] = {
	{ BMP180_NAME, 0 },
	{ "bmp180", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, bmp180_id);

static struct i2c_driver bmp180_i2c_driver = {
	.driver = {
		.name	= BMP180,
		},
	.id_table	= bmp180_id,
	.probe		= bmp180_i2c_probe,
	.remove		= bmp180_i2c_remove,

	.detect		= bmp180_i2c_detect,
	.address_list	= normal_i2c
};

module_i2c_driver(bmp180_i2c_driver);

MODULE_DESCRIPTION("BMP180 I2C bus driver");
MODULE_LICENSE("GPL");
