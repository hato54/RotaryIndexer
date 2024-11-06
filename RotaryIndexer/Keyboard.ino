



int UpButtonState = HIGH;
int DownButtonState = HIGH;
int LeftButtonState = HIGH;
int RightButtonState = HIGH;
int SelectButtonState = HIGH;

int UpLastButtonState = HIGH; 
int DownLastButtonState = HIGH;
int LeftLastButtonState = HIGH;
int RightLastButtonState = HIGH;
int SelectLastButtonState = HIGH;

unsigned long UpLastButtonDebounceTime = 0;
unsigned long DownLastButtonDebounceTime = 0;
unsigned long LeftLastButtonDebounceTime = 0;
unsigned long RightLastButtonDebounceTime = 0;
unsigned long SelectLastButtonDebounceTime = 0;

unsigned int debounceDelay = 100;

int OldKey = NONE;

int GetKey() { 
  int Button = NONE;
  
 int reading = digitalRead(UP_BUTTON); 
 if(reading != UpLastButtonState) {
     UpLastButtonDebounceTime = millis();
  }

  if ((millis() - UpLastButtonDebounceTime) > debounceDelay) {
    if (reading != UpButtonState) {
      UpButtonState = reading;
      if(UpLastButtonState == LOW) {
        Button = UP;
        Serial.println("UP");
      }
    }
  }
  UpLastButtonState = reading;

 reading = digitalRead(DOWN_BUTTON); 
 if(reading != DownLastButtonState) {
     DownLastButtonDebounceTime = millis();
  }

  if ((millis() - DownLastButtonDebounceTime) > debounceDelay) {
    if (reading != DownButtonState) {
      DownButtonState = reading;
      if(DownLastButtonState == LOW) {
        Button = DOWN;
        Serial.println("DOWN");
      }
    }
  }
 DownLastButtonState = reading;

 reading = digitalRead(LEFT_BUTTON); 
 if(reading != LeftLastButtonState) {
     LeftLastButtonDebounceTime = millis();
  }

  if ((millis() - LeftLastButtonDebounceTime) > debounceDelay) {
    if (reading != LeftButtonState) {
      LeftButtonState = reading;
      if(LeftLastButtonState == LOW) {
        Button = LEFT;
        Serial.println("LEFT");
      }
    }
  }
  LeftLastButtonState = reading;

 reading = digitalRead(RIGHT_BUTTON); 
 if(reading != RightLastButtonState) {
     RightLastButtonDebounceTime = millis();
  }

  if ((millis() - RightLastButtonDebounceTime) > debounceDelay) {
    if (reading != RightButtonState) {
      RightButtonState = reading;
      if(RightLastButtonState == LOW) {
        Button = RIGHT;
        Serial.println("RIGHT");
      }
    }
  }
  RightLastButtonState = reading;

 reading = digitalRead(SELECT_BUTTON); 
 if(reading != SelectLastButtonState) {
     SelectLastButtonDebounceTime = millis();
  }

  if ((millis() - SelectLastButtonDebounceTime) > debounceDelay) {
    if (reading != SelectButtonState) {
      SelectButtonState = reading;
      if(SelectLastButtonState == LOW) {
        Button = SELECT;
        Serial.println("SELECT");
      }
    }
  }
  SelectLastButtonState = reading;

  delay(10);
  return(Button);
}
