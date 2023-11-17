
uint8_t rowPins[8] = { 10, 11, 12, 13, A0, A1, A2, A3 };
uint8_t colPins[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };
#define joyX A4
#define joyY A5
int xValue, yValue;
byte mapWithFood[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 };
String character = "";
byte direction = 0;

String mapping[8] = { "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000" };
bool ate = true, start = false;
byte Pos[2];
void setup() {
randomSeed(millis());
  Serial.begin(9600);
  // Turn everything to low
  for (int i = 0; i < 8; i++) {
    pinMode(colPins[i], OUTPUT);
    pinMode(rowPins[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    mapWithFood[i] = byte(mapping[i].toInt());
    Serial.println(mapWithFood[i]);
  }
}


void loop() {


  Move();
  /*if (ate) {
    FoodSpawn();
  }*/
  for (int rows = 0; rows < 8; rows++) {
    for (int k = 0; k < 8; k++) digitalWrite(colPins[k], HIGH);
    digitalWrite(rowPins[rows], HIGH);
    for (int cols = 0; cols < 8; cols++) {
      digitalWrite(colPins[7 - cols], mapWithFood[rows] & 1 << cols ? LOW : HIGH);
    }
    delay(5);
    digitalWrite(rowPins[rows], LOW);
  }
}

void FoodSpawn() {
  byte row, col, zeros;
  character = "";
  row = random(0, 8);
  col = random(0, 8);
  Serial.print("Row: ");
  Serial.print(row);
  Serial.print(" \tCol: ");
  Serial.print(col);
  Serial.println("");
  Serial.print("mapWithFood[row]: ");
  Serial.print(mapWithFood[row]);
  Serial.println("");
  for (int i = 8; i >= 0; i--) {
    if (mapWithFood[row] - (byte(pow(2, i))) > 0) {
      mapWithFood[row] -= byte(pow(2, i));
      character = character + "1";
    } else if ((mapWithFood[row] - (byte(pow(2, i))) < 0)) {
      character = character + "0";
    }
  }
  Serial.print("character: ");
  Serial.print(character);
  Serial.println("");


  Serial.print("character.charAt(col)");
  Serial.print(character.charAt(col));
  Serial.println("");
  if (character.charAt(col) == '0') {
    character.setCharAt(col, '1');
    Serial.print("character.charAt(col)");
    Serial.print(character.charAt(col));
    Serial.println("");
  }
  mapWithFood[row] = byte(character.toInt());
  ate = false;
  for (int i = 0; i < 8; i++) {
    Serial.print(mapWithFood[i], BIN);
    Serial.print(",");
  }
  Serial.println("");
}

void Move() {
  
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  if (start == false) {
  byte Pos[2] = { random(0, 8), random(0, 8) };
    mapping[Pos[0]][Pos[1]] = '1';
    for (int i = 0; i < 8; i++) {
      mapWithFood[i] = byte(mapping[i].toInt());
      Serial.println(mapWithFood[i]);
    }
    start = true;
  }
  if (xValue > 1000) {
    direction = 3;
  } else if (xValue < 100) {
    direction = 4;
  } else if (yValue > 1000) {
    direction = 1;
  } else if (yValue < 100) {
    direction = 0;
  }

  /*switch (direction) {
    case 0:
      mapping[Pos[0]][Pos[0]] = '0';
      mapping[row - 1][col] = '1';
      for (int i = 0; i < 8; i++) {
        mapWithFood[i] = byte(mapping[i].toInt());
        Serial.println(mapWithFood[i]);
      }
      break;

    case 1:
      mapping[row][col] = '0';
      mapping[row + 1][col] = '1';
      for (int i = 0; i < 8; i++) {
        mapWithFood[i] = byte(mapping[i].toInt());
        Serial.println(mapWithFood[i]);
      }
      break;

    case 2:
      mapping[row][col] = '0';
      mapping[row][col + 1] = '1';
      for (int i = 0; i < 8; i++) {
        mapWithFood[i] = byte(mapping[i].toInt());
        Serial.println(mapWithFood[i]);
      }
      break;

    case 3:
      mapping[row][col] = '0';
      mapping[row][col - 1] = '1';
      for (int i = 0; i < 8; i++) {
        mapWithFood[i] = byte(mapping[i].toInt());
        Serial.println(mapWithFood[i]);
      }
      break;

    default:

      break;
  }*/
}
