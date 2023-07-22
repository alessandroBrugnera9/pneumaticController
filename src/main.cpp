#include <Arduino.h>

// SENSORS
// enum sensors
// {
//   ankle1 = A0,
//   ankle2,
//   knee1,
//   knee2,
//   hip1,
//   hip2,
//   biArticular1,
//   biArticular2,
//   biArticular3,
// };

const float voltageMultiplier = 560.0 / (560.0 + 390.0);
const float voltageRange = voltageMultiplier * 4.0;

float pressures[9];

void getPressures()
{
  for (int i = 0; i < 9; i++)
  {
    const int sensorPin = i + A0;
    int sensorValue = analogRead(sensorPin);      // Read the analog value from the pressure sensor
    float voltage = sensorValue * (3.3 / 4095.0); // Convert the analog value to voltage (assuming a 3.3V reference voltage, and 12 bits resolution)
    Serial.println(voltage, 4);                   // Print pressure value with 4 decimal places, (3.3/4096/2.4) has this precision

    // Tension divider with R2=560k and R1=390K
    // Map the voltage range (voltageMultiplier to voltageMultiplier*5) to the pressure range (0 MPa to 1 MPa)
    pressures[i] = (voltage - voltageMultiplier) / voltageRange;
  }
}

// VALVES
// start enum from 22 to avoid conflict with analog pins
const int valvePins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};

enum ValveState
{
  CLOSE,
  FILL,
  UNFILL,
};

ValveState valvesStates[9];

void setValvesStates()
{
  for (int i = 0; i < 9; i++)
  {
    const int valveIndex = i + 22;
    switch (valvesStates[i])
    {
    case FILL:
      digitalWrite(valvePins[valveIndex], HIGH);
      digitalWrite(valvePins[valveIndex + 1], LOW);
      break;

    case CLOSE:
      digitalWrite(valvePins[valveIndex], LOW);
      digitalWrite(valvePins[valveIndex + 1], LOW);
      break;

    case UNFILL:
      digitalWrite(valvePins[valveIndex], LOW);
      digitalWrite(valvePins[valveIndex + 1], HIGH);
      break;

    default:
      break;
    }
  }
}

// XPC COMMUNICATION
void readXPC()
{
  // TODO: decide if this is ISR or not
  // TODO: read valves command
}

void sendXPC()
{

  // TODO: handler variables to send to XPC
  // TODO: send to XPC
}

// LOOP MEASUREMENT
unsigned int counter = 0;
const int nLoops = 100;
unsigned long microsStart;

void setup()
{
  // preparing valves
  for (int i = 0; i < 18; i++)
  {
    pinMode(valvePins[i], OUTPUT);
    digitalWrite(valvePins[i], LOW);
  }

  // preparing sensors
  analogReadResolution(12); // changing reading resolution to 12 bits from arduino due

  // preparing serial communication
  counter = 0;
  Serial.begin(115200); // Initialize serial communication
  Serial.println("Setup Finished.");
}

void loop()
{
  // measure the time for 100 loops
  if (counter == 0)
  {
    microsStart = micros();
  }
  else if (counter == nLoops)
  {
    Serial.print("Time for 100 loops: ");
    Serial.println(micros() - microsStart);
    counter = 0;
  }

  readXPC();

  // handle valves and sensors
  getPressures();
  setValvesStates();

  sendXPC();
  counter++;
}