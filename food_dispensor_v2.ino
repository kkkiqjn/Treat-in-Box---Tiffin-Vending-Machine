
#include <Servo.h>
Servo s1, s2, s3, s4, s5, s6;
int ut1 = 22, ue1 = 23, ut2 = 24, ue2 = 25, ut3 = 26, ue3 = 27, ut4 = 28, ue4 = 29, ut5 = 30, ue5 = 31, ut6 = 32, ue6 = 33;  //uLTRASONIC PINS
int sp1 = 2, sp2 = 3, sp3 = 4, sp4 = 5, sp5 = 6, sp6 = 7;                                                                    //SERVO PINS
int c;
int e1 = 8, e2 = 9, e3 = 10, e4 = 11, e5 = 12, e6 = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ut1, OUTPUT);  //  trigpin
  pinMode(ue1, INPUT);   //  echopin
  pinMode(ut2, OUTPUT);
  pinMode(ue2, INPUT);
  pinMode(ut3, OUTPUT);
  pinMode(ue3, INPUT);
  pinMode(ut4, OUTPUT);
  pinMode(ue4, INPUT);
  pinMode(ut5, OUTPUT);
  pinMode(ue5, INPUT);
  pinMode(ut6, OUTPUT);
  pinMode(ue6, INPUT);
  Serial.println();

  // servo pwm pin
  s1.attach(sp1);
  s2.attach(sp2);
  s3.attach(sp3);
  s4.attach(sp4);
  s5.attach(sp5);
  s6.attach(sp6);
  pinMode(e1, OUTPUT);
  // enable pin
  s1.write(0);
  s2.write(0);
  s3.write(0);
  s4.write(0);
  s5.write(0);
  s6.write(0);
  
}

void loop() {
  Serial.println("choose a no. : ");
  while (Serial.available() == 0) {}
  c = Serial.parseInt();
  if (c == 1) {
    check(ut1, ue1, 5000, e1, s1);
  } else if (c == 2) {
    check(ut2, ue2, 5000, e2, s2);
  } else if (c == 3) {
    check(ut3, ue3, 5000, e3, s3);
  } else if (c == 4) {
    check(ut4, ue4, 5000, e4, s4);
  } else if (c == 5) {
    check(ut5, ue5, 5000, e5, s5);
  } else if (c == 6) {
    check(ut6, ue6, 5000, e6, s6);
  }
}
void check(int x, int y, int d, int e, Servo z) {

  digitalWrite(x, HIGH);
  delay(10);
  digitalWrite(x, LOW);
  int t = pulseIn(y, HIGH);
  int distance = 0.017 * t;

  while (distance > 21) {
    digitalWrite(x, HIGH);
    delay(10);
    digitalWrite(x, LOW);
    int t = pulseIn(y, HIGH);
    distance = 0.017 * t;
    Serial.println(distance);
    delay(100);
  }


  if (distance <= 20) {



    Serial.print(distance);
    delay(500);
    z.write(90);  // 180 angle
    Serial.println("on");
    delay(100);
    digitalWrite(e, HIGH);
    delay(d);
    digitalWrite(e, LOW);
    delay(500);
    z.write(0);  // 0 angle
    Serial.println("off");

    //} else
    //   Serial.println("error");
  }
   delay(50);
  //loop();
}
