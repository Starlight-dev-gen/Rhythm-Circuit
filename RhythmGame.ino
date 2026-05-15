#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
const int lButton = 2;
int lPressed = 0;
const int rButton = 3;
int rPressed = 0;
bool gameRunning = false;
String lStrip = "";
String rStrip = "";

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

  if (!gameRunning){
    if (lPressed == HIGH && rPressed == HIGH){
      gameRunning = true;
    }
  }
  else{
    lcd.setCursor(0, 0)
    lcd.print(lStrip);
    lcd.setCursor(0, 1);
    lcd.print(rStrip);
  }
}
