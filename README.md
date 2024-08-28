# Robot-de-surveillance-environnemental_STEAMY_PRO

# Steamy Project : Conception d’un robot

# Environnemental mobile


# Sommaire

## [A- Présentation du projet](###-A--Présentation-du-projet)

## a. Objectif du projet

## b. Contexte d’utilisation

## [B- Matériels nécessaires](#B- Matériels nécessaires)

## a. Composants et utilités

## b. Outil logiciel

## [C- Installation et configuration](#C- Installation et configuration)

## a. Montage physique

## b. Configuration logicielle

## [D- Fonctionnement](#D- Fonctionnement)

## a. Explication du code

## b. Fonctionnement du système

## c. Résultats


### A- Présentation du projet

### a. Objectif du projet

L'objectif de ce projet est de concevoir un système intelligent utilisant le potentiel du kit
"STEAMY PRO". Ce système agit comme un contrôleur mobile, capable de surveiller et
d'informer sur l'état d'un lieu en temps réel, en détectant divers obstacles et en fournissant des
alertes appropriées. Le projet met en œuvre plusieurs composants électroniques pour assurer
une régulation fiable et automatique de l'environnement de

### b. Contexte d’utilisation

Le système est conçu pour être utiliser dans n’importe quel lieu où l’engin peut se déplacer. Il
surveille et communique les données environnementales du milieu où il se trouve. Le robot
fonctionne en dépendant de l’opérateur qui le gouverne à distance. Il réagit aux entrées
(comme le capteur ultra-sons, le capteur d’humidité et température, etc.) et affiche les
résultats via un écran LCD, un buzzer ...

### B- Matériels nécessaires

### a. Composants et utilités


<img src="/images/Arduino_uno.jpeg" style="width:5.75in;height:2.45833in" />
Arduino Uno


<img src="/images/Arduino_Shield.png" style="width:50%;height:auto" />
shield Arduino

<img src="/images/LCD.png" style="width:50%;height:auto" />

**Écran LCD** pour l’affichage des informations


<img src="/images/module_capteurIR.png" style="width:auto;height:auto" />
capteur infrarouge

<img src="/images/ultrason.png" style="width:50%;height:auto" />
Capteur ultra-son

<img src="/images/télécommande_IR.jpg" style="width:50%;height:auto" />
Télécommande infrarouge

<img src="/images/DHT22.png" style="width:25%;height:auto" />
capteur de tem pérature et
d’humidité

<img src="/images/buzzer.png" style="width:25%;height:auto" />
Buzzer


### b. Outil logiciel

Pour ce projet nous utiliserons l’IDE Arduino. C’est une application multiplateforme qui est
écrite dans des fonctions de C et C++. Il est utilisé pour écrire et télécharger des
programmes sur des cartes compatibles Arduino. Il fournit plusieurs bibliothèques sous forme
de classes (programmation orienté objet) qui sont utilisées notamment pour les différents
capteurs et modules compatibles avec Arduino. Il utilise le programme avrdude pour
convertir le code exécutable en un fichier texte au codage hexadécimal qui est chargé dans la
carte Arduino par un programme de chargement dans le firmware de la carte.
Téléchargez et installez depuis le [site officielle de téléchargement](https://www.arduino.cc/en/software)

N.B. : Veuillez à télécharger et installer l'IDE Arduino compatible avec votre système
d'exploitation
Après installation vous devrez obtenir l’interface suivante ou une interface similaire en
fonction de la version.


### C- Installation et configuration

### c.Montage physique

En utilisant le kit Steamy Pro, nous avons pu accéder à un module Arduino Shield ainsi qu'à
différents autres modules compatibles avec les composants utilisés. Cela a grandement
facilité les branchements. Pour plus d'informations sur l'utilisation de ce kit, veuillez vous
référer à la documentation disponible à l'adresse de la  [Documentation officielle du kit Steamy pro](http://www.jjj.com.)
Voici les branchements effectués pour chaque équipement :
_Moteurs CC :_ Chaque moteur CC a été relié à un module dédié, principalement composé d'un
circuit intégré L293D. Chaque module a été branché respectivement aux broches D11 et D
pour l'un, et D5 et D6 pour l'autre.
_Écran LCD :_ L'écran LCD a été relié aux broches SDA et SCL.
_Capteur à ultrasons :_ Le capteur à ultrasons a été branché aux broches D3 pour l'écho (echo)
et D2 pour le déclenchement (trig).
_Capteur DHT (température et humidité) :_ La broche de signal du capteur DHT a été reliée à
la broche D13 de l'Arduino.
_Capteur infrarouge :_ Le capteur infrarouge a été branché à la broche D9.

```
Image du montages effectué :
```
### b.Configuration logicielle

Pour pouvoir faire fonctionner correctement les diferents capteur et actionneurs utilisées pour
ce projets vous aurez besoin d’installer certaines bibliothèques sous arduino. Pour installer
une bibliothèque il suffit de taper son nom dans la barre de recherche qui se trouve au niveau
du gestionnaire de bibliothèque. Les bibliothèques dont vous aurez besoins sont les
suivantes :

-LiquidCrystal_I2C : Cette bibliothèque permet d'afficher des informations sur l'écran
LCD en utilisant le protocole de communication I2C.

-Wire : Est une bibliothèque prée installée avec l’arduino IDE. Elle gère la communication
I2C entre l'Arduino Uno et les périphériques compatibles, comme l'écran LCD.


-DHT :La bibliothèque DHT facilite la communication entre l'Arduino Uno et le
capteur de température et d'humidité, permettant ainsi la lecture des données
environnementales.

-IRremote : La bibliothèque IRremote permet d'utiliser le capteur infrarouge pour
recevoir et interpréter les signaux provenant de la télécommande infrarouge. Cela
permet de contrôler le robot à distance.

### D- Fonctionnement

### a. Explication du code

La logique de ce système a été codé en C++ propre aux matériels Arduino. Ayant pris en
charge plusieurs module pour ce projet il est nécessaire de procéder d’abord à l’appel des
bibliothèques propre au fonctionnement de ces modules.
#include <IRremote.hpp> // pour l’émetteur infra-rouge
#include "DHT.h" // pour le capteur d’humidité et de Température
#include <Wire.h> // pour le fonctionnement de l’écran LCD
#include <LiquidCrystal_I2C.h> // pour le fonctionnement de l’écran LCD

Ensuite nous définissons les variables globales de notre système. C’est également à cette
étape que l’on établir les pines que nous utiliserons dans notre système.

```
const unsigned long checkInterval = 3000;
unsigned long time_mouv;
unsigned long diff_time;
const int trigPin = 2; // Pin connecté au trig du capteur Dht
```

```
const int echoPin = 3; // Pin connecté à echo du capteur Dht
```
```
//motor 1
int motor_in1 = 11;
int motor_in2 = 12;
//motor 2
int motor2_in1 = 5;
int motor2_in2 = 6;
LiquidCrystal_I2C lcd(0x27,16,2); //objet servant pour l’affichage sur l’écran LCD
DHT dht(DHTPIN, DHTTYPE); // objet servant pour la lecture de la température et
de l’humidité.
```
Pour avoir des informations sur l’environnement entourant le robot on a créé deux fonctions
donnees_env() et alertDanger() qui se charge respectivement de récupérer des données
relatives au climat et aux potentielle obstacle devant le robot.
```
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
```
```
lcd.print(" C");
}
void alertDanger(){
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);// Envoyer une impulsion de 10μs sur la pin trig pour
démarrer la mesure
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
digitalWrite(buzzer, LOW);}
}
```

Ensuite on va créer les fonctions qui permettront de contrôler les quatre directions de
déplacements du robot avancer, reculer, gauche, droite ainsi que l’arrêt de l’engin.
```
void avancer(){
digitalWrite(motor_in1, HIGH);
digitalWrite(motor_in2,LOW);
digitalWrite(motor2_in1, HIGH);
digitalWrite(motor2_in2,LOW);
}
```
```
void reculer (){
digitalWrite(motor_in1, LOW);
digitalWrite(motor_in2,HIGH);
digitalWrite(motor2_in1, LOW);
digitalWrite(motor2_in2,HIGH);
}
void right(){
digitalWrite(motor_in1, LOW);
digitalWrite(motor_in2,HIGH);
digitalWrite(motor2_in1, HIGH);
digitalWrite(motor2_in2, LOW);
}
```
```
void left(){
digitalWrite(motor_in1, HIGH);
digitalWrite(motor_in2,LOW);
digitalWrite(motor2_in1,LOW);
digitalWrite(motor2_in2,HIGH);
}
```

```
void stopMotor(){
digitalWrite(motor_in1, LOW);
digitalWrite(motor_in2,LOW);
digitalWrite(motor2_in1,LOW);
digitalWrite(motor2_in2,LOW);
}
```
La dernière partie concerne le code principal. Nous avons une fonction setup() qui permet
contient toutes les configurations de base du code et une boucle qui se répète dans la fonction
loop(). Dans cette dernière le système lit les signaux infrarouges qu’il reçoit. Il les compare
aux signaux déclencheurs d’actions et réagir en conséquence.

```
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
lcd.init();
lcd.backlight();
dht.begin();
//pinMode(motor_en, OUTPUT);
pinMode( motor_in1, OUTPUT);
pinMode(motor_in2, OUTPUT);
```
```
//pinMode(motor2_en, OUTPUT);
pinMode( motor2_in1, OUTPUT);
pinMode(motor2_in2, OUTPUT);

pinMode(buzzer, OUTPUT);
```
```
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
Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Affiche les
données brutes
if (IrReceiver.decodedIRData.decodedRawData == 0xB946FF00){ //avant
time_mouv = millis();
avancer();
}else if(IrReceiver.decodedIRData.decodedRawData == 0xEA15FF00){ //arriere
time_mouv = millis();
```

```
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
stopMotor() ;
}
//stopMotor();
delay(500); // Ajouter un délai pour éviter une surcharge de la sortie série
}
diff_time=millis() - time_mouv;
}
```
### b. Fonctionnement du système

Le système fonctionne de la façon suivante :


#### 1. Démarrage et État du Système

En appuyant sur l'interrupteur d'allumage, les différents capteurs sont activés, rendant ainsi
l'appareil prêt à fonctionner.

#### 2. Affichage des Données Environnementales

Grâce au capteur DHT22, qui mesure la température et l'humidité, le robot affiche sur l'écran
LCD la température ambiante ainsi que le pourcentage d'humidité de l'environnement dans
lequel il se trouve.

#### 3. Contrôle à Distance

Une fois l'appareil allumé, le capteur infrarouge est prêt à recevoir les signaux émis par la
télécommande infrarouge, qui sera utilisée pour contrôler le robot.
Pour avancer ou reculer, il suffit d'appuyer une fois sur la touche correspondante de la
télécommande ; le robot effectuera alors l'action commandée pendant trois secondes.
De même, pour les déplacements latéraux (gauche ou droite), il suffit d'appuyer sur le bouton
correspondant, et le robot tournera dans la direction souhaitée pendant trois secondes.
Si vous souhaitez arrêter le robot pendant ces trois secondes de déplacement, il vous suffit
d'appuyer sur la touche "stop".


#### 4. Détection d'Obstacles et Affichage de la Distance

Si l'appareil s'approche à moins de 10 cm d'un obstacle, il affichera la distance le séparant de
cet obstacle sur l'écran LCD, et un buzzer se mettra à sonner pour alerter l'utilisateur

### c. Résultats

Ce système permet de surveiller un environnement à distance et de recueillir des informations
à son sujet. Développé à des fins éducatives, ce prototype présente encore des lacunes en
termes de fonctionnalités pour être utilisé dans le cadre de la surveillance environnementale.
Cependant, il peut servir de base pour la création d'appareils plus performants et plus utiles.

**Image du prototype**

## Améliorations Possibles

**_Capteur de luminosité_** _:_ l'ajout d'un capteur de luminosité permet de détecter avec précision
la présence d'obscurité dans le milieu surveillé. Cela offre une analyse plus complète des
conditions de l'environnement.

_S_ **_auvegarde et transmission des données_** _:_ Un mécanisme de sauvegarde des données
environnementales en temps réel a été implémenté. Le système peut envoyer ces informations
vers un appareil distant, facilitant l'accès et l'analyse des données.

**Mobilité** **_améliorée_** _:_ L'utilisation de quatre moteurs au lieu de deux permet une mobilité
accrue du robot dans son environnement. Cela se traduit par une couverture plus large et une
plus grande flexibilité dans les déplacements.


**_Guidage automatique_** _:_ Un mode de guidage automatique peut être ajouté, basé sur le
capteur à ultrasons. Cette fonctionnalité peut permettre au robot de naviguer de manière
autonome dans l'environnement surveillé, optimisant ainsi la collecte des données.

**_Ajout d'une caméra :_** L'intégration d'une caméra permettrait d'optimiser le téléguidage à
distance tout en recueillant davantage d'informations sur la zone à analyser. Une caméra peut
fournir une vue en temps réel de l'environnement, facilitant ainsi la navigation et l'analyse des
données.

**_Utilisation d'un module Bluetooth :_** L'ajout d'un module Bluetooth faciliterait le téléguidage
à distance en augmentant la portée de contrôle. Cela permettrait de commander le robot plus
facilement , offrant ainsi plus de flexibilité et de liberté de mouvement lors des opérations de
surveillance ou d'analyse.

**Difficultés**

**1. Difficultés lors de l’implémentation du système de guidage**
_Description_ : Le contrôle de la vitesse entraînait un comportement inattendu, où une roue
tournait plutôt que les deux.
_Impact_ : Cela affecte la maniabilité et la direction du robot, rendant le téléguidage moins
précis et limitant son efficacité.
_Solution_ : Ce problème nécessite une réévaluation de la logique de contrôle des moteurs pour
assurer un mouvement synchronisé.
**2. Lecture des données environnementales par le capteur DHT**
_Description :_ Le capteur DHT fonctionnait de manière aléatoire, ce qui rendait la collecte de
données imprévisible.
_Impact_ : L'imprécision des données de température et d'humidité peut compromettre l'analyse
de l'environnement, rendant les décisions basées sur ces informations peu fiables.
_Solution :_ Cela pourrait nécessiter une vérification des connexions, du code ou même un
remplacement du capteur.


**3. Problème d’alimentation**
_Description_ : L'utilisation d'une seule pile de 9V ne suffisait pas à alimenter l'ensemble de
l'appareil.
_Impact_ : Un problème d'alimentation peut entraîner des pannes intermittentes ou un
fonctionnement instable du système. Cela peut limiter la durée d'utilisation du robot.
_Solution :_ Cela pourrait nécessiter l'utilisation de plusieurs batteries ou d'une source
d'alimentation externe.

## Conclusion

En résumé, ce robot de surveillance est un projet éducatif simple mais efficace, qui peut être
facilement adapté et amélioré pour répondre à diverses applications de surveillance. Son
aspect modulaire en fait un outil pédagogique intéressant pour explorer les domaines de la
robotique et de l'automatisation.
