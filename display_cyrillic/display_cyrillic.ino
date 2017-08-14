
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_1602_RUS.h>

LiquidCrystal_1602_RUS lcd(12, 11, 5, 4, 3, 2);

void setup()
{

  lcd.begin(16, 2);

  lcd.print(L"Кирилица тест");
  lcd.setCursor(0,1);

  lcd.print(L"Радо ");

}

void loop() {

}

