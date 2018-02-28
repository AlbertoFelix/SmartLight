/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
#define trigPin 4
#define echoPin 5
#define motorR 7
#define motorL 44
#define botton 10

// defines variables
long duration;
int distance;
char turn = 'l';

void turnRight(){
  //digitalWrite(motorR, LOW);
  digitalWrite(motorL, HIGH);
  turn = 'r';
  delay(500);
  digitalWrite(motorL, LOW);
  delay(100);  
}

void turnLeft(){
  digitalWrite(motorR, HIGH);
  turn = 'l';
  //digitalWrite(motorL, LOW);
  delay(500);
  digitalWrite(motorR, LOW);  
  delay(100);
}

void setup() {
  
    pinMode(motorR, OUTPUT);
    pinMode(motorL, OUTPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication
}

void loop() {
    digitalWrite(motorR, HIGH);
    digitalWrite(motorL, HIGH);
    
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration*0.034/2;
    // Prints the distance on the Serial Monitor
    /*delay(500);
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("cm");
    delay(500);*/
    
    if(distance <= 2 && turn == 'l'){
        digitalWrite(motorR, LOW);
        digitalWrite(motorL, LOW);
        turnRight();
    }
    digitalWrite(motorR, HIGH);
    digitalWrite(motorL, HIGH);
    
    if(distance <= 2 && turn == 'r'){
        digitalWrite(motorR, LOW);
        digitalWrite(motorL, LOW);
        turnLeft();
    }
    
    digitalWrite(motorR, HIGH);
    digitalWrite(motorL, HIGH);
    
}
