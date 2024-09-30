#include <IRremote.hpp>
#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define IR_RECEIVE_PIN 9
#define buzzer 10 
#define DHTPIN 13 // Digital pin connected to the DHT sensor 13
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

const unsigned long checkInterval = 3000;
unsigned long time_mouv;
unsigned long diff_time;
const int trigPin = 2;  // Pin connecté au trig du capteur
const int echoPin = 3;

//motor 1
int motor_value;
int motor_in1 = 11;
int motor_in2 = 12;
//motor 2
int motor2_in1 = 5; 
int motor2_in2 = 6;
LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(DHTPIN, DHTTYPE);

void donnees_env(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  lcd.setCursor(9,0);
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
}
void alertDanger(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);// Envoyer une impulsion de 10µs sur la pin trig pour démarrer la mesure
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Lire le temps d'impulsion sur la pin echo
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration*0.034/2;
  if (distance < 10){
    digitalWrite(buzzer, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OBSTACLE a");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.print(" CM");
    delay(100);
   }else{
    digitalWrite(buzzer, LOW);
   }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
  //pinMode(motor_en, OUTPUT);
  pinMode( motor_in1, OUTPUT);
  pinMode(motor_in2, OUTPUT);

  //pinMode(motor2_en, OUTPUT);
  pinMode( motor2_in1, OUTPUT);
  pinMode(motor2_in2, OUTPUT);

  pinMode(buzzer, OUTPUT);
  digitalWrite(motor_in1, LOW);
  digitalWrite(motor_in2, LOW);

  digitalWrite(motor2_in1, LOW);
  digitalWrite(motor2_in2, LOW);

  Serial.begin(9600); // Établir la communication série
  Serial.println("Initialisation du récepteur IR...");
  
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Récepteur IR démarré avec succès.");
 }
 void loop(){
  donnees_env();
  alertDanger();
  if (IrReceiver.decode()) {
    Serial.println("Signal IR reçu !");
    
    // Vérifier si les données reçues sont valides
    if (IrReceiver.decodedIRData.decodedRawData != 0) {
      Serial.print("Données brutes reçues : ");
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Affiche les données brutes
      if (IrReceiver.decodedIRData.decodedRawData == 0xB946FF00){ //avant
        time_mouv = millis();
        avancer();
      }else if(IrReceiver.decodedIRData.decodedRawData == 0xEA15FF00){ //arriere
        time_mouv = millis();
        reculer();
      }else if (IrReceiver.decodedIRData.decodedRawData == 0xBC43FF00){ //droite
        time_mouv = millis();
        right();
      }else if (IrReceiver.decodedIRData.decodedRawData == 0xBB44FF00){ //gauche
        time_mouv = millis();
        left();
      }else if (IrReceiver.decodedIRData.decodedRawData == 0xBF40FF00){ //arret
        stopMotor();
      }
    } else {
      Serial.println("Erreur : Données IR reçues mais non valides.");
    }
    IrReceiver.resume(); // Permet la réception de la prochaine valeur
  } else {
    // Afficher un message d'attente pour la réception
    if (diff_time > checkInterval){
      stopMotor();
    }
    //stopMotor();
    delay(500); // Ajouter un délai pour éviter une surcharge de la sortie série
  }
   diff_time=millis() - time_mouv;
 }
void avancer() { 
    digitalWrite(motor_in1, HIGH);
    digitalWrite(motor_in2, LOW);
    digitalWrite(motor2_in1, HIGH);
    digitalWrite(motor2_in2, LOW); 
  }
void reculer() {
    digitalWrite(motor_in1, LOW);
    digitalWrite(motor_in2, HIGH); 
    digitalWrite(motor2_in1, LOW);
    digitalWrite(motor2_in2, HIGH); 
    } 
void right() {
    digitalWrite(motor_in1, LOW);
    digitalWrite(motor_in2, HIGH);
    digitalWrite(motor2_in1, HIGH);
    digitalWrite(motor2_in2, LOW);
    } 
void left() {
    digitalWrite(motor_in1, HIGH); 
    digitalWrite(motor_in2, LOW);
    digitalWrite(motor2_in1, LOW); 
    digitalWrite(motor2_in2, HIGH);
      } 
void stopMotor() { 
    digitalWrite(motor_in1, LOW);
    digitalWrite(motor_in2, LOW);
    digitalWrite(motor2_in1, LOW);
    digitalWrite(motor2_in2, LOW);
    }
