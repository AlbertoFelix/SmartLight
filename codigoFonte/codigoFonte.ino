#include <Wire.h>
#include <LiquidCrystal_I2C.h>



// defines pins numbers
#define buttonOnOff 18
#define buttonOnOffSensores 19
#define buttonBrilho 2
#define trigPin 22
#define echoPin 23
#define AnalogLDR A2
#define led1 12
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define led6 7
#define led7 8
#define led8 9
#define led9 10
#define led10 11

// defines variables
#define brilhoMaximo 1024
#define brilhoMinimo 500
long duration;
int distance, Brilho = 0, Leitura = 0, controleBrilho = 0; 
byte OnOff = 0, OnOffSensores = 0, vez = 0;

// Inicializa o display no endereço 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);


void interruptor(){
  OnOff = !OnOff;
  delay(10);
  vez = OnOff;  
}

void interruptorSensores(){
  OnOffSensores = !OnOffSensores;
  delay(10);
  vez = OnOffSensores + 2;
}

void controlBrilho(){
  if(controleBrilho == 0)
    controleBrilho = 1;
  else if(controleBrilho == 1)
    controleBrilho = 2;
  else if(controleBrilho == 2)
    controleBrilho = 3;
  else if(controleBrilho == 3)
    controleBrilho = 0;
   delay(150);
}





void setup() {
    // Leds conectados nos pinos PWM
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(led7, OUTPUT);
    pinMode(led8, OUTPUT);
    pinMode(led9, OUTPUT);
    pinMode(led10, OUTPUT);

    //Botão liga e desliga sistema
    pinMode(buttonOnOff, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonOnOff), interruptor, RISING);

    //Botão liga e desliga Sensores
    pinMode(buttonOnOffSensores, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonOnOffSensores), interruptorSensores, RISING);
    

    //Botão controle do brilho
    pinMode(buttonBrilho, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonBrilho), controlBrilho, RISING);

    
    pinMode(trigPin, OUTPUT); // trigPin como saída
    pinMode(echoPin, INPUT); // echoPin como entrada
     
    Serial.begin(9600); 
    
    // Inicializa o display LCD 16x2
   lcd.init();
   
   // Liga a luz de fundo do LCD
   lcd.setBacklight(HIGH);
}

void loop() {
   
  if(OnOff == 0){
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    analogWrite(led4, 0);
    analogWrite(led5, 0);
    analogWrite(led6, 0);
    analogWrite(led7, 0);
    analogWrite(led8, 0);
    analogWrite(led9, 0);
    analogWrite(led10, 0);
    if (vez == 0) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Desligado");
      vez = 1;
    }
    
  }else{
      if (vez == 1) {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Ligado");
        if (OnOffSensores == 0) {
          vez = 2;
        }
        else {
          vez = 3;
        }
        
      }
      
      if(OnOffSensores == 0){
        if (vez == 2) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Sensores Desl.");
          
          vez = 4;
        }

        if (vez == 4) {
          if(controleBrilho == 0){
          lcd.setCursor(0, 0);
          lcd.print("Brilho: 0%       ");
          analogWrite(led1, 0);
          analogWrite(led2, 0);
          analogWrite(led3, 0);
          analogWrite(led4, 0);
          analogWrite(led5, 0);
          analogWrite(led6, 0);
          analogWrite(led7, 0);
          analogWrite(led8, 0);
          analogWrite(led9, 0);
          analogWrite(led10, 0);
        } else if(controleBrilho == 1){
          lcd.setCursor(0, 0);
          lcd.print("Brilho: 25%       ");
          analogWrite(led1, 100);
          analogWrite(led2, 100);
          analogWrite(led3, 100);
          analogWrite(led4, 100);
          analogWrite(led5, 100);
          analogWrite(led6, 100);
          analogWrite(led7, 100);
          analogWrite(led8, 100);
          analogWrite(led9, 100);
          analogWrite(led10, 100);
        } else if(controleBrilho == 2){
          lcd.setCursor(0, 0);
          lcd.print("Brilho: 50%          ");
          analogWrite(led1, 170);
          analogWrite(led2, 170);
          analogWrite(led3, 170);
          analogWrite(led4, 170);
          analogWrite(led5, 170);
          analogWrite(led6, 170);
          analogWrite(led7, 170);
          analogWrite(led8, 170);
          analogWrite(led9, 170);
          analogWrite(led10, 170);
        } else if(controleBrilho == 3){
          lcd.setCursor(0, 0);
          lcd.print("Brilho: 100%       ");
          analogWrite(led1, 255);
          analogWrite(led2, 255);
          analogWrite(led3, 255);
          analogWrite(led4, 255);
          analogWrite(led5, 255);
          analogWrite(led6, 255);
          analogWrite(led7, 255);
          analogWrite(led8, 255);
          analogWrite(led9, 255);
          analogWrite(led10, 255);
        }
        } 
        
      }else{
          if (vez == 3) {
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Sensores");
            lcd.setCursor(2, 1);
            lcd.print("Ligados");
            vez = 4;
          }
          
          
          // Limpa o trigPin
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2);
          
          // Seta o trigPin para estado HIGH por 10 micro segundos
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
          // Lê o echoPin, retorna o tempo de viajem da onda sonora em microsegundos
          duration = pulseIn(echoPin, HIGH);
          // Calculando a distância
          distance = duration*0.034/2;
          // Prints the distance on the Serial Monitor
          /*delay(500);*/
          Serial.print("Distance: ");
          Serial.print(distance);
          Serial.println("cm");
          //delay(500);

          //Entrada analógica OK***********************************************/
          Leitura = analogRead(AnalogLDR);
          Brilho = map(Leitura, brilhoMinimo, brilhoMaximo, 10, 255);
          Serial.println(Leitura);
          Serial.println(Brilho);
          if(Brilho >= 220 || distance <= 60){
            analogWrite(led1, 255);
            analogWrite(led2, 255);
            analogWrite(led3, 255);
            analogWrite(led4, 255);
            analogWrite(led5, 255);
            analogWrite(led6, 255);
            analogWrite(led7, 255);
            analogWrite(led8, 255);
            analogWrite(led9, 255);
            analogWrite(led10, 255);
          } else{
            analogWrite(led1, 0);
            analogWrite(led2, 0);
            analogWrite(led3, 0);
            analogWrite(led4, 0);
            analogWrite(led5, 0);
            analogWrite(led6, 0);
            analogWrite(led7, 0);
            analogWrite(led8, 0);
            analogWrite(led9, 0);
            analogWrite(led10, 0);
          }
          /*********************************************************************/
      }
      
  } 
    
}
