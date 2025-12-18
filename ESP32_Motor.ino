#include <AccelStepper.h>

#define LANGKAH_PER_REV 2048

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

AccelStepper motor1(AccelStepper::HALF4WIRE, M1_PIN1, M1_PIN3, M1_PIN2, M1_PIN4);
AccelStepper motor2(AccelStepper::HALF4WIRE, M2_PIN1, M2_PIN3, M2_PIN2, M2_PIN4);

unsigned long startTime;
bool running = true;

void setup() {
  Serial.begin(115200);
  // Kecepatan Normal
  motor1.setMaxSpeed(500);
  motor1.setAcceleration(300);
  motor2.setMaxSpeed(500);
  motor2.setAcceleration(300);

  // Kecepatan Rendah
  motor1.setMaxSpeed(200);
  motor1.setAcceleration(100);
  motor2.setMaxSpeed(200);
  motor2.setAcceleration(100);

  // Kecepatan Tinggi
  motor1.setMaxSpeed(1000);
  motor1.setAcceleration(600);
  motor2.setMaxSpeed(1000);
  motor2.setAcceleration(600);

  // Motor Berputar Searah Jarum Jam
  motor1.moveTo(LANGKAH_PER_REV);
  motor2.moveTo(LANGKAH_PER_REV);

  // Motor Berputar Berlawanan Arah Jarum Jam
  motor1.moveTo(-LANGKAH_PER_REV);
  motor2.moveTo(-LANGKAH_PER_REV);

  // Pengujian Kecepatan Rendah
  motor1.moveTo(LANGKAH_PER_REV / 2);
  motor2.moveTo(-LANGKAH_PER_REV / 2);

  // Pengujian Kecepatan Tinggi
  motor1.moveTo(LANGKAH_PER_REV * 2);
  motor2.moveTo(-LANGKAH_PER_REV * 2);

  // Uji Ketahanan Rotasi
  motor1.moveTo(LANGKAH_PER_REV * 100);
  motor2.moveTo(-LANGKAH_PER_REV * 100);
}

void loop() {
  motor1.run();
  motor2.run();

  // Ketahanan Rotasi Selama 2 Menit
  if (running) {
    motor1.run();
    motor2.run();

    if (millis() - startTime >= 120000) { // 2 menit
      running = false;
      motor1.stop();
      motor2.stop();
      Serial.println("Pengujian selesai: kedua motor berhenti setelah 2 menit");
    }
  }

}
