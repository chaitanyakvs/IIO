obj-m+=bmp180-driver.o

all:
	make -C /lib/modules/4.15.0-128-generic/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/4.15.0-128-generic/build/ M=$(PWD) clean
