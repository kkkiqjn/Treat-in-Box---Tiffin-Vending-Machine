#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 400


#define button 6

#define led 7
#define buzzer 8

//time of flight pins
#define tof 14
unsigned long duration;



const int trigger = 4;
const int echo =5;




float distance;
float dist_inches;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);


  //Stepper Motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  //Button
  pinMode(button, INPUT_PULLUP);

  //Buzzer
  // pinMode(buzzer, OUTPUT);


  //cup dispensed detection ultrasonic sensor
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);



  


  //Low cup using time of flight
  pinMode(tof,INPUT);





  pinMode(led, OUTPUT);

  pinMode(buzzer,OUTPUT);




  delay(500);
  while(lowCuptof()==false){
    tone(buzzer,1000);
    delay(500);
    tone(buzzer,260);
  }
  noTone(buzzer);

}

void loop() {
  // put your main code here, to run repeatedly:
  int x = digitalRead(button);
    delay(50);
    digitalWrite(dirPin, LOW);
    if (x == 0 && lowCuptof()) {
     digitalWrite(dirPin,HIGH);
      Serial.println("Switch pressed");
      

      
      loop:
      {
      // This while loop ensures that the motor rotates untill the cup dispenses


      while (true) {
        // Spin the stepper motor 1 revolution slowly:
        for (int i = 0; i < stepsPerRevolution; i++) {
          // These four lines result in 1 step:
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(500);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(500);
        }
        delay(800);

        digitalWrite(trigger, LOW);  //ultra sonic sensor starts measurement
        delayMicroseconds(5);
        digitalWrite(trigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger, LOW);
        distance = pulseIn(echo, HIGH);
        distance = distance * 0.0343 / 2;
            //distance of the cup gets calculated here
        if (distance <10) {
          Serial.print("cup dispensed:");

          // tone(buzzer, 100);

          digitalWrite(led, HIGH);
          tone(buzzer,1000);
          delay(1000);
          noTone(buzzer);
          
        
          break;
        }
      }

      delay(3000);

 
      }
      // print the value on the serial monitor 
      digitalWrite(trigger, LOW);  //ultra sonic sensor starts measurement
      delayMicroseconds(5);
      digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);

      // Acquire and convert to inches
      distance = pulseIn(echo, HIGH);
      distance = distance * 0.0343 / 2;
      while(distance <10) {
            digitalWrite(trigger, LOW);  //ultra sonic sensor starts measurement
            delayMicroseconds(5);
            digitalWrite(trigger, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigger, LOW);

            // Acquire and convert to inches
            distance = pulseIn(echo, HIGH);
            distance = distance * 0.0343 / 2;

      


      } 


        //Led gets off when the cup is not detected
        if(lowCuptof()){
        digitalWrite(led, LOW);
        goto loop;
        }
        else{
          digitalWrite(led,LOW);
          while(lowCuptof()==false){
            tone(buzzer,1000);
            delay(500);
            tone(buzzer,260);
          }
          noTone(buzzer);
        }



    
    }

}



bool lowCuptof(){
  uint16_t distance=0;
          duration = pulseIn(tof, HIGH);
          distance=duration/100;
          
           Serial.print("distance: ");
           Serial.print( distance);
           Serial.print(" mm,time: ");
           Serial.print( duration); 
           Serial.println("us");
           delay(100);
           if(distance<=4)return true;
           else{
            return false;
           }
}
