# i2ctest.py
# A brief demonstration of the Raspberry Pi I2C interface, using the Sparkfun
# Pi Wedge breakout board and a SparkFun MCP4725 breakout board:
# https://www.sparkfun.com/products/8736

import smbus

# I2C channel 1 is connected to the GPIO pins
channel = 1

#  MCP4725 defaults to address 0x60
address = 0x68

# Register addresses (with "normal mode" power-down bits)
reg_read_dac = 0x75

# Initialize I2C (SMBus)
bus = smbus.SMBus(channel)

bus.read_i2c_block_data(0x68, 0x75)
