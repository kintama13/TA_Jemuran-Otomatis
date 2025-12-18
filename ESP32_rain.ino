#define SENSOR_HUJAN_DO_PIN 32

int statusSebelumnya = HIGH;           // awal: tidak hujan
unsigned long waktuSebelumnya = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_HUJAN_DO_PIN, INPUT_PULLUP);

  Serial.println("Output | Waktu Respon (detik)");
}

void loop() {
  int statusSekarang = digitalRead(SENSOR_HUJAN_DO_PIN);
  unsigned long waktuSekarang = millis();

  // Jika terjadi perubahan kondisi
  if (statusSekarang != statusSebelumnya) {

    // Hitung waktu respon (detik)
    float waktuRespon = (waktuSekarang - waktuSebelumnya) / 1000.0;

    // 1 = Hujan, 0 = Tidak hujan
    int outputHujan = (statusSekarang == LOW) ? 1 : 0;

    Serial.print(outputHujan);
    Serial.print(" | ");
    Serial.print(waktuRespon, 2);
    Serial.println(" s");

    // Update nilai sebelumnya
    statusSebelumnya = statusSekarang;
    waktuSebelumnya = waktuSekarang;
  }

  delay(20); // sampling cepat
}
