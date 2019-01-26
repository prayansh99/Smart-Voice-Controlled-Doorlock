
/*
 * 4,5,6,7 to D4,D5,D6,D7
 * A TO VCC, K TO GND
 * VSS TO GND, VDD TO VCC
 * V0 TO VARIABLE
 * RW TO GND
 * RS TO 8
 * EN TO 9
 * ENABLE HIGH
 * * :::::::::::::::::Servo::::::::::::::::
 * Brown - GND
 * RED - VCC
 * Orange - Signal(15)
 */
  int flag = 0;
 #include<LiquidCrystal.h>                      //For LCD
 #include<Servo.h>                              //For Servo
 #include<SoftwareSerial.h>                     //For HC-05 u can also connect directly to Rx and Tx port

 LiquidCrystal lcd(8,9,4,5,6,7);                // RS, E, D4, D5, D6, D7
 Servo servo;
 String voice;


                                   //Control variable
void setup() 
{ pinMode(3,OUTPUT);
  digitalWrite(3,LOW); 
  Serial.begin(9600);//to begin transmission btw arduino and bluetooth
  lcd.begin(16,2);
  Serial.println("Hey");
  lcd.setCursor(0,0);                        
  lcd.print(" Status - LOCK");                  //By default Lockmode
  servo.attach(2);
  lcd.setCursor(0,1);
  lcd.print("Plz Speak Code");
  servo.write(0);
}

void loop() {
  voice="";
    while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = Serial.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  }  
  if (voice.length() > 2) {
    Serial.println(voice);
    if(voice=="*hello")
    {
      if(flag==1)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Already OPENED");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Plz Speak The");
        lcd.setCursor(0,1);
        lcd.print("    Password");
        voice="a";
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PASSWORD - MATCH");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("    OPENING");
        servo.write(160);
        delay(3000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("    WELCOME");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0,0);
        
        lcd.print(" Plz Speak the");
        lcd.setCursor(0,1);
        lcd.print("    Password");
        flag=1;
      }
    }                                                                                                                                                                                                                                                                                                                                                                                                                         
    else if(voice=="*done")
    {
      if(flag==0)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Already CLOSED");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Plz Speak the");
        lcd.setCursor(0,1);
        lcd.print("    Password");
        voice="a";
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PASSWORD - MATCH");
        servo.write(0);
        delay(3000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("    CLOSING");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Plz Speak the");
        lcd.setCursor(0,1);
        lcd.print("    Password");
        flag=0;
        voice="a";
      }
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error Try Again!");  
    }
  }
}

