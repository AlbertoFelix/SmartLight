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
#define AnalogLDR A2
#define lumenPin 52

// defines variables
#define brilhoMaximo 1024
#define brilhoMinimo 500
long duration;
int distance, Brilho = 0, Leitura = 0;
char turn = 'l';

/*void limpeza(){
  
}*/

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

    pinMode(botton, INPUT_PULLUP);
    pinMode(motorR, OUTPUT);
    pinMode(motorL, OUTPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(lumenPin, OUTPUT);
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

    //Entrada analógica OK
    Leitura = analogRead(AnalogLDR);
    Brilho = map(Leitura, brilhoMinimo, brilhoMaximo, 10, 255);
    if(Brilho >= 220){
      digitalWrite(ledPin, HIGH);
    } else{
      digitalWrite(ledPin, LOW);
    }
    //###################################
    
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
