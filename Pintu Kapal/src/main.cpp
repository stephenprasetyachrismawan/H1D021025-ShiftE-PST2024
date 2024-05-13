#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;

LiquidCrystal_I2C lcd(0x27,16,2);
int SDA_pin = D3;
int SCL_pin = D7;

int trigPin = D1;
int echoPin = D0;
int led_hijau = D5;
int led_kuning = D6;
int masuk = 0;
long duration;
int distance;
void setup() {
  myservo.attach(D4);
  pinMode(led_hijau,OUTPUT);
  pinMode(led_kuning,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
  Wire.begin(SDA_pin,SCL_pin);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  myservo.write(0);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = 0.034 * duration /2;
  Serial.print("Jarak : ");
  Serial.print(distance);
  Serial.print(" cm\n");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Jarak");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.setCursor(7,1);
  lcd.print("cm");
  if(distance < 10){
    digitalWrite(led_hijau,HIGH);
    digitalWrite(led_kuning,LOW);
    if(masuk == 0){
      myservo.write(180);
    }
    
    masuk = 1;
  }else{
    digitalWrite(led_hijau,LOW);
    digitalWrite(led_kuning,HIGH);
    if(masuk == 1){
      myservo.write(0);
    }
     masuk = 0;
  }

  delay(1000);
  // put your main code here, to run repeatedly:
}

