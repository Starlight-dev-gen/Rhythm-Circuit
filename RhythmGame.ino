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
float multiplier = 0.0;
String lStrip = "";
String rStrip = "";
//int lNotes[] = {4, 8, 12, 16, 20, 24, 28, 32, 34, 36, 42, 44, 50, 52, 58, 60};
String lNotes = "------[]------[]------[]------[]------[]------[]------[]------[]--[]--[]----------[]--[]----------[]--[]----------[]--[]--------"; 
//int rNotes[] = {8, 16, 24, 32, 38, 40, 46, 48, 51, 54, 56, 59, 62, 64};
String rNotes = "--------------[]--------------[]--------------[]--------------[]----------[]--[]----------[]--[]----[]----[]--[]----[]----[]--[]";
int progress = 0;
int remainder = lNotes.length();
int len = 16;

advance(String l, String r, float multiplier, int progress, int remainder){
  l = "";
  r = "";
  if (remainder < 16){
    len--;
  }
  for (int i = progress; i < progress + len; i++){
    l = l + lNotes[i];
    r = r + rNotes[i];
  }
  remainder--;
  progress++;
  delay((250 / 2) * multiplier);
}

void setup() {
  lcd.begin(16, 2);
  pinMode(lButton, INPUT);
  pinMode(rButton, OUTPUT);

  lcd.print("Press both");
  lcd.setCursor(0, 1);
  lcd.print("buttons to start");
}

void loop() {
  lPressed = digitalRead(lButton);
  rPressed = digitalRead(rButton);

  if (!gameRunning && !selectionMode){
    if (lPressed == HIGH && rPressed == HIGH){
      selectionMode = true;
      delay(15);
    }
  }
  else if(!gameRunning && selectionMode){
    if(!difficultySelect){
      if(lPressed == HIGH){
        lcd.setCursor(0, 0);
        lcd.print(">Normal");
        lcd.setCursor(0, 1);
        lcd.print(" Mirrored");
        mirrored = false;
        selectionMode = false;
        difficultySelect = true;
        delay(15);
      }
      else if(rPressed == HIGH){
        lcd.setCursor(0, 0);
        lcd.print(" Normal");
        lcd.setCursor(0, 1);
        lcd.print(">Mirrored");
        mirrored = true;
        selectionMode = false;
        difficultySelect = true;
        delay(15);
      }
      else{
        lcd.setCursor(0, 0);
        lcd.print(" Normal");
        lcd.setCursor(0, 1);
        lcd.print(" Mirrored");
      }
    }
    else{
      if(lPressed == HIGH && rPressed == HIGH){
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
      }
      else if(lPressed == HIGH && rPressed == LOW){
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
      }
      else if(lPressed == LOW && rPressed == HIGH){
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
      }
      else{
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
    if (mirrored){
      advance(lStrip, rStrip, multiplier, progress, remainder);
    }
    else{
      advance(rStrip, lStrip, multiplier, progress, remainder);
    }

    lcd.setCursor(0, 0);
    lcd.print(lStrip);
    lcd.setCursor(0, 1);
    lcd.print(rStrip);
  }
}
