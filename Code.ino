#include <dht.h>
#include <Servo.h>

dht DHT;
Servo servo;

int   tempSensorPin = 3;
int   servoPin      = 5;
int   servoDelay    = 12;
int   servoDeg      = 50;
int   trigPin       = 8; 
int   echoPin       = 9;
int   ledPin        = 13;
int   buzzerPin     = 11;
bool  servoIncr     = true;
float velocity, distance, duration;


void rotateServo(){
  if(servoIncr){
    for(servoDeg; servoDeg<=130; servoDeg++){
      servo.write(servoDeg);
      if(servoDeg%5==0){
         calculateDistance();
         alertOn();
      }
      delay(servoDelay);
    }
  }
  else if(!servoIncr){
    for(servoDeg; servoDeg>=50; servoDeg--){
      servo.write(servoDeg);
      if(servoDeg%5==0){
         calculateDistance();
         alertOn();
      }
      delay(servoDelay);
    }
  }

  servoIncr = servoDeg>=130 ? false : servoDeg<=50 ? true : servoIncr;
}

void calculateVelocity(int temp){
   velocity = 332 + (0.6 * temp);
   velocity = (velocity/1000000.00)*100;
}

void calculateDistance(){
   digitalWrite(trigPin, LOW);
   delayMicroseconds(5);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   distance = (velocity * duration)/2.00;

   //Serial.print("Distance = ");
   //Serial.println(distance, 4);
}

void alertOn(){
  if(distance<=30){
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 500);
    //Serial.println("Intruder Detected!");
  }
}

void setup() {
  //Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}


void loop(){
  
  int var = DHT.read11(tempSensorPin);
  delay(500);
  
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);
  
  int currTemp = DHT.temperature;
  //Serial.print("Current Temperature: ");
  //Serial.println(currTemp);

  calculateVelocity(currTemp);
  //Serial.print("Velocity = ");
  //Serial.println(velocity, 4); 
  
  rotateServo();
   
}
