// MOTOR & STEPPER MOTOR Series :: http://fitrox.lnwshop.com
// EP.7 A4988 1-8Step Motor Driver w/o Library Example

int dirPin = 2;                         // pin 2 กำหนดเป็น Direction pin
int stepPin = 3;                        // pin 3 กำหนดเป็น Step pin
int stepsPerRev = 1600;                 // กำหนด step/รอบ เป็น 1600 (1/8 Step Mode)
int limitz = 4;
int hight;
int x = 0, b = 0;
boolean f1 = false;
boolean f2 = false;

boolean f3 = false;
void setup() {
  // StepPin และ dirPin เป็น OUTPUT
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(limitz, INPUT);
  Serial.begin(9600);

  
}

void loop() {
  // ให้มอเตอร์หมุนทิศตามเข็มนาฬิกาโดยให้ Direction เป็น HIGH


  // Pulse 1 ลูก กว้าง 4000 us
  // หน่วงเวลา 2 วินาที
  // หน่วงเวลา 2 วินาที
  if (digitalRead(limitz) == HIGH) {
    digitalWrite(dirPin, HIGH);

    // สร้าง Pulse ให้มอเตอร์ ซึ่ง 1 ลูกมอเตอร์จะหมุน 1 Step ต้องการ 1 รอบ ต้องสร้าง Pulse 1600 ลูก
    for (int i = 0; i < 8000; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(100);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(100);
      // Pulse 1 ลูก กว้าง 4000 us
    }

    f1 = true;
    while (f1 == true) {
      digitalWrite(dirPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
      if (digitalRead(limitz) == HIGH) {
        f2 = true;

        while (f2 == true) {
          digitalWrite(dirPin, LOW);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500);
          hight = 0;

        }
      }
    }
  }
  else {


    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(70);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(70);

  }
}



void infy_up() {
  digitalWrite(dirPin, HIGH);

  digitalWrite(stepPin, HIGH);
  delayMicroseconds(70);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(70);

}

void infy_down() {
  digitalWrite(dirPin, LOW);

  digitalWrite(stepPin, HIGH);
  delayMicroseconds(70);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(70);

}

 
