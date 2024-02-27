#include<Arduino.h>

void separateCoordinates(String gcode);
void setup() {
  Serial.begin(9600);

  // Wait for user input
  Serial.println("Enter G-code:");
  while (!Serial.available()) {
    // Wait for input
  }
  
  // Read the entered G-code
  String gcode = Serial.readStringUntil('\n');

  // Separate X and Y components
  separateCoordinates(gcode);
}

void loop() {}

void separateCoordinates(String gcode) {
  char* cstr = new char[gcode.length() + 1];
  strcpy(cstr, gcode.c_str());

  char* token = strtok(cstr, " ");
  bool firstCoord = true;
  while (token != NULL) {
    if (token[0] == 'X') {
      float x = atof(token + 1);
      if (!firstCoord) {
        Serial.print(",");
      }
      Serial.print("(");
      Serial.print(x, 4); // Print x with 4 decimal places
      firstCoord = false;
    } else if (token[0] == 'Y') {
      float y = atof(token + 1);
      Serial.print(",");
      Serial.print(y, 4); // Print y with 4 decimal places
      Serial.print(")");
      firstCoord = true;
    }
    token = strtok(NULL, " ");
  }

  delete[] cstr;
}
