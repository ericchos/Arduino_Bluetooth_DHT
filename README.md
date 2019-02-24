# Arduino_Bluetooth_DHT

Adding bluetooth to the Arduino with the HC-05 is much more simple than you think; The HC-05 bluetooth module adds a wireless serial port to your Arduino.
This is an example of using the HC-05 bluetooth module to perform actions from your smart phone.

The Setup:
- Arduino (Any Kind)
- HC-05 UART Bluetooth Module
- LEDs or any generic GPIO peripheral

## How to Use:
1. [Add Adafruit DHT library](https://github.com/adafruit/DHT-sensor-library)
2. Clone this repository
3. Connect HC-05 module to arduino pins 7 & 8 for software serial. [See How to Do This](https://howtomechatronics.com/tutorials/arduino/arduino-and-hc-05-bluetooth-module-tutorial/)
4. Connect DHT22 sensor to pin 4
5. Search **Bluetooth Terminal** on your smartphone appstore
6. Pair the HC-05 to your smartphone and you can send commands to the Arduino through the serial port

## Default Command List:
Sending the following strings (no '\r' or '\n' needed) can output the following:
- "0" : Read analog channel 0
- "1" : Read analog channel 1
- "2" : Read analog channel 2
- "3" : Read analog channel 3
- "4" : Read analog channel 4
- "5" : Read analog channel 5
- "6" : Read analog channel 6
- "7" : Read analog channel 7
- "D" : Read DHT22 Temperature and Humidity
- "R" : Toggle the Red LED
- "G" : Toggle the Green LED
- "B" : Toggle the Blue LED
