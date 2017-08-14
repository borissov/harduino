
#include <Arduino.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Create a set of new characters
byte smiley[8] = {
    B00000, 
    B01010,
    B00000,
    B00000,
    B10001,
    B01110,
    B00000,
    B00000
};

byte heart_h[8] = {
    B00000,
    B00000,
    B01010,
    B10101,
    B10001,
    B01010,
    B00100, 
    B00000
}; 
byte heart_f[8] = {
    B00000,
    B00000,
    B01010,
    B11111,
    B11111,
    B01110,
    B00100, 
    B00000
}; 
byte ohm[8] = {
    B00000,
    B01110,
    B10001,
    B10001,
    B10001,
    B01010,
    B01010, 
    B11011
}; 
byte rect[8] = {
    B11111,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B10001,
    B11111
};
byte arrow_u[8] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B00100,
    B00100,
    B00100, 
    B00100
}; 
byte arrow_d[8] = { 
    B00100,
    B00100,
    B00100,
    B00100, 
    B00100, 
    B11111,
    B01110,
    B00100
}; 
byte diamond[8] = {
    B00000,
    B00100,
    B01010,
    B10001, 
    B01010,
    B00100,
    B00000,
    B00000 
}; 
int z=1;
void setup() 
{
    lcd.begin(16,2); // Initialize LCD 2x16

    lcd.createChar (0, smiley); // load smiley to memory 0
    lcd.createChar (1, heart_h); // load heart_h to memory 1
    lcd.createChar (2, heart_f); // load heart_f to memory 2
    lcd.createChar (3, ohm); // load ohm to memory 3
    lcd.createChar (4, rect); // load rect to memory 4
    lcd.createChar (5, arrow_u); // load arrow_u to memory 5
    lcd.createChar (6, arrow_d); // load arrow_d to memory 6
    lcd.createChar (7, diamond); // load diamond to memory 7

    lcd.clear(); //clear the screen
    lcd.setCursor(0,0); //set cursor to upper left corner

    lcd.print(char(0)); //display a smiley
    lcd.print(char(1)); //display a hollow heart
    lcd.print(char(2)); //display a filled heart
    lcd.print(char(3)); //display a ohm
    lcd.print(char(4)); //display a rectangle
    lcd.print(char(5)); //display a arrow
    lcd.print(char(6)); //display a rectangle
    lcd.print(char(7)); //display a arrow
}

void loop() {
    z= z +1;
    lcd.setCursor(0,1); //set cursor to bottom left second line
    lcd.print(char(0));
    lcd.print(char(z)); 
    lcd.print(char(3));
    lcd.print(char(0));
    if (z==2)z=0;
    delay(500);

}
