# keypad-unlock
Code for Keypad unlock
#include <Password.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, A3, A2, A1, A0);
Password password = Password( "1111" );

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

  pinMode(9, OUTPUT);
  
  Serial.begin(9600);
   keypad.addEventListener(keypadEvent);
   lcd.begin(16, 2);
   lcd.print("Please Enter Password:");
   lcd.setCursor(0, 1);
}
  
void loop(){
  
  char key = keypad.getKey();
  keypad.getKey();
  
  if (key){
    
    lcd.print(key);
    
    
  }
  
  
}

void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
  
  Serial.println(eKey);
  switch (eKey){
    case '*':
    pwdcheck();
    break;
    
    case '#': 
   password.reset();
   lcd.clear();
    lcd.print("Please Enter Password:");
    lcd.setCursor(0, 1);
   
    
    default:
    password.append(eKey);
     }
  }
}

void pwdcheck(){
  if (password.evaluate()){
    lcd.print("Success Wellcome to Robo Inventors");
   
  }else{
    lcd.print("Sorry Password is Wrong");
    digitalWrite(9,HIGH);
   
  }
}
