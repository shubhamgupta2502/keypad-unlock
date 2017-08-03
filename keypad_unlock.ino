#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Password.h>
LiquidCrystal lcd(12, 11, A3, A2, A1, A0);

Password password = Password( "1234" );

byte maxPasswordLength = 4; 
byte currentPasswordLength = 0;
const byte ROWS = 4;
const byte COLS = 3; 

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; 
byte colPins[COLS] = {8, 7, 6}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
   pinMode(9, OUTPUT);// yellow
  pinMode(10, OUTPUT);// red
  Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.print("Enter Password:");
   lcd.setCursor(0, 1);
}

void loop(){
   char key = keypad.getKey();
   if (key != NO_KEY){
      delay(60); 
      switch (key){
      case '*': checkPassword(); 
      break;
      case '#': resetPassword();
       lcd.clear();
    lcd.print("Enter Password:");
    password.reset();
    lcd.setCursor(0,1);
      break;
      default: processNumberKey(key);
      }
   }
}

void processNumberKey(char key) {
   lcd.print(key);
   currentPasswordLength++;
   password.append(key);
   if (currentPasswordLength == maxPasswordLength) {
      checkPassword();
   } 
}

void checkPassword() {
   if (password.evaluate()){
      lcd.print(" OK.");
       digitalWrite(9,HIGH);
    delay(2000);
    digitalWrite(9,LOW);
      
   } else {
      lcd.print(" Sorry Wrong passwowrd!");
      digitalWrite(10,HIGH);
    delay(2000);
    digitalWrite(10,LOW);
      
   } 
   resetPassword();
}

void resetPassword() {
   password.reset(); 
   currentPasswordLength = 0; 
}

