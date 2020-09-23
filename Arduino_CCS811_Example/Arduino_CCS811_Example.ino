#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;
int eCO2 = 0; //returns eCO2 reading
int TVOC = 0; //return TVOC reading
float temp = 0.0;
void setup() {
  Serial.begin(9600);

  Serial.println("CCS811 test");

  if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while (1);
  }

  // Wait for the sensor to be ready
  while (!ccs.available());
  temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
}

void loop() {
  if (ccs.available()) {
    if (!ccs.readData()) {
      eCO2 = ccs.geteCO2();
      TVOC = ccs.getTVOC();
      temp = ccs.calculateTemperature();
      Serial.print("CO2: ");
      Serial.print(eCO2);
      Serial.print("ppm\t");
      Serial.print("TVOC: ");
      Serial.print(TVOC);
      Serial.print("ppb\t");
      Serial.print("Temperatulkre: ");
      Serial.print(temp);
      Serial.println("C");
    }
    else {
      Serial.println("ERROR!");
      while (1);
    }
  }
  delay(500);
}
