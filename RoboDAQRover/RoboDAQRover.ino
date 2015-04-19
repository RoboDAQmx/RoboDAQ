//PIN 8 - Servo
//PIN 7, PIN 6 - Motor Derecha
//PIN 5, PIN 4 - Motor Izquierda
//PIN 3 - Reactor
#include<Servo.h>
Servo servo;
int x, pos = 0;
void setup(){
  Serial.begin(9600);
  servo.attach(8);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  servo.write(pos);
}
void loop(){
  while(Serial.available()>0){
    x = Serial.read();
    switch(x){
      case 8: avanzar();
      break;
      case 2: retroceder();
      break;
      case 6: derecha();
      break;
      case 4: izquierda();
      break;
      case 5: parar();
      break;
      case 1: abrir();
      break;
      case 3: cerrar();
      break;
      case 7: encender();
      break;
      case 9: apagar();
      break;
    }
  }
}
void avanzar(){
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
}
void retroceder(){
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
}
void derecha(){
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
}
void izquierda(){
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
}
void parar(){
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
}
void abrir(){
  servo.write(pos);
  pos = pos + 20;
}
void cerrar(){
  servo.write(pos);
  pos = pos - 20;
}
void encender(){
  digitalWrite(3,HIGH);
}
void apagar(){
  digitalWrite(3,LOW);
}
