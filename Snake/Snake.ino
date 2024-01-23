String mapping[8] = { "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000" };

#include <EEPROM.h>
#define joyX A4
#define joyY A5
uint8_t rowPins[8] = { 10, 11, 12, 13, A0, A1, A2, A3 };
uint8_t colPins[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };
const int BUTTON = 0;
byte FoodPos[2];
byte length = 1;
byte Pos[2] = { 0, 0 };
byte snakeBody[64][2];
bool end = false, start = false;
String direction = "";

const char* numbersArray[] = {
  // 0
  "00111100",
  "01000010",
  "01000010",
  "01000010",
  "01000010",
  "01000010",
  "01000010",
  "00111100",

  // 1
  "00001000",
  "00011000",
  "00101000",
  "00001000",
  "00001000",
  "00001000",
  "00001000",
  "00111110",

  // 2
  "00111100",
  "01000010",
  "00000010",
  "00000100",
  "00001000",
  "00010000",
  "00100000",
  "01111110",

  // 3
  "00111100",
  "01000010",
  "00000010",
  "00001100",
  "00000010",
  "00000010",
  "01000010",
  "00111100",

  // 4
  "00011000",
  "00101000",
  "01001000",
  "10001000",
  "11111111",
  "00001000",
  "00001000",
  "00001000",

  // 5
  "01111110",
  "01000000",
  "01000000",
  "01111100",
  "00000010",
  "00000010",
  "01000010",
  "00111100",

  // 6
  "00011100",
  "00100000",
  "01000000",
  "01111100",
  "01000010",
  "01000010",
  "01000010",
  "00111100",

  // 7
  "01111110",
  "00000010",
  "00000100",
  "00001000",
  "00010000",
  "00100000",
  "00100000",
  "00100000",

  // 8
  "00111100",
  "01000010",
  "01000010",
  "00111100",
  "01000010",
  "01000010",
  "01000010",
  "00111100",

  // 9
  "00111100",
  "01000010",
  "01000010",
  "00111110",
  "00000010",
  "00000010",
  "01000010",
  "00111100"
};
const char* scoreArray[] = {
  // s
  "00111110",
  "01000000",
  "01000000",
  "00111100",
  "00000010",
  "00000010",
  "00000010",
  "01111100",
  // Additional row for 8x8 format

  // c
  "00111110",
  "01000000",
  "01000000",
  "01000000",
  "01000000",
  "01000000",
  "01000000",
  "00111110",  // Additional row for 8x8 format

  // o
  "00111100",
  "01000010",
  "01000010",
  "01000010",
  "01000010",
  "01000010",
  "01000010",
  "00111100",  // Additional row for 8x8 format

  // r
  "01111100",
  "01000010",
  "01000010",
  "01111100",
  "01000010",
  "01000010",
  "01000010",
  "01000010",  // Additional row for 8x8 format

  // e
  "01111100",
  "01000000",
  "01000000",
  "01111100",
  "01000000",
  "01000000",
  "01000000",
  "01111100"  // Additional row for 8x8 format
};
const char* bestArray[] = {
  // B
  "01111100",
  "01000010",
  "01000010",
  "01111100",
  "01000010",
  "01000010",
  "01000010",
  "01111100",  // Additional row for 8x8 format

  // E
  "01111100",
  "01000000",
  "01000000",
  "01111100",
  "01000000",
  "01000000",
  "01000000",
  "01111100",  // Additional row for 8x8 format

  // S
  "00111110",
  "01000000",
  "01000000",
  "00111100",
  "00000010",
  "00000010",
  "00000010",
  "01111100",  // Additional row for 8x8 format

  // T
  "01111110",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000"  // Additional row for 8x8 format
};
const char* startArray[] = {
  // S
  "00111110",
  "01000000",
  "01000000",
  "00111100",
  "00000010",
  "00000010",
  "00000010",
  "01111100",  // Additional row for 8x8 format

  // T
  "01111110",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000",  // Additional row for 8x8 format

  // A
  "00111100",
  "01000010",
  "01000010",
  "01111110",
  "01000010",
  "01000010",
  "01000010",
  "01000010",  // Additional row for 8x8 format

  // R
  "01111100",
  "01000010",
  "01000010",
  "01111100",
  "01001000",
  "01000100",
  "01000010",
  "01000010",  // Additional row for 8x8 format

  // T
  "01111110",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000",
  "00011000"
};


void setup() {
  pinMode(BUTTON, LOW);

  for (int i = 0; i < 8; i++) {
    pinMode(colPins[i], OUTPUT);
    pinMode(rowPins[i], OUTPUT);
  }
  Serial.begin(9600);
  if (EEPROM.read(0) == 255) {
    EEPROM.update(0, 0);
  } else EEPROM.update(0,(EEPROM.read(0)+1));
  FoodPos[0] = random(0, 8);
  FoodPos[1] = random(0, 8);
  snakeBody[0][0] = Pos[0];
  snakeBody[0][1] = Pos[1];
}

void loop() {
  if (start == false) {
    Start();
  }
  if (end == false && start==true) {
    ToMapping();
    Output();
    Move();
  }
  if (end == true) End();
}



void Output() {
  for (int i = 0; i < 30; i++) {
    for (int rows = 0; rows < 8; rows++) {
      for (int k = 0; k < 8; k++) digitalWrite(colPins[k], HIGH);
      digitalWrite(rowPins[rows], HIGH);
      for (int cols = 0; cols < 8; cols++) {
        digitalWrite(colPins[7 - cols], (mapping[rows][7 - cols] == '1') ? LOW : HIGH);
        
      }
      delay(2);
      digitalWrite(rowPins[rows], LOW);
      CheckDirection();
    }
    
  }
}

void FoodSpawn() {
  while (mapping[FoodPos[0]][FoodPos[1]] == '1') {
    FoodPos[0] = random(0, 8);
    FoodPos[1] = random(0, 8);
  }
  ToMapping();
}

void ToMapping() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      mapping[i][j] = '0';
    }
  }
  mapping[FoodPos[0]][FoodPos[1]] = '1';
  for (int i = 0; i < length; i++) {
    mapping[snakeBody[i][0]][snakeBody[i][1]] = '1';
  }
}
void CheckFood() {
  if (mapping[Pos[0]][Pos[1]] == '1' && Pos[0] != FoodPos[0] && Pos[1] != FoodPos[1]) {
    end = true;
  }
  if (Pos[0] == FoodPos[0] && Pos[1] == FoodPos[1]) {
    length++;
    for (int i = length; i >= 0; i--) {
      if (i == 0) {
        snakeBody[i][0] = Pos[0];
        snakeBody[i][1] = Pos[1];
      } else {
        snakeBody[i][0] = snakeBody[i - 1][0];
        snakeBody[i][1] = snakeBody[i - 1][1];
      }
    }
    FoodSpawn();
  }
}
void CheckDirection() {
  int xValue, yValue;
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  //-----------IRANYOK-----------
  if (xValue > 800) {
    direction = "down";
  }
  if (xValue < 200) {
    direction = "up";
  }
  if (yValue < 200) {
    direction = "left";
  }
  if (yValue > 800) {
    direction = "right";
  }
}
void Move() {
  CheckDirection();
  //-----------MOZGAS-----------
  //Mozgás le

  if (direction == "down") {
    Pos[0] = (Pos[0] + 1) % 8;
  }
  //Mozgás fel
  else if (direction == "up") {
    if (Pos[0] == 0) {
      Pos[0] = 8;
    }
    Pos[0] = Pos[0] - 1;
  }
  //Mozgás jobbra
  else if (direction == "right") {
    if (Pos[1] == 7) {
      Pos[1] = -1;
    }
    Pos[1] = (Pos[1] + 1) % 8;
  }
  //Mozgás balra
  else if (direction == "left") {
    if (Pos[1] == 0) {
      Pos[1] = 8;
    }
    Pos[1] = (Pos[1] - 1) % 8;
  }
  if (direction != "") {
    for (int i = length - 1; i >= 0; i--) {
      if (i == 0) {
        snakeBody[i][0] = Pos[0];
        snakeBody[i][1] = Pos[1];
      } else {
        snakeBody[i][0] = snakeBody[i - 1][0];
        snakeBody[i][1] = snakeBody[i - 1][1];
      }
    }
    CheckFood();
    ToMapping();
  }
  //-----------SERIAL KIIRATAS-----------
  Serial.print("direction: ");
  Serial.println(direction);
  Serial.print("Position: ");
  Serial.print(Pos[0]);
  Serial.print(" ");
  Serial.println(Pos[1]);
  Serial.print("FoodPosition: ");
  Serial.print(FoodPos[0]);
  Serial.print(" ");
  Serial.println(FoodPos[1]);
  Serial.println("mapping: ");
  for (int i = 0; i < 8; i++) {
    Serial.println(mapping[i]);
  }
}
void End() {

  byte score[2];
  if (EEPROM.read(0) == 255) {
    EEPROM.update(0, 0);
  } else EEPROM.update(0,(EEPROM.read(0)+1));
  if (EEPROM.read(1) == 255) {
    EEPROM.update(1, length);
  } else if (length > EEPROM.read(1)) {
    EEPROM.update(1, length);
  }
  score[0] = length / 10;
  score[1] = length % 10;

  for (int s = 0; s < 5; s++) {
    for (int i = 0; i < 8; i++) {

      mapping[i] = scoreArray[((s)*8) + i];
      Exit();
      if (end == false) return;
    }
    Output();
  }
  Exit();
  for (int s = 0; s < 2; s++) {
    for (int i = 0; i < 8; i++) {
      mapping[i] = numbersArray[((score[s]) * 8) + i];
      Exit();
      if (end == false) return;
    }
    Output();
  }
  Exit();
  score[0] = EEPROM.read(1) / 10;
  score[1] = EEPROM.read(1) % 10;
  for (int s = 0; s < 4; s++) {

    for (int i = 0; i < 8; i++) {
      mapping[i] = bestArray[((s)*8) + i];
      Exit();
      if (end == false) return;
    }
    Output();
  }

  for (int s = 0; s < 2; s++) {
    for (int i = 0; i < 8; i++) {
      mapping[i] = numbersArray[((score[s]) * 8) + i];
      Exit();
      if (end == false) return;
    }
    Output();
  }
}
void Exit() {
  if (digitalRead(BUTTON) == 0) {
    end = false;
    start = false;
    length = 1;
    direction = "";
    FoodPos[0] = random(0, 8);
    FoodPos[1] = random(0, 8);
    Pos[0] = random(0, 8);
    Pos[1] = random(0, 8);
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 2; j++) {
        snakeBody[i][j] = -1;
      }
    }
    snakeBody[0][0] = Pos[0];
    snakeBody[0][1] = Pos[1];
    return;
  }
}
void Start() {
  for (int s = 0; s < 5; s++) {
    for (int i = 0; i < 8; i++) {
      mapping[i] = startArray[((s)*8) + i];
      if (digitalRead(BUTTON) == 0) {
        start = true;
        return;
      }
    }
    Output();
  }
}
