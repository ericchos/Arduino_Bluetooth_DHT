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

// Global 
SoftwareSerial mySerial(7, 8); // RX, TX
DHT dht(DHTPIN, DHTTYPE);

// Functions 
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
  D(F("Send a 1 to read from the sensor\r\n"));
  
  // The HC-06 defaults to 9600 according to the datasheet.
  mySerial.begin(9600);
  
  dht.begin();
}

void loop() {
  
  // Receive character from Bluetooth Module 
  char rxData = mySerial.read();
  
  // Read Sensor if "1" is received
  if(rxData == '1')
  {
    dht_read();
    D(F("Received: ")); D(rxData); D(F("\r\n"));
  }
}

//===========================================================
// Read from DHT sensor and print the 
// temperature & humidity over the serial connection 
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
    D(F("Humidity: "));
    D(h);
    D(F(" %\t"));
    D(F("Temperature: ")); 
    D(t);
    D(F(" *C\r\n"));
    
    // Print output to bluetooth module
    mySerial.print(h);
    mySerial.print("&");
    mySerial.print(t);
    mySerial.print("\r\n");
  }
}