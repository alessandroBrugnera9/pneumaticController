#include <Arduino.h>

#include "EasyCAT.h" // EasyCAT library to interface the LAN9252


int nloopsCounter = 0;
unsigned long timeStart = 0;
const int nloops = 10000;

// Ethercat
EasyCAT EASYCAT(9); // EasyCAT SPI chip select. Standard is pin 9


// DECLARING PINS
// Valve Pins
// B Comes first of A because matlab convention in inverted with A and B
int valve1B = 33;
int valve2B = 41;
int valve3B = 40;
int valve4B = 39;
int valve5B = 27;
int valve6B = 26;
int valve7B = 13;
int valve8B = 12;
int valve9B = 10;
int valve1A = 24;
int valve2A = 25;
int valve3A = 23;
int valve4A = 22;
int valve5A = 28;
int valve6A = 29;
int valve7A = 30;
int valve8A = 31;
int valve9A = 32;

// Pressure Sensors Pins
// Non used pins are commented
  // TODO: remove these after assinng new pins
// int sensor1Pin = A3;
int sensor2Pin = A1;
int sensor3Pin = A9;
int sensor4Pin = A10;
int sensor5Pin = A3;
int sensor6Pin = A8;
// int sensor7 = A4;
int sensor8Pin = A0;
int sensor9Pin = A2;

void getPressureSensorsVoltage()
{
  // Reading
  // uint16_t sensor1 = analogRead(sensor1Pin);
  uint16_t sensor2 = analogRead(sensor2Pin);
  uint16_t sensor3 = analogRead(sensor3Pin);
  uint16_t sensor4 = analogRead(sensor4Pin);
  uint16_t sensor5 = analogRead(sensor5Pin);
  uint16_t sensor6 = analogRead(sensor6Pin);
  // uint16_t sensor7 = analogRead(sensor7Pin);
  uint16_t sensor8 = analogRead(sensor8Pin);
  uint16_t sensor9 = analogRead(sensor9Pin);

  // Unused Pins
  // TODO: remove these after assinng new pins
  uint16_t sensor1 = 0;
  uint16_t sensor7 = 0;


  // Sending
  // sensor1
  // Send first the most significant byte and then the least significant byte
  EASYCAT.BufferIn.Byte[0] = (sensor1 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[1] = (sensor1 & 0xFF);

  // sensor2
  EASYCAT.BufferIn.Byte[2] = (sensor2 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[3] = (sensor2 & 0xFF);

  // sensor3
  EASYCAT.BufferIn.Byte[4] = (sensor3 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[5] = (sensor3 & 0xFF);

  // sensor4
  EASYCAT.BufferIn.Byte[6] = (sensor4 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[7] = (sensor4 & 0xFF);

  // sensor5
  EASYCAT.BufferIn.Byte[8] = (sensor5 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[9] = (sensor5 & 0xFF);

  // sensor6
  EASYCAT.BufferIn.Byte[10] = (sensor6 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[11] = (sensor6 & 0xFF);

  // sensor7
  EASYCAT.BufferIn.Byte[12] = (sensor7 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[13] = (sensor7 & 0xFF);

  // sensor8
  EASYCAT.BufferIn.Byte[14] = (sensor8 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[15] = (sensor8 & 0xFF);

  // sensor9
  EASYCAT.BufferIn.Byte[16] = (sensor9 >> 8) & 0xFF;
  EASYCAT.BufferIn.Byte[17] = (sensor9 & 0xFF);
}

void controlValves()
{
  // Turning on/off Solenoids
  // digitalWrite(valve1A, EASYCAT.BufferOut.Byte[0]);
  // digitalWrite(valve1B, EASYCAT.BufferOut.Byte[1]);
  digitalWrite(valve2A, EASYCAT.BufferOut.Byte[2]);
  digitalWrite(valve2B, EASYCAT.BufferOut.Byte[3]);
  digitalWrite(valve3A, EASYCAT.BufferOut.Byte[4]);
  digitalWrite(valve3B, EASYCAT.BufferOut.Byte[5]);
  digitalWrite(valve4A, EASYCAT.BufferOut.Byte[6]);
  digitalWrite(valve4B, EASYCAT.BufferOut.Byte[7]);
  digitalWrite(valve5A, EASYCAT.BufferOut.Byte[8]);
  digitalWrite(valve5B, EASYCAT.BufferOut.Byte[9]);
  digitalWrite(valve6A, EASYCAT.BufferOut.Byte[10]);
  digitalWrite(valve6B, EASYCAT.BufferOut.Byte[11]);
  // digitalWrite(valve7A, EASYCAT.BufferOut.Byte[12]);
  // digitalWrite(valve7B, EASYCAT.BufferOut.Byte[13]);
  digitalWrite(valve8A, EASYCAT.BufferOut.Byte[14]);
  digitalWrite(valve8B, EASYCAT.BufferOut.Byte[15]);
  digitalWrite(valve9A, EASYCAT.BufferOut.Byte[16]);
  digitalWrite(valve9B, EASYCAT.BufferOut.Byte[17]);
}

void setup()
{
  Serial.begin(115200);
  // initial time for loop counter
  timeStart = millis();
  nloopsCounter = 0;

  // Pin Configurations
  //---------------------------------------------------------------------------------------------------------------------------//
  pinMode(valve1A, OUTPUT);
  pinMode(valve1B, OUTPUT);
  pinMode(valve2A, OUTPUT);
  pinMode(valve2B, OUTPUT);
  pinMode(valve3A, OUTPUT);
  pinMode(valve3B, OUTPUT);
  pinMode(valve4A, OUTPUT);
  pinMode(valve4B, OUTPUT);
  pinMode(valve5A, OUTPUT);
  pinMode(valve5B, OUTPUT);
  pinMode(valve6A, OUTPUT);
  pinMode(valve6B, OUTPUT);
  pinMode(valve7A, OUTPUT);
  pinMode(valve7B, OUTPUT);
  pinMode(valve8A, OUTPUT);
  pinMode(valve8B, OUTPUT);
  pinMode(valve9A, OUTPUT);
  pinMode(valve9B, OUTPUT);

  // Ethercat initlization if failed stay in loop blinking
  if (EASYCAT.Init() == true)
  {
  }

  else // initialization failed
  {
    while (1)
    {
      digitalWrite(13, LOW);
      delay(500);
      digitalWrite(13, HIGH);
      delay(500);
    }
  }

  Serial.println("Setup finished");
}

void loop()
{
  EASYCAT.MainTask(); // execute the EasyCAT task

  // every 10000 loops calculate the time necessary with counter
  if (nloopsCounter == nloops)
  {
    Serial.print("Time for ");
    Serial.print(nloops);
    Serial.print(" loops: ");
    Serial.println(millis() - timeStart);
    timeStart = millis();
    nloopsCounter = 0;
  }
  nloopsCounter++;

  if (Serial.available())
  {
    while (Serial.available())
    {
      Serial.read();
    }
    
    // also prints the pressure
    // 1v is 0 bar
    // 5v is 10 bar

    Serial.println("Sensor ");
    float voltage = (analogRead(A3) * 5.0) / 1023.0;
    Serial.print("Voltage: ");
    Serial.println(voltage);

    Serial.print("Pressure: ");
    Serial.println((voltage - 1.0) * (10.0 / 4.0));
  }

  getPressureSensorsVoltage();
  controlValves();
}