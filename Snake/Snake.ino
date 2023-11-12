

uint8_t rowPins[8] = { 10, 11, 12, 13, A0, A1, A2, A3 };
uint8_t colPins[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };


#define joyX A4
#define joyY A5
int xValue, yValue;

void setup() {

  Serial.begin(9600);
  // Turn everything to low
  for (int i = 0; i < 8; i++) {
    pinMode(colPins[i], OUTPUT);
    pinMode(rowPins[i], OUTPUT);
  }
}

void loop() {

  byte character[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);

  for (int row = 0; row < 8; row++) {                         
    for (int k = 0; k < 8; k++) digitalWrite(colPins[k], HIGH);  
    digitalWrite(rowPins[row], HIGH);                            
    for (int col = 0; col < 8; col++) {
      digitalWrite(colPins[7 - col], character[row] & 1 << col ? LOW : HIGH);
    }
    delay(5);
    digitalWrite(rowPins[row], LOW);
  }
}


