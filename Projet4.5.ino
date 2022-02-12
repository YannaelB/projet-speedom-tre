#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define trigPin 8
#define echoPin 9
#define trig 6
#define echo 7
#define trig2 5
#define echo2 4
int TempsInit = 0;
int TempsReel = 0;
int TempsSec = 0;
int TempsMil = 0;
int TempsInit2 = 0;
int TempsReel2 = 0;
int TempsSec2 = 0;
int TempsMil2 = 0;
int a = 0;
float b, c, d, e;
float v, t, km, ti, tf;
boolean detection_main = false;
boolean detection_main2 = false;
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  {
    lcd.init();
  }
}
void loop() {

 /* lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("Speedometre");*/
  boolean fin1 = false;
  boolean fin2 = false;
  boolean fin3 = false;
  boolean fin = false;
  boolean debut = true;


    float duration3, distance3;
   digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  
    digitalWrite(trig2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2, LOW);

    duration3 = pulseIn(echo2, HIGH);
    distance3 = (duration3 / 2) * 0.0344;
   /* if( (duration3 <1||duration3 > 5)&& detection_main == false ){
      Serial.print("ok");
    }*/
    
  //Serial.println(distance3);

  // calcul du premier chrono
  // on effectue le traitement suivant si aucune detection effectuee
  if( ( distance3>50||distance3<2 )&& detection_main == false){
   //Serial.println(" GOOD");
   TempsInit2 = (millis());
  TempsReel2 = (millis() - TempsInit2);
  TempsSec2 = (TempsReel2 /1000)%60;
  TempsMil2 = (TempsReel2 %1000)/10;
  // Serial.println(distance3);
  
  //intialisation du temps-secondes
  int secondes2 =millis()/1000;
  int TempsMil2 =millis()/10;
  lcd.backlight();
 /* lcd.setCursor(0, 1);
  lcd.print("chrono:");*/
   lcd.setCursor(0, 0);
  lcd.print(secondes2);
  lcd.setCursor(3,0);
  lcd.print("sec");
  lcd.setCursor(6, 0);
  lcd.print(TempsMil2);      
  ti = TempsMil2;  
 if( distance3<50 && distance3>2){
  lcd.clear();
 }
  

  }

  //distance3 distance du premier capteur
  if((distance3<50 &&  distance3 > 3) || detection_main2 == true ){
    detection_main = true;
    detection_main2 = true;

float duration2, distance2;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration2 = pulseIn(echo, HIGH);
    distance2 = (duration2 / 2) * 0.0344;
   // Serial.println(distance2);
    

  TempsInit = (millis());
  TempsReel = (millis() - TempsInit);
  TempsSec = (TempsReel /1000)%60;
  TempsMil = (TempsReel %1000)/10;
  
  //intialisation du temps-secondes
  int secondes =millis()/1000;
  int TempsMil =millis()/10;
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print(secondes);
  lcd.setCursor(3,1);
  lcd.print("sec");
  lcd.setCursor(6, 1);
  lcd.print(TempsMil);      
 //Serial.print(TempsMil);
  t = TempsMil;  

   if(distance2<70 && distance2>3){
      lcd.backlight();
      lcd.setCursor(12, 1);
      lcd.print("f");
      delay(3000);
      lcd.clear();
      fin = true;
      
      
       
  }
 }
  if (fin) {
    float duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) * 0.0344;
    b = distance;
    fin1 = true;
   /* if (distance >= 400 || distance <= 2) {
      lcd.print("Out of range");
      delay(500);
    }
    else {
      lcd.backlight();// Envoi du message
      lcd.setCursor(0, 0);
      lcd.print(distance);
      lcd.print(" cm");
      delay(500);
    }
    delay(500);
    lcd.clear();*/
  }
  
  if (fin1) {
    float duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) * 0.0344;
    c = distance;
    fin2= true;
    /*if (distance >= 400 || distance <= 2) {
      lcd.print("Out of range");
      delay(500);
    }
    else {
      lcd.backlight();// Envoi du message
      lcd.setCursor(0, 0);
      lcd.print(distance);
      lcd.print(" cm");
      delay(500);
    }
    delay(500);
    lcd.clear();*/
  }
  
  if (fin2) {
    float duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) * 0.0344;
    d = distance;
    fin3= true;
  /* if (distance >= 400 || distance <= 2) {
      lcd.print("Out of range");
      delay(500);
    }
    else {
      lcd.backlight();// Envoi du message
      lcd.setCursor(0, 0);
      lcd.print(distance);
      lcd.print(" cm");
      delay(500);
    }
    delay(500);
    lcd.clear();*/
 }

  
  if (fin3) {
    Serial.println("on est dans fin3");
    float e = b + c + d;
    float dist = e / 3;
    float tf = (t - ti) / 100;
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(dist);
    lcd.print(" cm");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(tf);
    lcd.print(" sec");
    delay(5000);
    lcd.clear();
    float v = (dist/100) / tf;
    float km = v * 3.6;
    lcd.print(v);
    lcd.print(" m/s");
    lcd.setCursor(0, 1);
    lcd.print(km);
    lcd.print(" km/h");
    exit(0);  


  }

}
