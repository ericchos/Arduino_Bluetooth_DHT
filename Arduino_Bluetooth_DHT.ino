/*
  Arduino Bluetooth DHT Sensor
  
  Program reads from DHT Sensor and outputs the reading through the HC-05/06
  bluetooth module. Use a computer/Android phone/raspberry pi to get wireless 
  temperature & humidity readings.
  
  For instructions on the sensor, refer to: https://learn.adafruit.com/dht/overview 
  Library can be found at: https://github.com/adafruit/DHT-sensor-library
*/
#include <SoftwareSerial.h>
#include <DHT.h>

//Defines whether debug output will be used
//Comment out if not using 
#define DEBUG 

#ifdef DEBUG 
  #define D(x) Serial.print(x)
#else
  #define D(x)
#endif

#define DHTPIN    5
#define DHTTYPE   DHT22
#define R_LED     6
#define G_LED     9
#define B_LED     4

// Global 
SoftwareSerial mySerial(7, 8); // RX, TX
DHT dht(DHTPIN, DHTTYPE);
uint8_t rState = 0; // Initial state of red LED pin 
uint8_t gState = 0; // Initial state of green LED pin
uint8_t bState = 0; // Initial state of blue LED pin

// Functions 
void print_sensor(uint8_t sensor);
void dht_read();

//===========================================================
// Main Routine 
//===========================================================
void setup() {
  // Open serial communications:
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  D(F("Starting Arduino DHT22 Bluetooth Sensor\r\n"));
  D(F("Enter 0-7 to read from the respective analog sensors.\r\n"));
  D(F("Enter D to read from the DHT sensor.\r\n"));
  D(F("Enter R,G, or B to toggle each color of the RGB LED.\r\n"));
  
  //Initialize LED Port
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  
  // The HC-06 defaults to 9600 according to the datasheet.
  mySerial.begin(9600);
  
  dht.begin();
}

void loop() {
  
  // Receive character from Bluetooth Module 
  char rxData = mySerial.read();
  
  // Read Sensor if "1" is received
  print_sensor(rxData);
}

//===========================================================
// Read out a certain sensor based on the input from the
// bluetooth serial commands
//===========================================================
void print_sensor(uint8_t sensor)
{
  switch(sensor)
  {
    case '0':
      D(F("ADC 0: ")); D(analogRead(A0));
      mySerial.println(analogRead(A0));
      break;
    case '1':
      D(F("ADC 1: ")); D(analogRead(A1));
      mySerial.println(analogRead(A1));
      break;    
    case '2':
      D(F("ADC 2: ")); D(analogRead(A2));
      mySerial.println(analogRead(A2));
      break;    
    case '3':
      D(F("ADC 3: ")); D(analogRead(A3));
      mySerial.println(analogRead(A3));
      break;    
    case '4':
      D(F("ADC 4: ")); D(analogRead(A4));
      mySerial.println(analogRead(A4));
      break;   
    case '5':
      D(F("ADC 5: ")); D(analogRead(A5));
      mySerial.println(analogRead(A5));
      break;    
    case '6':
      D(F("ADC 6: ")); D(analogRead(A6));
      mySerial.println(analogRead(A6));
      break;    
    case '7':
      D(F("ADC 7: ")); D(analogRead(A7));
      mySerial.println(analogRead(A7));
      break;    
    case 'D':
      dht_read();
      break;
    case 'R':
      rState = !rState;
      digitalWrite(R_LED, rState);
      break;
    case 'G':
      gState = !gState;
      digitalWrite(G_LED, gState);
      break;
    case 'B':
      bState = !bState;
      digitalWrite(B_LED, bState);
      break;
  }
}

//===========================================================
// Read from DHT sensor and print the 
// temperature & humidity over the serial connection 
// From DHTtester.ino in Adafruit DHT library
//===========================================================
void dht_read()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, 
  // if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    D(F("Failed to read from DHT\r\n"));
    mySerial.print(F("0"));
    mySerial.print(F("\r\n"));
    mySerial.print(F("0"));
    mySerial.print(F("\r\n"));
  } else {
    // Print output to Arduino serial port
    D(F("Temperature: ")); 
    D(t);
    D(F("*C\t"));
    D(F("Humidity: "));
    D(h);
    D(F("%\r\n"));
    
    // Print output to bluetooth module
    mySerial.print(t);
    mySerial.print("\t");
    mySerial.print(h);
    mySerial.print("\r\n");
  }
}
