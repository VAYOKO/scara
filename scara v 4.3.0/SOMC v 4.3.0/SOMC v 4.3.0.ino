// 6430 = half round 
// 12810

#include <elapsedMillis.h>

#include <AccelStepper.h>
elapsedMillis printtime;
// Define a stepper and the pins it will use
int limitz = 15, limitx = 16, limity = 17, limitry = 18;
AccelStepper stepper1(AccelStepper::FULL2WIRE, 24, 25);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(AccelStepper::FULL2WIRE, 26, 27);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper3(AccelStepper::FULL2WIRE, 28, 29);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper4(AccelStepper::FULL2WIRE, 22, 23);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

int curpos = 1000;
int maxposz = 1630418;
int minposz = 0;
boolean func1 = false;
boolean f1 = false, f21 = false, f2 = false, f3 = false, f4 = false;
int buz = 14;


//unlock limit protection

boolean unlock_limit[4] = { false, false, false, false };
//unlock max limit protection
boolean unlock_maxlimit[4] = { false, false, false, false };

//solf limit each axis
long maxlimit_y = -7000;



  long signed valz[10];
int valx[10];
int valy[10];
int valry[10];
int pos1, pos2, pos3;
long pos4;
#include <LiquidCrystal.h>
//LCD pin to Arduino Example By ArduinoAll
const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;
LiquidCrystal lcd(pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);
int val = 10;
int rec_count = 0;
long distance;
void setup() {
  lcd.begin(16, 2);
  pinMode(limitz, INPUT);
  pinMode(limity, INPUT);
  pinMode(limitx, INPUT);
  pinMode(limitry, INPUT);
  stepper4.setMaxSpeed(100000.0);
  stepper4.setAcceleration(10000.0);    // setAcceleration อัตราเร่ง 


  stepper3.setMaxSpeed(20000.0);
  stepper3.setAcceleration(500.0);

  stepper2.setMaxSpeed(20000.0);
  stepper2.setAcceleration(500.0);


  stepper1.setMaxSpeed(20000.0);
  stepper1.setAcceleration(500.0);

  Serial.begin(250000);
  pinMode(buz, OUTPUT);
  lcd.setCursor(0, 1);

  delay(400);

  delay(400);
  tone(buz, 5);
  delay(400);
  tone(buz, 10);
  delay(400);
  tone(buz, 15);
  delay(400);
  noTone(buz);
  lcd.clear();
  stepper1.setSpeed(10000);
  stepper2.setSpeed(1000);
  stepper3.setSpeed(1000);
  stepper4.setSpeed(80000);
}
void data_out() {
  if (printtime >= 100) {
    printtime = 0;
    int m4Speed = stepper4.speed();
    int m3Speed = stepper3.speed();
    int m2Speed = stepper2.speed();
    int m1Speed = stepper1.speed();
    pos1 = stepper1.currentPosition();
    pos2 = stepper2.currentPosition();
    pos3 = stepper3.currentPosition();
    pos4 = stepper4.currentPosition();
    Serial.print(rec_count, DEC);
    Serial.print(",");
    Serial.print(pos1, DEC);
    Serial.print(",");
    Serial.print(pos2, DEC);
    Serial.print(",");
    Serial.print(pos3, DEC);
    Serial.print(",");
    Serial.print(pos4, DEC);
    Serial.print(",");

    Serial.print(m1Speed, DEC);
    Serial.print(",");
    Serial.print(m2Speed, DEC);
    Serial.print(",");
    Serial.print(m3Speed, DEC);
    Serial.print(",");
    Serial.print(m4Speed, DEC);
    Serial.print(",");
    Serial.print(distance, DEC);

    Serial.print("\n");
  }
}
void limit_protect() {

  if ((digitalRead(limity) == HIGH) && (unlock_limit[0] == false)) {
    stepper2.stop();
    stepper2.setCurrentPosition(0);
  }
  //  if ((stepper2.currentPosition() >= maxlimit_y) && (unlock_maxlimit[0] == false)) {
  //    stepper2.stop();
  //   stepper1.setSpeed(0.00);
  //
  //  }
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
    stepper2.setSpeed(2000);
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

  if (digitalRead(limitz) == HIGH) {
    stepper4.setSpeed(0.00);

    stepper4.setCurrentPosition(0);
    stepper4.stop();
  }

  stepper4.setSpeed(-20000);
  stepper4.runSpeed();
}

void loop() {

  stepper4.moveTo(valz[rec_count]);
 
  stepper4.run();
  stepper3.moveTo(valx[rec_count]);
  stepper3.run();
  stepper2.moveTo(valy[rec_count]);
  stepper2.run();
  stepper1.moveTo(valry[rec_count]);
  stepper1.run();
 
  data_out();
  if (rec_count > 9) {

    rec_count = 0;
  }
  if (Serial.available() > 0) {      //check serial value
    char incomeing = Serial.read();  //read serial value




    if (incomeing == 'W') {
      valz[rec_count] -= distance;
      data_out();
    } else if (incomeing == '1') {
      distance = 500;
    } else if (incomeing == '2') {
      distance = 100;
    } else if (incomeing == '3') {
      distance = 1000;
    }
     else if (incomeing == '4') {
      distance = 12800;
    } else if (incomeing == 'Q') {
      data_out();
      valz[rec_count] += distance;
    }


    if (incomeing == 'E') {
      data_out();
      valx[rec_count] -= distance;
    }

    else if (incomeing == 'R') {
      data_out();
      valx[rec_count] += distance;
    }

    if (incomeing == 'K') {
      valy[rec_count] -= distance;
      data_out();
      unlock_limit[0] = true;
      unlock_maxlimit[0] = false;
    }

    else if (incomeing == 'Y') {
      data_out();
      valy[rec_count] += distance;
      unlock_limit[0] = false;
      unlock_maxlimit[0] = true;
    } else if (incomeing == 'U') {
      data_out();
      valry[rec_count] += distance;

    } else if (incomeing == 'I') {
      data_out();
      valry[rec_count] -= distance;
    } else if (incomeing == 'M') {
      rec_count += 1;

    } else if (incomeing == 'N') {
      rec_count -= 1;
    }
    if (incomeing == 'B') {
      func1 = true;
      while (func1 == true) {
        data_out();
        homeposry();
        homeposz();
        homeposx();
        homeposy();
        if (Serial.available() > 0) {      //check serial value
          char incomeing = Serial.read();  //read serial value

          if (incomeing == 'J') {
            func1 = false;
            lcd.clear();
          }
        }
      }
    }
  }
}
void lcd_home() {
  lcd.setCursor(0, 1);
  lcd.print("HOME POSITON");
}
void normal() {

  Serial.write(1);
}
void crash() {

  Serial.write(0);
}