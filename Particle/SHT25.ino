// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// SHT25
// This code is designed to work with the SHT25_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Humidity?sku=SHT25_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// SHT25 I2C address is 0x40(64)
#define Addr 0x40

double humidity = 0.0, cTemp = 0.0, fTemp = 0.0;
void setup() 
{
    // Set variable
    Particle.variable("i2cdevice", "SHT25");
    Particle.variable("humidity", humidity);
    Particle.variable("cTemp", cTemp);
  
    // Initialise I2C communication as MASTER 
    Wire.begin();
    // Initialise serial communication, set baud rate = 9600
    Serial.begin(9600);
    delay(300);
}

void loop() 
{
    unsigned int data[2];
    // Start I2C communication
    Wire.beginTransmission(Addr);
    // Send humidity measurement command, NO HOLD master
    Wire.write(0xF5);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(500);

    // Request 2 bytes of data
    Wire.requestFrom(Addr, 2);

    // Read 2 bytes of data
    // humidity msb, humidity lsb
    if(Wire.available() == 2)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
        
        // Convert the data
        humidity = ((((data[0] * 256.0) + data[1]) * 125.0) / 65536.0) - 6; 
        
        // Output data to dashboard
        Particle.publish("Relative Humidity    :  ",  String(humidity));
    }

    // Start I2C transmission
    Wire.beginTransmission(Addr);
    // Send temperature measurement command, NO HOLD master           
    Wire.write(0xF3);
    // Stop I2C transmission
    Wire.endTransmission();
    delay(500);
    
    // Request 2 bytes of data
    Wire.requestFrom(Addr,2);

    // Read 2 bytes of data
    // temp msb, temp lsb
    if(Wire.available() == 2)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
        
        // Convert the data
        cTemp = ((((data[0] * 256.0) + data[1]) * 175.72) / 65536.0) - 46.85;
        fTemp = (cTemp * 1.8) + 32;
        
        // Output data to dashboard
        Particle.publish("Temperature in Celsius:  ",  String(cTemp));
        Particle.publish("Temperature in Fahrenheit:  ", String(fTemp));
    } 
  delay(300);
}
