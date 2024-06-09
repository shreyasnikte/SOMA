#include <Arduino.h>

// put function declarations here:
int LED_BuiltIn = 2;
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BuiltIn, OUTPUT);
  Serial.begin(115200);
  int result = myFunction(2, 3);
}

void loop() {
  digitalWrite(LED_BuiltIn, HIGH);
  delay(1000);
  Serial.println("Hello from the board");
  digitalWrite(LED_BuiltIn, 0x0);
  delay(1000);
  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}