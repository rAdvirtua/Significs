#include <SoftwareSerial.h>

const int analogPin1 = A0;
const int analogPin2 = A1;
const int analogPin3 = A2;
const int analogPin4 = A3;
const int analogPin5 = A4;

bool thumb = false;
bool index = false;
bool middle = false;
bool ring = false;
bool pinky = false;
char detected = '\0';
bool numberMode = false; // Mode flag

// HC-05 Bluetooth module setup (RX on 10, TX on 11)
SoftwareSerial BT(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);   // Serial Monitor for debugging
  BT.begin(9600);       // Start Bluetooth communication
  delay(1000);          // Wait for serial monitor to initialize
  Serial.println("Sign Language Interpreter Ready!");
  BT.println("Sign Language Interpreter Ready!"); // Send to Bluetooth
}

void loop() {
  // Read actual sensor values
  int value1 = analogRead(analogPin1);
  int value2 = analogRead(analogPin2);
  int value3 = analogRead(analogPin3);
  int value4 = analogRead(analogPin4);
  int value5 = analogRead(analogPin5);

  // Determine if fingers are bent
  thumb = value1 > 350;
  index = value2 > 350;
  middle = value3 > 350;
  ring = value4 > 350;
  pinky = value5 > 350;

  // Debugging output to Serial Monitor
  Serial.print("Thumb: "); Serial.print(thumb);
  Serial.print(" | Index: "); Serial.print(index);
  Serial.print(" | Middle: "); Serial.print(middle);
  Serial.print(" | Ring: "); Serial.print(ring);
  Serial.print(" | Pinky: "); Serial.println(pinky);

  // Toggle between letter mode and number mode if only the thumb is bent
  if (thumb && !index && !middle && !ring && !pinky) {
    numberMode = !numberMode;
    Serial.print("Mode Switched: ");
    Serial.println(numberMode ? "Number Mode" : "Letter Mode");
    BT.print("Mode Switched: ");
    BT.println(numberMode ? "Number Mode" : "Letter Mode");
    delay(2000); // Prevent accidental toggling
  }

  // Letter Mode
  if (!numberMode) {
    if (thumb && index && middle && ring && pinky) detected = 'A';
    else if (!thumb && index && middle && ring && pinky) detected = 'B';
    else if (!thumb && !index && middle && ring && pinky) detected = 'C';
    else if (!thumb && !index && !middle && ring && pinky) detected = 'D';
    else if (!thumb && !index && !middle && !ring && pinky) detected = 'E';
    else detected = '\0'; // Reset detected character
  }
  // Number Mode
  else {
    if (!thumb && !index && !middle && !ring && !pinky) detected = '0';
    else if (!thumb && index && !middle && !ring && !pinky) detected = '1';
    else if (!thumb && index && middle && !ring && !pinky) detected = '2';
    else if (!thumb && index && middle && ring && !pinky) detected = '3';
    else if (!thumb && index && middle && ring && pinky) detected = '4';
    else if (!thumb && !index && middle && ring && pinky) detected = '5';
    else if (!thumb && !index && !middle && ring && pinky) detected = '6';
    else if (!thumb && !index && !middle && !ring && pinky) detected = '7';
    else if (!thumb && !index && !middle && !ring && !pinky) detected = '8';
    else if (!thumb && !index && !middle && !ring && pinky) detected = '9';
    else detected = '\0'; // Reset detected character
  }

  // Send detected character to Serial Monitor and Bluetooth
  if (detected != '\0') {
    Serial.print("Detected: ");
    Serial.println(detected);
    BT.print("Detected: ");
    BT.println(detected);
  }

  delay(1500); // Delay for readability
}
