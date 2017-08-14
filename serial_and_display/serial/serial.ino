
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define INPUT_BUFFER_SIZE 33
char inData[INPUT_BUFFER_SIZE]; // Allocate for choice string
char inChar; // Buffer for every char
byte index = 0; // using for cycles

void setup()
{ 
  lcd.begin(16, 2);
  lcd.print("Display Start");

  Serial.begin(115200);
}

void menu()
{
     //Clear 'ping' from input buffer
     while(Serial.available() > 0)
     {     
       Serial.read(); 
     }
 
     Serial.println("ready");
     while (Serial.available() == 0) {
      ;  // wait for user input
     }
     while (Serial.available() > 0) // Don't read unless                                 
     {
      
      if (index < INPUT_BUFFER_SIZE) // One less than the size of the array
      {
        inChar = Serial.read(); // Read a character  
        inData[index] = inChar; // Store it
        index++; // Increment where to write next
        inData[index] = '\0'; // Null terminate the string
      }
     }
    
    for (index = 0; index < INPUT_BUFFER_SIZE; index++)
    {
      if(index<=15)
      {
        lcd.setCursor(index, 0);
      }
      else
      {
        lcd.setCursor((index-16), 1);
      }
      lcd.print(inData[index]);
    }
    

    //Null Choice Buffer
    for (index = 0; index < INPUT_BUFFER_SIZE; index++)
    {
      inData[index] = '\0';
    }
    index = 0; 
}

void loop() {
  if(Serial.available())
  {
     menu();
  }
  else
  { 
    //lcd.scrollDisplayRight();
    // wait a bit:
    //delay(150);
  }
}

