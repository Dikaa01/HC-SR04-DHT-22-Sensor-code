#include "DHT.h"
DHT dht(2, DHT11);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 11;
const int echoPin = 12;
long duration;
float distance;
float c;
float d;

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init(); 
  lcd.backlight(); 

 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();

  if (isnan(kelembaban) || isnan(suhu)) {
    Serial.println(F("Gagal Baca Data DHT sensor!"));
    return;
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  d = duration * 0.034 / 2;
  c = (331.2+(0.606*suhu)+(0.0124*kelembaban))/10000;  
  distance = duration * c / 2;
  
  //d = duration * 0,034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  Serial.println(c);
  Serial.println(d);
  
  Serial.print("Kelembaban: ");
  Serial.println(kelembaban);
  Serial.print("Suhu: ");
  Serial.println(suhu);

   // Tampilkan data di LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(kelembaban);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(suhu);
  lcd.print(" %");
  delay(2000); // Tampilkan selama 2 detik

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  delay(2000); // Tampilkan selama 2 detik
}
