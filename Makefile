CC = gcc
CFLAGS = -D USE_DEV_LIB -Wall -pthread
LIBS = -lrt -lm -lpigpio

SRC = main.c motorDriver.c DEV_Config.c dev_hardware_i2c.c dev_hardware_SPI.c sysfs_gpio.c PCA9685.c
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

run:
	sudo ./main
