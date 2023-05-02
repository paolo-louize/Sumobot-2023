#include <Ultrasonic.h>

//START Var
  Ultrasonic USsense(A0,A1);
   
  int LineSenseFL = 9;
  int LineSenseFR = 8;
  int LineSenseBL = 13;
  int LineSenseBR = 12;

  int ProxL = 10;
  int ProxR = 11;

  int ENA = 2;
  int MtrL1 = 4;
  int MtrL2 = 3;
  int MtrR1 = 5;
  int MtrR2 = 6;
  int ENB = 7;
  
  int USsenseDst;
  int LineTrackFL, LineTrackFR, LineTrackBL, LineTrackBR;
  int PrxL, PrxR;
//END Var

//START Func
  void Forward(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, 1);
    digitalWrite(MtrL2, LOW);
    digitalWrite(MtrR1, HIGH);
    digitalWrite(MtrR2, LOW);
  }

  void Backward(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH);
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, HIGH);
  }

  void TurnL(){
    analogWrite(ENA, 120);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH);
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, HIGH);
  }

  void TurnR(){
    analogWrite(ENA, 120);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH);
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, HIGH);
  }

  void CounterClockWise(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH);
    digitalWrite(MtrR1, HIGH);
    digitalWrite(MtrR2, LOW);
  }

  void ClockWise(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, HIGH);
    digitalWrite(MtrL2, LOW);
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, HIGH);
  }

  void Atk(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, HIGH);
    digitalWrite(MtrL2, LOW);
    digitalWrite(MtrR1, HIGH);
    digitalWrite(MtrR2, LOW);
  }

  void Stp(){
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, LOW);
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, LOW);
  }
//END Func

//START Design
  void setup() {
    
    pinMode(LineSenseFL,INPUT);
    pinMode(LineSenseFR,INPUT);
    pinMode(LineSenseBL,INPUT);
    pinMode(LineSenseBR,INPUT);
    pinMode(ProxL,INPUT);
    pinMode(ProxR,INPUT);
    pinMode(ENA,OUTPUT);
    pinMode(MtrL1,OUTPUT);
    pinMode(MtrL2,OUTPUT);
    pinMode(MtrR1,OUTPUT);
    pinMode(MtrR2,OUTPUT);
    pinMode(ENB,OUTPUT);

    Serial.begin(9600);

    delay(3000);
    ClockWise();
    delay(2550);
  }

  void loop() {
    USsenseDst = USsense.read(CM);
    if (USsenseDst>80){
      USsenseDst = 0;
    }
    
  
    LineTrackFL = digitalRead(LineSenseFL);
    LineTrackFR = digitalRead(LineSenseFR);
    LineTrackBL = digitalRead(LineSenseBL);
    LineTrackBR = digitalRead(LineSenseBR);
    PrxL = digitalRead(ProxL);
    PrxR = digitalRead(ProxR);

    if(LineTrackFL == 0 && LineTrackFR == 0 && LineTrackBL == 0 && LineTrackBR == 0){
      Stp();
      Serial.println("Stop");
    }
    else if(LineTrackFL == 0 && LineTrackFR == 0){
      Backward();
      delay(300);
      ClockWise();
      delay(800);
      Serial.println("Backward");
    }
    else if(LineTrackBL == 0 && LineTrackBR == 0){
      Forward();
      delay(1000);
      Serial.println("Forward");
    }
    else if(LineTrackFL == 0){
      TurnL();
      Serial.println("Backward Left");
    }
    else if(LineTrackFR == 0){
      TurnR();
      Serial.println("Backward Right");
    }
    else if(LineTrackBL == 0){
      TurnR();
      Serial.println("Forward Right");
    }
    else if(LineTrackBR == 0){
      TurnL();
      Serial.println("Forward Left");
    }
    else if(PrxL == 0){
      ClockWise();
      delay(1200);
      Serial.println("Clockwise");
    }
    else if(PrxR == 0){
      CounterClockWise();
      delay(1200);
      Serial.println("Counter Clockwise");
    }
    
    else if(USsenseDst > 0){
      Atk();
      Serial.println("Attack");
    }

    else{
      Forward();
      Serial.println("No Detect");
    }
  }

//END Design
