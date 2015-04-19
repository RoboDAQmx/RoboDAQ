//Barometro: 5V, GND, SDA - A4, SCL - A5
//Sensor humedad: 5V, GND, PIN 2
//Sensor CO2: 5V, GND, DOUT - A0
//Sensor UV: 5V, GND, OUT - A1
//Sensor Ultrasonco: 5V, GND, TRIG - PIN 12, ECHO - PIN 13
#include <Wire.h>
#include <BMP085.h>
#include <Ultrasonic.h>
#define TRIGGER_PIN  12
#define ECHO_PIN     13
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
BMP085 bmp;
#include <dht11.h>
dht11 DHT11;
#define DHT11PIN 3
#include "math.h"
double a = 116.6020682;
double b = -2.769034857;
double atCO2 = 399.50;
double rs = 1023.0-25.0;
double ro = rs*exp(log(a/atCO2)/b);
double ppm;
int sensor, mV, indice;
float cm;
void setup(){
  Serial.begin(9600);
  while(!bmp.begin(BMP085_ULTRA_HIGH_RES)){
    Serial.println("BMP085 conexion erronea");
  }
  int chk = DHT11.read(DHT11PIN);
  switch (chk){
    case DHTLIB_OK:
    break;
    case DHTLIB_ERROR_CHECKSUM:  Serial.println("DHT11 checksum error");
    break;
    case DHTLIB_ERROR_TIMEOUT:  Serial.println("DHT11 time out error");
    break;
    default:  Serial.println("DHT11 error desconocido");
    break;
  }
}
void loop(){
  barometro();
  humedad();
  CO2();
  UV();
  ultrasonico();
  delay(500);
}
void barometro(){
  double realTemperature = bmp.readFloatTemperature();
  double realPressure = bmp.readFloatPressure();
  float absoluteAltitude = bmp.getAltitude(realPressure);
  Serial.print(" ");
  Serial.print("Temperatura: ");
  Serial.print(realTemperature);
  Serial.println(" *C");
  Serial.print(" ");
  Serial.print("Presion: ");
  Serial.print(realPressure / 100.0);
  Serial.println(" mBar");
  Serial.print(" ");
  Serial.print("Altitud: ");
  Serial.print(absoluteAltitude);
  Serial.println(" m");
}
void humedad(){
  DHT11.read(DHT11PIN);
  Serial.print(" ");
  Serial.print("Humedad: ");
  Serial.print((float)DHT11.humidity, 2);
  Serial.println(" %");
}
void CO2(){
  rs = 1023.0 - analogRead(A0);
  ppm = a*pow((rs/ro),b);
  Serial.print(" ");
  Serial.print("CO2: ");
  Serial.print(ppm);
  Serial.println(" ppm");
}
void UV(){
  sensor = analogRead(A1);
  mV = sensor*(5000.0/1023.0);
  if(mV<227){
    indice = 0;
  }else if(mV<318){
    indice = 1;
  }else if(mV<408){
    indice = 2;
  }else if(mV<503){
    indice = 3;
  }else if(mV<606){
    indice = 4;
  }else if(mV<696){
    indice = 5;
  }else if(mV<795){
    indice = 6;
  }else if(mV<881){
    indice = 7;
  }else if(mV<976){
    indice = 8;
  }else if(mV<1079){
    indice = 9;
  }else if(mV<1170){
    indice = 10;
  }else{
    indice = 11;
  }
  Serial.print(" ");
  Serial.print("Indice ultravioleta: ");
  Serial.println(indice);
}
void ultrasonico(){
  long microsec = ultrasonic.timing();
  cm = ultrasonic.convert(microsec, Ultrasonic::CM);
  if(cm>30.0){
    Serial.print(" ");
    Serial.println("Fuera de alcance");
  }else{
    Serial.print(" ");
    Serial.print("Distancia: ");
    Serial.print(cm);
    Serial.println(" cm");
  }
}
