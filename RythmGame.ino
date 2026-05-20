#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
const int lButton = 2;
int lPressed = 0;
const int rButton = 3;
int rPressed = 0;
bool gameRunning = false;
bool selectionMode = false;
bool difficultySelect = false;
bool mirrored = false;
bool endScreen = false;
float multiplier = 0.0;
String lStrip = "";
String rStrip = "";
//int lNotes[] = {4, 8, 12, 16, 20, 24, 28, 32, 34, 36, 42, 44, 50, 52, 58, 60};
String lNotes = "------[]------[]------[]------[]------[]------[]------[]------[]--[]--[]----------[]--[]----------[]--[]----------[]--[]--------"; 
//int rNotes[] = {8, 16, 24, 32, 38, 40, 46, 48, 51, 54, 56, 59, 62, 64};
String rNotes = "--------------[]--------------[]--------------[]--------------[]----------[]--[]----------[]--[]----[]----[]--[]----[]----[]--[]";
int progress = 0;
int great = 0;
int ok = 0;
int miss = 0;
int combo = 0;

void reset(){
  progress = 0;

  great = 0;
  ok = 0;
  miss = 0;
  combo = 0;

  gameRunning = false;
  endScreen = false;

  selectionMode = false;
  difficultySelect = false;
  mirrored = false;

  multiplier = 0.0;

  lStrip = "";
  rStrip = "";

  RandomGenString();
}

void RandomGenString(){
  lNotes = "";
  rNotes = "";
  for(int i = 0; i < 64; i++){
    if(rand() % 2 == 0){
      lNotes = lNotes + "[]";
    }
    else{
      lNotes = lNotes + "--";
    }
    if(rand() % 2 == 0){
      rNotes = rNotes + "[]";
    }
    else{
      rNotes = rNotes + "--";
    }
  }
}



void PointDistribution(char symbol){
  if(symbol == '['){
    great++;
    combo++;
  }
  else if(symbol == ']'){
    ok++;
    combo++;
  }
    else if(symbol == '-' ||symbol == ' '){
    miss++;
    combo = 0;
  }
  
  
}

float Score(){
  float multiplier2 = 0;
    if(combo <= 5){
        multiplier2 = 1;    
    }
    else if(combo <= 10){
           multiplier2 = 1.25;
    }
     else if(combo <= 15){
           multiplier2 = 1.5;
    }
      else if(combo <= 20){
           multiplier2 = 1.75;
    }
      else if(combo <= 25){
           multiplier2 = 2;
    }
      else if(combo <= 30){
           multiplier2 = 2.25;
    }


  return (10 *great + 5 * ok - 2 * miss) * multiplier2;
}

 void advance(String &l, String &r, float multiplier, int &progress,int rPressed,int lPressed){
  l = "";
  r = "";
  
  for (int i = progress; i < progress + 16 && i < rNotes.length() && i < lNotes.length(); i++){
    l = l + lNotes[i];
    r = r + rNotes[i];

  }

  char charl = l[0];
  char charr = r[0];

      
      if(lPressed == HIGH ){
      PointDistribution(charl);
    }

      
     if(rPressed == HIGH ){
      PointDistribution(charr);
    }

  progress++;
  delay((250 / 2) * multiplier);
}

void setup() {
  lcd.begin(16, 2);
  pinMode(lButton, INPUT);
  pinMode(rButton, INPUT);

  Serial.begin(9600);
  lcd.print("Press both");
  lcd.setCursor(0, 1);
  lcd.print("buttons to start");
}

void loop() {
  lPressed = digitalRead(lButton);
  rPressed = digitalRead(rButton);
  //Serial.print("\nleft button: ");
  //Serial.print(lPressed);
  //Serial.print("\nright button: ");
  //Serial.println(rPressed);
  Serial.print("\nselection mode:");
  Serial.print(selectionMode);
  Serial.print("\ndifficulty select:");
  Serial.print(difficultySelect);
  //Serial.print("\ngame running:");
  //Serial.print(gameRunning);

  if(!gameRunning){
    if(!difficultySelect){
      if(!selectionMode){
        if (lPressed == HIGH && rPressed == HIGH){
        
        reset();
        selectionMode = true;
        delay(150);
        }
      }
      else{
        if(lPressed == HIGH){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(">Normal");
          lcd.setCursor(0, 1);
          lcd.print(" Mirrored");
          mirrored = false;
          selectionMode = false;
          difficultySelect = true;
          delay(150);
        }
        else if(rPressed == HIGH){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Normal");
          lcd.setCursor(0, 1);
          lcd.print(">Mirrored");
          mirrored = true;
          selectionMode = false;
          difficultySelect = true;
          delay(150);
        }
        else{
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Normal");
          lcd.setCursor(0, 1);
          lcd.print(" Mirrored");
        }
      }
    }
    else{
      if(lPressed == HIGH && rPressed == HIGH){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("x1");
        lcd.setCursor(3, 0);
        lcd.print("x1.25");
        lcd.setCursor(9, 0);
        lcd.print("x1.5");
        lcd.setCursor(11, 1);
        lcd.print("/\\");
        multiplier = 1.0;
        difficultySelect = false;
        delay(15);
        gameRunning = true;
      }
      else if(lPressed == HIGH && rPressed == LOW){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("x1");
        lcd.setCursor(3, 0);
        lcd.print("x1.25");
        lcd.setCursor(9, 0);
        lcd.print("x1.5");
        lcd.setCursor(0, 1);
        lcd.print("/\\");
        multiplier = 1.5;
        difficultySelect = false;
        delay(15);
        gameRunning = true;
      }
      else if(lPressed == LOW && rPressed == HIGH){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("x1");
        lcd.setCursor(3, 0);
        lcd.print("x1.25");
        lcd.setCursor(9, 0);
        lcd.print("x1.5");
        lcd.setCursor(5, 1);
        lcd.print("/\\");
        multiplier = 1.25;
        difficultySelect = false;
        delay(15);
        gameRunning = true;
      }
      else{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("x1");
        lcd.setCursor(3, 0);
        lcd.print("x1.25");
        lcd.setCursor(9, 0);
        lcd.print("x1.5");
      }
    }
  }
  else{
    if(!endScreen){
      if (mirrored){
        advance(lStrip, rStrip, multiplier, progress,rPressed,lPressed);
        lcd.setCursor(0,0);
        if(progress >= lNotes.length()){
           endScreen = true;    
        }
      }    
      else{
        advance(rStrip, lStrip, multiplier, progress,rPressed,lPressed);
        lcd.setCursor(0,0);
        if( progress >= lNotes.length()){
          endScreen = true;    
        }
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(lStrip);
      lcd.setCursor(0, 1);
      lcd.print(rStrip);
    }
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(Score());
      delay(500);
      lcd.clear();
      lcd.print("go back to menu!");
      if(lPressed == HIGH || rPressed == HIGH){
        reset();
      }
    }
  }
}