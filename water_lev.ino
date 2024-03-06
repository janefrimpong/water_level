#include <NewPing.h>

const int TRIGGER_PIN = 4;
const int ECHO_PIN = 2;
const int MAX_DISTANCE = 100; // Maximum distance in centimeters. Adjust this according to your sensor's specifications.
const int TANK_HEIGHT = 30; // The height of your water tank in centimeters.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int readWaterLevel() {
  // Send a pulse to the sensor to start the measurement.
  unsigned int distance = sonar.ping_cm();

  if (distance == 0) {
    Serial.println("Out of range");
    return -1; // Return -1 to indicate an error or out-of-range reading.
  } else {
    // Calculate the water level percentage.
    int waterLevel = 100 - ((distance * 100) / TANK_HEIGHT);

    // Ensure the water level percentage is within bounds.
    waterLevel = constrain(waterLevel, 0, 100);

    return waterLevel;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Water Level Measurement");
}

void loop() {
  int waterLevelPercentage = readWaterLevel();

  if (waterLevelPercentage != -1) {
    // Print the water level on the serial monitor.
    Serial.print("Water Level: ");
    Serial.print(waterLevelPercentage);
    Serial.println("%");
  }

  delay(1000); // Adjust this delay as needed for the desired update frequency.
}
