#define DEBUG 0

int irPin = A1;
int val = 0;

int first = A2;
int second = A3;
int third = A4;






int btn=analogRead(A5);


int LightRow[6];
int LightCol[6];


  
  int dice=0;
  //player
  int playerRow=5;
  int playerCol=0;
  int walkD = 400;


  int start=1;
  int winRow;
  int winCol;
  int loseRow[3];
  int loseCol[3];
  int winPoint=0;
  int re=0;
  
void setup() {
  
  //Dice
    
      pinMode(A2, OUTPUT);
      pinMode(A3, OUTPUT);
      pinMode(A4, OUTPUT);
    
    // set buttin pin to INPUT
  
    // initialize random seed by noise from analog pin 0 (should be unconnected)
    randomSeed(analogRead(A0));
  
    // if we're debugging, connect to serial 
    #ifdef DEBUG
      Serial.begin(9600);
    #endif
  




  for(int i = 0;i < 6;i++) LightRow[i]=i+8;
  for(int i = 0;i < 6;i++) LightCol[i]=i+2;

  
  
  
  for(int i = 0;i < 6;i++) pinMode(LightRow[i],OUTPUT);
  for(int i = 0;i < 6;i++) pinMode(LightCol[i],OUTPUT);

  LightOff();
  
  
}

void loop() {
  
  if(start == 1)
  {
    LightOff();
    delay(2000);

    //SetWin
    while(true)
    {
      winRow = random(0,6);
      winCol = random(0,6);
      if(winRow != playerRow && winCol != playerCol)
      {
        break;
      }
    }

    //SetBomb
    for(int i=0;i<=winPoint;i++)
    {
      while(true)
      {
        loseRow[i] = random(0,6);
        loseCol[i] = random(0,6);
        if(loseRow[i] != playerRow && loseCol[i] != playerCol)
        {
            if(loseRow[i] != winRow && loseCol != winCol)
            {
              break;
            }
        }
      }
    }


    //showTresure
    LightOn(winRow,winCol);
    delay(1000);
    LightOff();

    //showBomb
    for(int i=0;i<=winPoint;i++)
    {
      LightOn(loseRow[i],loseCol[i]);
      delay(100);
      LightOff();
      delay(100);
      LightOn(loseRow[i],loseCol[i]);
      delay(100);
      LightOff();
      delay(100);
      LightOn(loseRow[i],loseCol[i]);
      delay(100);
      LightOff();
      delay(100);
      
    }
    LightOff();
    
    start = 0;
    re=0;
  }
  

  
  //Serial.println(analogRead(A5));
  btn=analogRead(A5);
  if(dice!= 0 )
  {

      if(btn >= 900 )//Up
      {
          for(int i=1;i<=dice;i++)
          {
            LightOff();
            playerRow-=1;
            if(playerRow < 0)
            {
              playerRow=5;   
            }
            LightOn(playerRow,playerCol);
            delay(walkD);
            CheckLose();
            LightOff();
          }
          dice=0;
          OffDice();
      }
      else if(btn >= 400 )//Down
      {
          for(int i=1;i<=dice;i++)
          {
            LightOff();
            playerRow+=1;
            if(playerRow > 5)
            {
              playerRow=0;   
            }
            LightOn(playerRow,playerCol);
            delay(walkD);
            CheckLose();
            LightOff();
          }
          dice=0;
          OffDice();
      }
      else if(btn >= 290)//Left
      {
          for(int i=1;i<=dice;i++)
          {
            LightOff();
            playerCol-=1;
            if(playerCol < 0)
            {
              playerCol =5;   
            }
            LightOn(playerRow,playerCol);
            delay(walkD);
            CheckLose();
            LightOff();
          }
          dice=0;
          OffDice();
      }
      else if(btn > 150)//Right
      {
          for(int i=1;i<=dice;i++)
          {
            LightOff();
            playerCol+=1;
            if(playerCol > 5)
            {
              playerCol=0;   
            }
            LightOn(playerRow,playerCol);
            delay(walkD);
            CheckLose();
            LightOff();
          }
          dice=0;
          OffDice();
      } 
      
  }
  else
  {
      val = analogRead(irPin);
      if(val >= 320 && val <= 390){
        OffDice();
        buildUpTension();
        dice = ThrowDice();
        showDice(dice);
        
        //Serial.println(dice);
      }
      
  }


  //restartGame
  val = analogRead(irPin);
  if(val >= 10 && val <= 50)
  {
    dice=0;
    OffDice();
    RestartPoint();
  }

  if(re==0)
  {
    LightOn(playerRow,playerCol);
    CheckWin();
    if(winPoint == 3)
    {
        WinGame();
    }
  }
  
  

}










//Function

  void LightOn(int R,int C)
  {
    digitalWrite(LightRow[R],0);
    digitalWrite(LightCol[C],1);
  }
  
  void LightOff()
  {
    for(int i=0;i<6;i++)
    {
      digitalWrite(LightRow[i],1);
      digitalWrite(LightCol[i],0);
    }
  }
  void AllLight()
  {
    for(int i=0;i<6;i++)
    {
      digitalWrite(LightRow[i],0);
      digitalWrite(LightCol[i],1);
    }
  }
  //GetPoint
  void CheckWin()
  {
    //Collect
    
    if(playerRow == winRow && playerCol == winCol){ 
      winPoint+=1;
      start=1;
    }
    
  }
  //BombTrap
  void CheckLose()
  {
    for(int i=0;i<=winPoint;i++){
      if(playerRow == loseRow[i] && playerCol == loseCol[i]) 
      {
        Serial.println("lose");
        GameOver();
      }
    }
  }
  void WinGame()
  {

    
    dice=0;
    OffDice();
    while(true)
      {
        val = analogRead(irPin);
        if(val >= 10 && val <= 50)
        {
          
          RestartPoint();
          break;
        }
      }
  }
  void GameOver()
  {
      // ShowingBadMood

      dice=0;
      OffDice();
      while(true)
      {
        LightOn(1,1);
        LightOn(1,4);
        delay(1);
        LightOff();
        LightOn(3,1);
        LightOn(3,4);
        LightOn(3,2);
        LightOn(3,3);
        delay(1);
        LightOff();
        LightOn(4,0);
        LightOn(4,5);
        delay(1);
        LightOff();

        val = analogRead(irPin);
        if(val >= 10 && val <= 50)
        {
          RestartPoint();
          break;
        }
      }
  }
  void RestartPoint()
  {
    winPoint=0;
    start=1;
    playerRow=5;
    playerCol=0;
    re=1;
  }

  


//RandomDice
int ThrowDice() {

  int randNumber = random(1,4);

  #ifdef DEBUG
    Serial.println(randNumber);
  #endif

  return randNumber;
}
void OffDice() {
  
    digitalWrite(A2,LOW);
    digitalWrite(A3,LOW);
    digitalWrite(A4,LOW);
}
void showDice(int number) {
  digitalWrite(A2, HIGH);
  if (number >= 2) {
    digitalWrite(A3, HIGH);
  }
  if (number >= 3) {
    digitalWrite(A4, HIGH);
  }

}
void buildUpTension() {
  // light LEDs from left to right and back to build up tension
  // left to right
  digitalWrite(A2,HIGH);
  delay(50);
  OffDice();
  digitalWrite(A3,HIGH);
  delay(50);
  OffDice();
  digitalWrite(A4,HIGH);
  delay(50);
  OffDice();
    
  
  // right to left
  digitalWrite(A4,HIGH);
  delay(50);
  OffDice();
  digitalWrite(A3,HIGH);
  delay(50);
  OffDice();
  digitalWrite(A2,HIGH);
  delay(50);
  OffDice();
  
}
