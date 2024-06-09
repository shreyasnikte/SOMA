#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println("Hello from the board");
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}