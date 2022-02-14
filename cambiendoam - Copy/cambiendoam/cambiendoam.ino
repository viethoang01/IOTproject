#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define sensor A0
#define led 13
#define motor 8
#define button 12
int buttonState = 0;
#define button1 11 //
int buttonState1 = 0;
int lastButtonState = 0;
int lastButtonState1 = 0;
int count = 0;
int count1 = 0;
//.................................................
void setup() {
  Serial.begin(9600);
  lcd.init();
  pinMode(sensor, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  
  lcd.setCursor(0, 1);
  lcd.print("Do am dat:    %");
}
//.................................................
void loop() {
  buttonState = digitalRead(button);
  buttonState1 = digitalRead(button1);
  int value = analogRead(sensor);
  value = map(value, 0, 1023, 0, 100);
  lcd.setCursor(11, 1);
  lcd.print(value);
  if (buttonState != lastButtonState){   
    if(buttonState == HIGH){
      count++;
    }
    delay(50);
  }
  if (buttonState1 != lastButtonState1){   
    if(buttonState1 == HIGH){
      count1++;
    }
    delay(50);
  }
  lastButtonState = buttonState;
  lastButtonState1 = buttonState1;
  if(count % 2== 0){    
      Serial.println("che do khong auto");
      lcd.setCursor(0, 0);
      lcd.print("---- NO AUTO ----");
          
      if(count1 %2 == 0){  
        Serial.println("MOTOR ON");
        digitalWrite(led, HIGH);
        digitalWrite(motor, HIGH);
        lcd.setCursor(0, 3);
        lcd.print("MOTOR ON -noAuto-");
      }else{
        Serial.println("MOTOR OFF");
        digitalWrite(led, LOW);
        digitalWrite(motor, LOW);
        lcd.setCursor(0, 3);
        lcd.print("MOTOR OFF -noAuto-");
      }
     
      
    
  }else{
    Serial.println("che do auto");
    lcd.setCursor(0, 0);
    lcd.print("---- AUTO ----");
    if (value < 100) {
      lcd.setCursor(13, 1);
      lcd.print(' ');
    } else if (value < 10) {
      lcd.setCursor(12, 1);
      lcd.print(' ');
    }
    if (value > 70) {
      Serial.println("Do am binh thuong");
      lcd.setCursor(0, 2);
      lcd.print("    Do am dat ok    ");
      digitalWrite(led, LOW);
      digitalWrite(motor, LOW);
      lcd.setCursor(0, 3);
      lcd.print("MOTOR OFF -Auto-");
    }
    if(value < 40) {
      Serial.println("Dat kho thieu nuoc");
      lcd.setCursor(0, 2);
      lcd.print(" Dat kho thieu nuoc ");
      digitalWrite(led, HIGH);
      digitalWrite(motor, HIGH);
      lcd.setCursor(0, 3);
      lcd.print("MOTOR ON -Auto-");
    }
  }
}
