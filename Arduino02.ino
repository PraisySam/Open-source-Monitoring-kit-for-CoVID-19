#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int A2_input = 13;

void setup () {
Serial.begin(9600);
pinMode(A2_input,INPUT);
lcd.begin(16,2); 
}

void loop () {
  lcd.clear();
  int warning = digitalRead(A2_input);
  if (warning == 1) {
    lcd.print("WARNING DETECTED");
    lcd.setCursor(0,1);
    lcd.print("CALLING HELP");
    delay(400);}
  
  if(warning == 0) {
    lcd.print("  PATIENT SAFE");
    lcd.setCursor(0,1);
    lcd.print(" SENSORS OPTIMAL");
    delay(400);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  DEVELOPED BY");
    lcd.setCursor(0,1);
    lcd.print(" Team Twinni");
    delay(400);}
}
