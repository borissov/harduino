
#define INPUT_BUFFER_SIZE 10
char inData[INPUT_BUFFER_SIZE]; // Allocate for choice string
char inChar; // Buffer for every char
byte index = 0; // using for cycles


int brightness = 0;    // how bright the LED is
int fadeAmount = 5; 



void setup()
{ 
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(115200);
//   while (!Serial) //waiting serial connection
//  {
//    ;
//  }
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
    //show choice
  //  Serial.println(inData);
  
    //switch choices
      switch (inData[0]) 
    {
      case 'y':
        Serial.println("Yes");
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        break;
      case 'n':
        Serial.println("No");
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
        break;
      default: 
        Serial.println("Invalid Choice");
        break;
    }
    //Null Choice Buffer
    for (index = 0; index < INPUT_BUFFER_SIZE; index++)
    {
      inData[index] = '\0';
    }
    index = 0; 
}

void otherFunctionality()
{
  analogWrite(13, brightness);
  brightness = brightness + fadeAmount; 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  } 
  delay(30);       
}

void loop()
{ 
  if(Serial.available())
  {
     menu();
  }else{ 
   //  otherFunctionality();
  }
}
