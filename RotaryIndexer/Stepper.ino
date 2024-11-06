

  
   

int StepperSpeedValue;



void StepNext(int DivCount){

  // Serial.println(DivCount);
  for(long i = 0L ; i < STEPS360/(long)DivCount;i++){
    stepStepper(FWD);
    //Serial.println(i);
    //delay(50);
  }
   
  
}

// Set stepper speed
void SetStepperSpeed(int value){
  StepperSpeedValue = value;
}


// This function sets the direction and makes a step pulse
void stepStepper(bool dir){
  if(dir){
    digitalWrite(DIR, HIGH); //Serial.println("Step fwd");
  }else{
    digitalWrite(DIR, LOW); //Serial.println("Step bwd");
  } 
  delayMicroseconds(500);
  digitalWrite(STEP, LOW);
  delayMicroseconds(500);
  digitalWrite(STEP,HIGH);
  delayMicroseconds(StepperSpeedValue);

}

