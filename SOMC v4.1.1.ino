// Quickstop.pde
// -*- mode: C++ -*-
//
// Check stop handling.
// Calls stop() while the stepper is travelling at full speed, causing
// the stepper to stop as quickly as possible, within the constraints of the
// current acceleration.
//
// Copyright (C) 2012 Mike McCauley
// $Id:  $

#include <AccelStepper.h>
#include <elapsedMillis.h>

elapsedMillis printtime;
// Define a stepper and the pins it will use
int limitz = 25, limitx = 22, limity = 23, limitry = 24;
AccelStepper stepper4(AccelStepper::FULL2WIRE, 6, 7);   // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper1(AccelStepper::FULL2WIRE, 2, 3);   // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(AccelStepper::FULL2WIRE, 17, 5);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper3(AccelStepper::FULL2WIRE, 8, 9);   // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
int curpos = 1000;
int maxposz = 1630418;
int minposz = 0;
boolean func1 = false;
boolean f1 = false, f21 = false, f2 = false, f3 = false, f4 = false;
int buz = 10;



long signed valz;
int valx;
int valy;
int valry;
void setup() {
  pinMode(limitz, INPUT);
  pinMode(limity, INPUT);
  pinMode(limitx, INPUT);
  pinMode(limitry, INPUT);
  stepper4.setMaxSpeed(60000.0);
  stepper4.setAcceleration(12000.0);


  stepper3.setMaxSpeed(20000.0);
  stepper3.setAcceleration(500.0);

  stepper2.setMaxSpeed(20000.0);
  stepper2.setAcceleration(500.0);


  stepper1.setMaxSpeed(20000.0);
  stepper1.setAcceleration(500.0);

  Serial.begin(115200);
  pinMode(buz, OUTPUT);


  stepper1.setSpeed(10000);
  stepper2.setSpeed(1000);
  stepper3.setSpeed(1000);
  stepper4.setSpeed(50000);
}
void data_out() {
  if (printtime >= 100) {
    printtime = 0;
    float m4Speed = stepper4.speed();
    float m3Speed = stepper3.speed();
    float m2Speed = stepper2.speed();
    float m1Speed = stepper1.speed();
    Serial.print("spd step1: ");
    Serial.print(m1Speed);
    Serial.print(" ");
    Serial.print("pos step1: ");
    Serial.print(stepper1.currentPosition());
    Serial.print(" ");
    Serial.print("spd step2: ");
    Serial.print(m2Speed);
    Serial.print(" ");
    Serial.print("pos step2: ");
    Serial.print(stepper2.currentPosition());
    Serial.print(" ");
    Serial.print("spd step3: ");
    Serial.print(m3Speed);
    Serial.print(" ");
    Serial.print("pos step3: ");
    Serial.print(stepper3.currentPosition());
    Serial.print(" ");
    Serial.print("spd step4: ");
    Serial.print(m4Speed);
    Serial.print(" ");
    Serial.print("pos step4: ");
    Serial.println(stepper4.currentPosition());
  }
}
void homeposry() {

  if (digitalRead(limitry) == HIGH) {
    stepper1.setSpeed(0.00);
    stepper1.runSpeed();
    stepper1.stop();
    data_out();
    while (f21 == true) {
      int val = stepper1.currentPosition();
      data_out();
      stepper1.moveTo(1200);
      stepper1.run();
      if (stepper1.currentPosition() == 1200) {
        f21 = false;
        break;
      }
    }
    if (f21 == false) {
      stepper1.setCurrentPosition(0);
    }
    while (f2 == false) {
      if (digitalRead(limitry) == HIGH) {

        data_out();
        stepper1.setSpeed(-1200);
        stepper1.runSpeed();
      } else {

        stepper1.setCurrentPosition(0);
        f2 = true;
        f21 = true;
      }
    }


  } else {

    data_out();
    stepper1.setSpeed(-700);
    stepper1.runSpeed();
  }
}

void homeposy() {

  if (digitalRead(limity) == HIGH) {
    stepper2.setSpeed(0.00);
    stepper2.setCurrentPosition(0);
    data_out();
  } else {

    data_out();
    stepper2.setSpeed(-2000);
    stepper2.runSpeed();
  }
}
void homeposx() {
  if (digitalRead(limitx) == HIGH) {
    stepper3.setSpeed(0.00);
    stepper3.setCurrentPosition(0);
    data_out();
  } else {

    data_out();
    stepper3.setSpeed(-2000);
    stepper3.runSpeed();
  }
}
void homeposz() {
  data_out();
  stepper4.runSpeed();
  if (digitalRead(limitz) == HIGH) {
    stepper4.setSpeed(0.00);

    stepper4.setCurrentPosition(0);
  }

  stepper4.setSpeed(-20000);
  stepper4.runSpeed();
}

void loop() {

  stepper4.moveTo(valz);
  stepper4.run();
  stepper3.moveTo(valx);
  stepper3.run();
  stepper2.moveTo(valy);
  stepper2.run();
  stepper1.moveTo(valry);
  stepper1.run();
  if (Serial.available() > 0) {      //check serial value
    char incomeing = Serial.read();  //read serial value

    if (incomeing == 'W') {
      valz -= 5000;
    }

    else if (incomeing == 'Q') {
     
      valz += 5000;
    }


    if (incomeing == 'E') {
     
      valx -= 1000;
    }

    else if (incomeing == 'R') {

      valx += 1000;
    }

    if (incomeing == 'K') {
      valy -= 1000;
    }

    else if (incomeing == 'Y') {

      valy += 1000;

    } else if (incomeing == 'U') {

      valry += 1000;

    } else if (incomeing == 'I') {

      valry += 1000;
    }
    if (incomeing == 'B') {
      func1 = true;
      while (func1 == true) {

        homeposry();
        homeposz();
        homeposx();
        homeposy();
        if (Serial.available() > 0) {      //check serial value
          char incomeing = Serial.read();  //read serial value

          if (incomeing == 'J') {
            func1 = false;
          }
        }
      }
    }
  }
}
