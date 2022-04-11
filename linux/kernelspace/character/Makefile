obj-m += lm-led-k.o
obj-m += lm-button-k.o
obj-m += lm-hd44780-k.o
obj-m += lm-bmp280-i2c-k.o
obj-m += lm-led-pwm-k.o
obj-m += lm-pwm-k.o
obj-m += lmk-random.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

lm-led-k:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) lm-led-k.ko
	
lm-button-k:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) lm-button-k.ko

lm-hd44780-k:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) lm-hd44780-k.ko

lm-bmp280-i2c-k:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) lm-bmp280-i2c-k.ko

lm-led-pwm-k:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) lm-led-pwm-k.ko

lm-pwm-k:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) lm-pwm-k.ko

lmk-random:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) lmk-random.ko

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean