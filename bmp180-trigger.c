// IIO Trigger setup //


struct iio_trigger_ops trigger_ops = {
    .set_trigger_state = on,
    .validate_device = BMP_180,
}

struct iio_trigger *trig;

/* first, allocate memory for our trigger */
trig = iio_trigger_alloc(dev, "trig-%s-%d", name, idx);

/* setup trigger operations field */
trig->ops = &trigger_ops;

/* now register the trigger with the IIO core */
iio_trigger_register(trig);
