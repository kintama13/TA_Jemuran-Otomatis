// Sensor Kelembapan Tanah (ADC)
#define SENSOR_KELEMBAPAN_PIN 34   // pin ADC ESP32

void setup() {
  Serial.begin(115200);
}

void loop() {
  int nilaiADC = analogRead(SENSOR_KELEMBAPAN_PIN);

  Serial.print("Nilai ADC: ");
  Serial.println(nilaiADC);

  delay(1000); // baca setiap 1 detik
}
