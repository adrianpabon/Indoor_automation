#include <virtuabotixRTC.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int trigger = 3;
// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);
LiquidCrystal_I2C lcd(0x27,16,2); 

void setup() {
  pinMode(trigger, OUTPUT);
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  myRTC.setDS1302Time(10, 22, 22, 7, 22, 6, 2023);
}

void loop() {
  // This allows for the update of variables for time or accessing the individual elements.
  myRTC.updateTime();
  // Start printing elements as individuals
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
  // Delay so the program doesn't print non-stop

  lcd.setCursor(0, 0);
  lcd.print(myRTC.hours);
  lcd.print(":");

  lcd.setCursor(3, 0);
  lcd.print(myRTC.minutes);
  lcd.print(":");

  lcd.setCursor(6, 0);
  lcd.print(myRTC.seconds);

  delay(1000);

  if (myRTC.hours < 24 && myRTC.hours >= 6) {
    digitalWrite(trigger, LOW);
    lcd.setCursor(0, 1);
    lcd.print("ON");
  } else {
    digitalWrite(trigger, HIGH);  // turn of pin3.
    lcd.setCursor(0, 1);
    lcd.print("OFF");
  }
}

 