
uint8_t rowPins[8] = { 10, 11, 12, 13, A0, A1, A2, A3 };
uint8_t colPins[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };
#define joyX A4
#define joyY A5
int xValue, yValue;
byte mapWithFood[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 };
String character = "";
String direction;

String mapping[8] = { "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000", "00000000" };

bool ate = true, start = false;

void setup() {
  randomSeed(millis());
  Serial.begin(9600);
  // Turn everything to low
  for (int i = 0; i < 8; i++) 
  {
    pinMode(colPins[i], OUTPUT);
    pinMode(rowPins[i], OUTPUT);
  }
  
}


void loop() {


  Move();
  /*if (ate) {
    FoodSpawn();
  }*/
  for (int rows = 0; rows < 8; rows++) 
  {
    for (int k = 0; k < 8; k++) digitalWrite(colPins[k], HIGH);
    digitalWrite(rowPins[rows], HIGH);
    for (int cols = 0; cols < 8; cols++) 
    {
      digitalWrite(colPins[7 - cols], mapWithFood[rows] & 1 << cols ? LOW : HIGH);
    }
    delay(2);
    digitalWrite(rowPins[rows], LOW);
  }
  delay(1000);
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
  for (int i = 8; i >= 0; i--) 
  {
    if (mapWithFood[row] - (byte(pow(2, i))) > 0) 
    {
      mapWithFood[row] -= byte(pow(2, i));
      character = character + "1";
    } else if ((mapWithFood[row] - (byte(pow(2, i))) < 0)) 
    {
      character = character + "0";
    }
  }
  Serial.print("character: ");
  Serial.print(character);
  Serial.println("");
  Serial.print("character.charAt(col)");
  Serial.print(character.charAt(col));
  Serial.println("");
  if (character.charAt(col) == '0') 
  {
    character.setCharAt(col, '1');
    Serial.print("character.charAt(col)");
    Serial.print(character.charAt(col));
    Serial.println("");
  }
  mapWithFood[row] = byte(character.toInt());
  ate = false;
  for (int i = 0; i < 8; i++) 
  {
    Serial.print(mapWithFood[i], BIN);
    Serial.print(",");
  }
  Serial.println("");
}
byte Pos[2] = { 7, 7 };
byte snake;

void Move() {

  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  /*Serial.print("xValue: ");
  Serial.println(xValue);
  Serial.print("yValue: ");
  Serial.println(yValue);*/
  if (start == false) 
  {
    mapping[Pos[0]][Pos[1]] = '1';
    Serial.println("mapping[i]");
    for(int i=0;i<8;i++)
    {
      Serial.println(mapping[i]);
    }
    for (int i = 0; i < 8; i++) 
    {
      for (int j = 8; j > 0; j--) 
      {
        
        if(mapping[i][j]=='1')
        {
          if(j<6)
          {
            mapWithFood[i]+=pow(2,7-j)+1;
          }
          else mapWithFood[i]+=pow(2,7-j);
          
        }
      }
      Serial.println(" ");
    }
    start = true;
  }
  if (xValue > 1000) 
  {
    Serial.print("Moving down ");
    Serial.println("");
    direction = "down";
  }
  if (xValue < 100) 
  {
    Serial.print("Moving up ");
    Serial.println("");
    direction = "up";
  }
  if (yValue < 100) 
  {
    Serial.print("Moving left ");
    Serial.println("");
    direction = "left";
  }
  if (yValue > 1000) 
  {
    Serial.print("Moving  right");
    Serial.println("");
    direction = "right";
  }

  if (direction == "down") 
  {
    mapping[Pos[0]][Pos[1]] = '0';
    Pos[0] = (Pos[0]+1) % 8;

    mapping[Pos[0]][Pos[1]] = '1';
    for (int i = 0; i < 8; i++) 
    {
      for (int j = 8; j >= 0; j--) 
      {
        if(mapping[i][j]=='1')
        {
         if(Pos[1]<6) 
         {
          mapWithFood[i]=pow(2,7-Pos[1])+1;
          snake=mapWithFood[i];
         }
         else 
         {
          mapWithFood[i]=pow(2,7-Pos[1]);
          snake=mapWithFood[i];
         }
        }
        if(mapping[i][j]=='0')
        {
          if(Pos[0]==i)
          {
            mapWithFood[i]=snake;
          }
          else mapWithFood[i]=0;
        }
      }
      Serial.println(" ");
    }
  }
  if (direction == "up") 
  {
    mapping[Pos[0]][Pos[1]] = '0';
    if(Pos[0]==0)
    {
      Pos[0]=8;
    }
    Pos[0] = Pos[0]-1;

    mapping[Pos[0]][Pos[1]] = '1';
    
    for (int i = 0; i < 8; i++) 
    {
      for (int j = 8; j >= 0; j--) 
      {
        if(mapping[i][j]=='1')
        {

         if(Pos[1]<6) 
         {
          mapWithFood[i]=pow(2,7-Pos[1])+1;
          snake=mapWithFood[i];
         }
         else 
         {
          mapWithFood[i]=pow(2,7-Pos[1]);
          snake=mapWithFood[i];
         }
        }
        if(mapping[i][j]=='0')
        {
          if(Pos[0]==i)
          {
            mapWithFood[i]=snake;
          }
          else mapWithFood[i]=0;
        }
      }
      Serial.println(" ");
    }
    
  }
  if (direction == "right") 
  {
    mapping[Pos[0]][Pos[1]] = '0';
    if(Pos[1]==7)
    {
      Pos[1]=-1;
    }

    Pos[1] = (Pos[1]+1) %8;
    mapping[Pos[0]][Pos[1]] = '1';
    for (int i = 0; i < 8; i++) 
    {
      for (int j = 8; j >= 0; j--) 
      {
        if(mapping[i][j]=='1')
        {
         if(Pos[1]==7 || Pos[1]==6)
          {
            mapWithFood[i]=pow(2,7-Pos[1]);
          }else  
          {
            mapWithFood[i]=pow(2,7-Pos[1])+1;
            snake=mapWithFood[i];
          }
        }
        
      }
      Serial.println(" ");
    }
    
  }
  if (direction == "left") 
  {
    mapping[Pos[0]][Pos[1]] = '0';
    if(Pos[1]==0)
    {
      Pos[1]=8;
    }
    Pos[1] = (Pos[1]-1) %8;
    mapping[Pos[0]][Pos[1]] = '1';
    for (int i = 0; i < 8; i++) 
    {
      for (int j = 8; j >= 0; j--) 
      {
        
        if(mapping[i][j]=='1')
        {
         if(Pos[1]==7 || Pos[1]==6)
         {
          mapWithFood[i]=pow(2,7-Pos[1]);
          
         }else  
          {
            mapWithFood[i]=pow(2,7-Pos[1])+1;
            snake=mapWithFood[i];
          }
        }
      }
      Serial.println(" ");
    }
    
  }

  Serial.print("direction: ");
  Serial.println(direction);
  Serial.print("Position: ");
  Serial.print(Pos[0]);
  Serial.print(" ");
  Serial.println(Pos[1]);
  Serial.println("mapping: ");
  for(int i=0;i<8;i++){
    Serial.println(mapWithFood[i]);

  }
  
  
}
