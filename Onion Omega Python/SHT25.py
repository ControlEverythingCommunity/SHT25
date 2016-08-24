# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# SHT25
# This code is designed to work with the SHT25_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Humidity?sku=SHT25_I2CS#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# SHT25 address, 0x40(64)
# Send temperature measurement command
#		0xF3(243)	NO HOLD master
data = [0xF3]
i2c.write(0x40, data)

time.sleep(0.5)

# SHT25 address, 0x40(64)
# Read data back, 2 bytes
# Temp MSB, Temp LSB
data = i2c.readBytes(0x40, 0x40, 2)

# Convert the data
temp = data[0] * 256 + data[1]
cTemp= -46.85 + ((temp * 175.72) / 65536.0)
fTemp = cTemp * 1.8 + 32

# SHT25 address, 0x40(64)
# Send humidity measurement command
#		0xF5(245)	NO HOLD master
data = [0xF5]
i2c.write(0x40, data)

time.sleep(0.5)

# SHT25 address, 0x40(64)
# Read data back, 2 bytes
# Humidity MSB, Humidity LSB
data = i2c.readBytes(0x40, 0x40, 2)

# Convert the data
humidity = data[0] * 256 + data[1]
humidity = -6 + ((humidity * 125.0) / 65536.0)

# Output data to screen
print "Relative Humidity is : %.2f %%" %humidity
print "Temperature in Celsius is : %.2f C" %cTemp
print "Temperature in Fahrenheit is : %.2f F" %fTemp
