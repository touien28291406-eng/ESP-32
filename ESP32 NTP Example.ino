#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Khai bao chan cam bien DHT22
#define DHTPIN 4
#define DHTTYPE DHT22

// Khoi tao cam bien
DHT dht(DHTPIN, DHTTYPE);

// Khoi tao LCD I2C
// Dia chi I2C thuong dung: 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  // Khoi dong DHT22
  dht.begin();

  // Khoi dong LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("DO NHIET DO");
  lcd.setCursor(0, 1);
  lcd.print("DO DO AM DHT22");

  delay(2000);
  lcd.clear();
}

void loop() {
  // Doc nhiet do va do am
  float nhietdo = dht.readTemperature();
  float doam = dht.readHumidity();

  // Kiem tra loi cam bien
  if (isnan(nhietdo) || isnan(doam)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Loi cam bien!");
    Serial.println("Khong doc duoc DHT22");
    delay(2000);
    return;
  }

  // Hien thi nhiet do
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do: ");
  lcd.print(nhietdo, 1);
  lcd.print((char)223);
  lcd.print("C ");

  // Hien thi do am
  lcd.setCursor(0, 1);
  lcd.print("Do am: ");
  lcd.print(doam, 1);
  lcd.print("%   ");

  // Gui du lieu len may tinh
  Serial.print("Nhiet do: ");
  Serial.print(nhietdo);
  Serial.print(" C | Do am: ");
  Serial.print(doam);
  Serial.println(" %");

  delay(2000);
}