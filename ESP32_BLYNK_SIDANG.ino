#define BLYNK_TEMPLATE_ID "TMPL67ogi-8S7"
#define BLYNK_TEMPLATE_NAME "Pawang Hujan"
#define BLYNK_AUTH_TOKEN "IG2PtWj5HwV0e2USi033Uafa92uFgAOx"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <AccelStepper.h>
#include <Preferences.h>

// WiFi
char ssid[] = "Harahap family";
char pass[] = "Harahapfamily4666026";

// Sensor Hujan
#define SENSOR_HUJAN_DO_PIN 32
// Sensor Kelembapan
#define SENSOR_KELEMBAPAN_PIN1 34
#define SENSOR_KELEMBAPAN_PIN2 35
// Motor 1
#define M1_PIN1 16
#define M1_PIN2 17
#define M1_PIN3 18
#define M1_PIN4 19
// Motor 2
#define M2_PIN1 25
#define M2_PIN2 26
#define M2_PIN3 27
#define M2_PIN4 14

LiquidCrystal_PCF8574 lcd(0x27);
AccelStepper motor1(AccelStepper::HALF4WIRE, M1_PIN1, M1_PIN3, M1_PIN2, M1_PIN4);
AccelStepper motor2(AccelStepper::HALF4WIRE, M2_PIN1, M2_PIN3, M2_PIN2, M2_PIN4);

BlynkTimer timer;
int lastStatus = -1;
int lastStatusKering = -1;
Preferences preferences;
int nilaiBlynk = 0;
int posisiMotor = 0;
bool motorSedangBergerak = false;
int statusKelembapan1 = 0;
int statusKelembapan2 = 0;
int presentase1 = 0;
int presentase2 = 0;
int presentase = 0;

// Fungsi untuk membaca sensor hujan
void cekSensorHujan() {
  int statusHujan = digitalRead(SENSOR_HUJAN_DO_PIN);
  nilaiBlynk = (statusHujan == LOW) ? 1 : 0;
  Blynk.virtualWrite(V0, nilaiBlynk);

  // Mengirim Notifikasi Pada Aplikasi BLYNK
  if (nilaiBlynk != lastStatus) {
    if (nilaiBlynk == 1) {
      Blynk.logEvent("hujan", "⚠️ Hujan terdeteksi! Jemuran segera ditarik!");
    } else {
      Blynk.logEvent("cerah", "☀️ Cuaca cerah,Jemuran Keluar.");
    }
    lastStatus = nilaiBlynk; // Update status terakhir
  }
}

// Fungsi Membaca Sensor Kelembapan

// kalibrasi sensor kelembapan
int kalibrasiSensor(int x) {
  if(x >= 3000 && x <= 4095) {
    return x = 0;
  }
  float rumus = 4.67e-05 * (x * x) - 0.3294 * x + 568.3112;
  return round(constrain(rumus, 0, 100));
}

void cekSensorKelembapan() {
  statusKelembapan1 = analogRead(SENSOR_KELEMBAPAN_PIN1);
  statusKelembapan2 = analogRead(SENSOR_KELEMBAPAN_PIN2);

  presentase1 = kalibrasiSensor(statusKelembapan1);
  presentase2 = kalibrasiSensor(statusKelembapan2);

  Blynk.virtualWrite(V1, presentase1);
  Blynk.virtualWrite(V2, presentase2);

  presentase = max(presentase1, presentase2);
  int statusKering = (presentase < 25) ? 1 : 0;

  // mengirim notifikasi pada aplikasi blynk
  if(statusKering != lastStatusKering) {
    if (statusKering == 1) {
      Blynk.logEvent("kering", "👕 Pakaian sudah kering");
    }
    lastStatusKering = statusKering;
  }
}

// Fungsi Menarik Jemuran
void menarikJemuran() {
  if(motorSedangBergerak) return;
  motorSedangBergerak = true;

  motor1.setMaxSpeed(1000);
  motor2.setMaxSpeed(1000);
  motor1.setAcceleration(600);
  motor2.setAcceleration(600);

  // 12 Kali Putaran
  motor1.moveTo(-2048 * 12);
  motor2.moveTo(2048 * 12);

  while(motor1.distanceToGo() !=0 || motor2.distanceToGo() !=0) {
    motor1.run();
    motor2.run();
  }

  preferences.begin("jemuran", false);
  preferences.putInt("posisi", 1);
  preferences.end();

  posisiMotor = 1;
  motorSedangBergerak = false;
}

// Fungsi Mengeluarkan Jemuran
void mengeluarkanJemuran() {
  if(motorSedangBergerak) return;
  motorSedangBergerak = true;

  motor1.setMaxSpeed(1000);
  motor2.setMaxSpeed(1000);
  motor1.setAcceleration(600);
  motor2.setAcceleration(600);

  // 12 Kali Putaran
  motor1.moveTo(2048 * 12);
  motor2.moveTo(-2048 * 12);

  while(motor1.distanceToGo() !=0 || motor2.distanceToGo() !=0) {
    motor1.run();
    motor2.run();
  }

  preferences.begin("jemuran", false);
  preferences.putInt("posisi", 0);
  preferences.end();

  posisiMotor = 0;
  motorSedangBergerak = false;
}

// Rule base
void ruleBasedSystem(){
  if (motorSedangBergerak) return; 

  if (presentase < 25 && posisiMotor == 0) {
    menarikJemuran();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pakaian Kering ");
  }else if (nilaiBlynk == 1 && posisiMotor == 0){
    menarikJemuran();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status : Hujan");
  }else if (nilaiBlynk == 0 && presentase >= 25 && posisiMotor == 1){
    mengeluarkanJemuran();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status : Cerah");
  }
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setBacklight(255);

  preferences.begin("jemuran", true);
  posisiMotor = preferences.getInt("posisi", 0);
  preferences.end();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(SENSOR_HUJAN_DO_PIN, INPUT);
  pinMode(SENSOR_KELEMBAPAN_PIN1, INPUT);
  pinMode(SENSOR_KELEMBAPAN_PIN2, INPUT);

  timer.setInterval(1000L, cekSensorHujan);
  timer.setInterval(2000L, cekSensorKelembapan);
  timer.setInterval(1500L, ruleBasedSystem);
}

void loop() {
  Blynk.run();
  timer.run(); 
}
