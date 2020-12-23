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



// IIO Trigger Interface //


void iio_trigger_poll(struct iio_trigger *trig)
{
    int i;
    if (!atomic_read(&trig->use_count))
    {
        atomic_set(&trig->use_count, CONFIG_IIO_CONSUMERS_PER_TRIGGER);
        for (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) {

            if (trig->subirqs[i].enabled)
                generic_handle_irq(trig->subirq_base + i);
            else
                iio_trigger_notify_done(trig);
        }
    }
}
