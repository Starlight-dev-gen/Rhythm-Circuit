#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
const int lButton = 2;
int lPressed = 0;
const int rButton = 3;
int rPressed = 0;
bool gameRunning = false;
bool selectionMode = false;
String lStrip = "";
String rStrip = "";
int lNotes[] = {4, 8, 12, 16, 20, 24, 28, 32, 34, 36, 42, 44, 50, 52, 58, 60};
int rNotes[] = {8, 16, 24, 32, 38, 40, 46, 48, 51, 54, 56, 59, 62, 64};

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
    if (lPressed == HIGH){
      lcd.setCursor(0, 0);
      lcd.print(">Normal");
      lcd.setCursor(0, 1);
      lcd.print(" Mirrored");
      delay(15);
    }
    else if(rPressed == HIGH){
      lcd.setCursor(0, 0);
      lcd.print(" Normal");
      lcd.setCursor(0, 1);
      lcd.print(">Mirrored");
    }
    else{
      lcd.setCursor(0, 0);
      lcd.print(" Normal");
      lcd.setCursor(0, 1);
      lcd.print(" Mirrored");
    }
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print(lStrip);
    lcd.setCursor(0, 1);
    lcd.print(rStrip);
  }
}
