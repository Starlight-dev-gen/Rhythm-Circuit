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
String lStrip = ""; // 16 chars long
String rStrip = ""; // 16 chars long
int lNotes[] = {4, 8, 12, 16, 20, 24, 28, 32, 34, 36, 42, 44, 50, 52, 58, 60};
int rNotes[] = {8, 16, 24, 32, 38, 40, 46, 48, 51, 54, 56, 59, 62, 64};

void advance(String l, String r, float multiplier){
  // lStrip and rStrip are plugged into this function later, as well as the multiplier
  // mirroring is taken care of by function call, just make sure the strings are being rewritten
  // notes DO NOT CORRESPOND TO INDICES
  // positions not included in the notes should be two empty spaces or --
  // positions included should be []
  // Example:
  //  first lStrip with current lNotes: ------[]------[]
  //  first rStrip with current rNotes: --------------[]
  // These should flow leftwards with each call
  delay((250 / 2) * multiplier);
  // delay should be good but feel free to adjust if testing shows it is too slow/fast
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
      advance(lStrip, rStrip, multiplier);
    }
    else{
      advance(rStrip, lStrip, multiplier);
    }

    lcd.setCursor(0, 0);
    lcd.print(lStrip);
    lcd.setCursor(0, 1);
    lcd.print(rStrip);
  }
}
