#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
 
#include <DabbleESP32.h>
#include <Wire.h>
 
const int enJ5 = 32, in1J5 = 18, in2J5 = 19;
const int enJ2 = 27, in1J2 = 16, in2J2 = 17;
const int enJ3 = 25, in1J3 = 13, in2J3 = 12;
const int enJ4 = 26, in1J4 = 15, in2J4 = 14;
 
const int freq = 5000, resolution = 8;
const int chJ5 = 0, chJ2 = 1, chJ3 = 2, chJ4 = 3;
const int vitesse = 227;
 
void setup() {
  Serial.begin(115200);
  Dabble.begin("AdamESP32");
  Wire.begin(21, 22);
  Wire.setClock(400000);
 
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
 
  pinMode(in1J5, OUTPUT);
  pinMode(in2J5, OUTPUT);
  pinMode(in1J2, OUTPUT);
  pinMode(in2J2, OUTPUT);
  pinMode(in1J3, OUTPUT);
  pinMode(in2J3, OUTPUT);
  pinMode(in1J4, OUTPUT);
  pinMode(in2J4, OUTPUT);
 
  ledcSetup(chJ5, freq, resolution);
  ledcAttachPin(enJ5, chJ5);
  ledcSetup(chJ2, freq, resolution);
  ledcAttachPin(enJ2, chJ2);
  ledcSetup(chJ3, freq, resolution);
  ledcAttachPin(enJ3, chJ3);
  ledcSetup(chJ4, freq, resolution);
  ledcAttachPin(enJ4, chJ4);
 
  arret();
  Serial.println("Pret - connecte Dabble sur le telephone");
}
 
void arret() {
  ledcWrite(chJ5, 0);
  digitalWrite(in1J5, LOW);
  digitalWrite(in2J5, LOW);
  ledcWrite(chJ2, 0);
  digitalWrite(in1J2, LOW);
  digitalWrite(in2J2, LOW);
  ledcWrite(chJ3, 0);
  digitalWrite(in1J3, LOW);
  digitalWrite(in2J3, LOW);
  ledcWrite(chJ4, 0);
  digitalWrite(in1J4, LOW);
  digitalWrite(in2J4, LOW);
}
 
void avancer() {
  ledcWrite(chJ5, vitesse);
  digitalWrite(in1J5, HIGH);
  digitalWrite(in2J5, LOW);
  ledcWrite(chJ2, vitesse);
  digitalWrite(in1J2, LOW);
  digitalWrite(in2J2, HIGH);
  ledcWrite(chJ3, vitesse);
  digitalWrite(in1J3, HIGH);
  digitalWrite(in2J3, LOW);
  ledcWrite(chJ4, vitesse);
  digitalWrite(in1J4, HIGH);
  digitalWrite(in2J4, LOW);
}
 
void reculer() {
  ledcWrite(chJ5, vitesse);
  digitalWrite(in1J5, LOW);
  digitalWrite(in2J5, HIGH);
  ledcWrite(chJ2, vitesse);
  digitalWrite(in1J2, HIGH);
  digitalWrite(in2J2, LOW);
  ledcWrite(chJ3, vitesse);
  digitalWrite(in1J3, LOW);
  digitalWrite(in2J3, HIGH);
  ledcWrite(chJ4, vitesse);
  digitalWrite(in1J4, LOW);
  digitalWrite(in2J4, HIGH);
}
 
void rotation_droite() {
  ledcWrite(chJ5, vitesse);
  digitalWrite(in1J5, HIGH);
  digitalWrite(in2J5, LOW);
  ledcWrite(chJ2, vitesse);
  digitalWrite(in1J2, LOW);
  digitalWrite(in2J2, HIGH);
  ledcWrite(chJ3, vitesse);
  digitalWrite(in1J3, LOW);
  digitalWrite(in2J3, HIGH);
  ledcWrite(chJ4, vitesse);
  digitalWrite(in1J4, LOW);
  digitalWrite(in2J4, HIGH);
}
 
void rotation_gauche() {
  ledcWrite(chJ5, vitesse);
  digitalWrite(in1J5, LOW);
  digitalWrite(in2J5, HIGH);
  ledcWrite(chJ2, vitesse);
  digitalWrite(in1J2, HIGH);
  digitalWrite(in2J2, LOW);
  ledcWrite(chJ3, vitesse);
  digitalWrite(in1J3, HIGH);
  digitalWrite(in2J3, LOW);
  ledcWrite(chJ4, vitesse);
  digitalWrite(in1J4, HIGH);
  digitalWrite(in2J4, LOW);
}
 
void straight_droite() {
  ledcWrite(chJ5, vitesse);
  digitalWrite(in1J5, HIGH);
  digitalWrite(in2J5, LOW);
  ledcWrite(chJ2, vitesse);
  digitalWrite(in1J2, HIGH);
  digitalWrite(in2J2, LOW);
  ledcWrite(chJ3, vitesse);
  digitalWrite(in1J3, LOW);
  digitalWrite(in2J3, HIGH);
  ledcWrite(chJ4, vitesse);
  digitalWrite(in1J4, HIGH);
  digitalWrite(in2J4, LOW);
}
 
void straight_gauche() {
  ledcWrite(chJ5, vitesse);
  digitalWrite(in1J5, LOW);
  digitalWrite(in2J5, HIGH);
  ledcWrite(chJ2, vitesse);
  digitalWrite(in1J2, LOW);
  digitalWrite(in2J2, HIGH);
  ledcWrite(chJ3, vitesse);
  digitalWrite(in1J3, HIGH);
  digitalWrite(in2J3, LOW);
  ledcWrite(chJ4, vitesse);
  digitalWrite(in1J4, LOW);
  digitalWrite(in2J4, HIGH);
}
 
void loop() {
  Dabble.processInput();
 
  if (GamePad.isUpPressed()) {
    avancer();
    Serial.println("AVANCER");
  } else if (GamePad.isDownPressed()) {
    reculer();
    Serial.println("RECULER");
  } else if (GamePad.isRightPressed()) {
    rotation_droite();
    Serial.println("RDROITE");
  } else if (GamePad.isLeftPressed()) {
    rotation_gauche();
    Serial.println("RGAUCHE");
  } else if (GamePad.isCirclePressed()) {
    straight_droite();
    Serial.println("SDROITE");
  } else if (GamePad.isCrossPressed()) {
    straight_gauche();
    Serial.println("SGAUCHE");
  } else {
    arret();
  }
 
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)0x68, (uint8_t)6, (bool)true);
  int16_t ax = (Wire.read() << 8) | Wire.read();
  int16_t ay = (Wire.read() << 8) | Wire.read();
  int16_t az = (Wire.read() << 8) | Wire.read();
 
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)0x68, (uint8_t)6, (bool)true);
  int16_t gx = (Wire.read() << 8) | Wire.read();
  int16_t gy = (Wire.read() << 8) | Wire.read();
  int16_t gz = (Wire.read() << 8) | Wire.read();
 
  Serial.print("G: ");
  Serial.print(gx);
  Serial.print(" ");
  Serial.print(gy);
  Serial.print(" ");
  Serial.println(gz);
 
  Serial.print("A: ");
  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.println(az);
  Serial.println("");
} 