/***************************************
*
* Sytem to contol a index table
* You can rotete max 360 steps
*
* Use Center key to browse the menu
* - Adjust position 
* - Number of div?
* - Run, press button (Right)
*
*   How to use:
*   Adjust rotary table
*   Select how many gears
*   Run rotary table one step to next gear position
*   Go sto start position after last gear position
*   Made by Håkan Tore´n 2024
***************************************/
#define VERSION "V241103"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



// stepper 200 step gear 1:50  -> 200 * 50 10000 step
// if DivCount = 50  -> 10000 / 50 = 200 step
 
// Define stepper speed (delay between steps)

#define STEPPER_SPEED 1000    // Delay between steps
#define MaxDiv 360            // 360 degrees
  
    
#define UP_BUTTON 4
#define DOWN_BUTTON 5
#define LEFT_BUTTON 6
#define RIGHT_BUTTON 7
#define SELECT_BUTTON 8

#define STEP    2                       // Board harware pin, Step signal
#define DIR     3                      // Board harware pin, Direction signal
#define ENABLE  13                       // Board harware pin, Enable signal

 #define STEPS360 12000L                 // Number of steps 360 degrees

 #define FWD true
 #define BWD false

    
    
enum{
  NONE,
  SELECT,
  RIGHT,
  LEFT,
  UP,
  DOWN
};


enum{
  ADJUST,
  DIV,
  RUN,
  HOME
};


// Different menues
enum{
  MENY_STARTUP,
  MENY_ADJUST,
  MENY_DIV,
  MENY_RUN
};

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int State = ADJUST;
int MenyIndex = MENY_STARTUP; //MENY_ADJUST;  // Start menue, adjust rotary table
int DivCount = 2;             // Start value 2 gears (180 degrees)
int RunCount = 1; //3;

bool StartUp = true;

void setup() {
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(SELECT_BUTTON, INPUT_PULLUP);

  digitalWrite(ENABLE, true);

  SetStepperSpeed(STEPPER_SPEED);

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.begin(16, 2);                      // set up the LCD's number of columns and rows
  lcd.clear();                           // Clear LCD
  lcd.setCursor(0,0);                    // Set cursor to x=0 and y=0
  lcd.print("Digital Index ");           // Print text on LCD
  lcd.setCursor(0,1);
  lcd.print("Table ");
  lcd.setCursor(7,1);
  lcd.print(VERSION);
  delay(2000);

  //Serial.begin(115200);
}

void loop() { 

int Key;

  if(StartUp){
    MenyIndex = MENY_ADJUST;
    Key = SELECT;
    StartUp = false;
  }else{
    Key = GetKey(); 
  }
  
 switch(Key){  
  case SELECT:
    switch(MenyIndex){
      case MENY_ADJUST:
        lcd.clear();  
        lcd.setCursor(0,0);
        lcd.print("Adjust position"); 
        State = ADJUST;
        break;
      case MENY_DIV:
          lcd.clear();   
          lcd.setCursor(0,0);
          lcd.print("Number of div?"); 
          lcd.setCursor(0,1);
          lcd.print(DivCount);
          State = DIV;
          break; 
      case MENY_RUN:
        lcd.clear();   
        lcd.setCursor(0,0);
        lcd.print("Run,press button");  
        State = RUN;
        break; 
    }
    if(MenyIndex >= MENY_RUN){
      MenyIndex = MENY_ADJUST;
    }else{
      MenyIndex++;
    }
    break;
  case RIGHT:
    if(State == ADJUST){
      for(int i = 0; i < 10; i++){
        stepStepper(FWD);
      }
    }else if(State == DIV){  
      if(DivCount == MaxDiv){
        DivCount = 1;
      }
      DivCount++;
      lcd.setCursor(0,1);
      lcd.print("   ");
      lcd.setCursor(0,1);
      lcd.print(DivCount);  
    }else if(State == RUN){
      if(RunCount < DivCount){
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print(RunCount + 1); 
        StepNext(DivCount);
        lcd.setCursor(0,1);
        lcd.print(RunCount + 1);
        lcd.print(", Next?");
        RunCount++;
        if(RunCount == DivCount){
          lcd.clear();
          lcd.setCursor(0,0); 
          lcd.print("End,press button"); 
          lcd.setCursor(0,1);
          lcd.print("to Homing");
          State = HOME; 
        }
      }
    }else if(State == HOME){
      StepNext(DivCount);
      lcd.clear();   
      lcd.setCursor(0,0);
      lcd.print("Number of div?"); 
      lcd.setCursor(0,1);
      lcd.print(DivCount); 
      RunCount = 1;
      State = DIV;
      MenyIndex = MENY_RUN;
    }
    break;
  case LEFT:
    if(State == ADJUST){
      for(int i = 0; i < 10; i++){
        stepStepper(BWD);
      }
    }else if(State == DIV){
      if(DivCount <= 2){
        DivCount = MaxDiv;  
      }else{
        DivCount--;
      }
      lcd.setCursor(0,1);
      lcd.print("   ");
      lcd.setCursor(0,1);
      lcd.print(DivCount);  
    }
    break;
  case UP:
    if(State == ADJUST){
      for(int i = 0; i < 100; i++){
        stepStepper(FWD);
      }
    }else if(State == DIV){
      if(DivCount <= MaxDiv - 10){
        DivCount+=10;
      }else{
        DivCount = DivCount - (MaxDiv - 10);
      }
      lcd.setCursor(0,1);
      lcd.print("   ");
      lcd.setCursor(0,1);
      lcd.print(DivCount);  
    }
    break;
  case DOWN:
     if(State == ADJUST){
      for(int i = 0; i < 100; i++){
        stepStepper(BWD);
      }
     }else if(State == DIV){
      if(DivCount > 10){
         DivCount -= 10;  
      }else{
        DivCount = MaxDiv - DivCount;
      }
      lcd.setCursor(0,1);
      lcd.print("   ");
      lcd.setCursor(0,1);
      lcd.print(DivCount);  
    }
    break;
   
  
 }

 
}


