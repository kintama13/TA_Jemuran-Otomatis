#define SENSOR_KELEMBABAN_PIN 34

int sensorKelembapan = 0;
float hasilRumus = 0;
float presentasePakaian = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_KELEMBABAN_PIN, INPUT);
} 

void loop() {
  sensorKelembapan = analogRead(SENSOR_KELEMBABAN_PIN);

  float x = sensorKelembapan;
  
  if (x >= 3000 && x <= 4095) {
    presentasePakaian = 0;
  } else {
    // polynimial orde - 2
    hasilRumus = 4.67e-05 * (x * x) - 0.3294 * x + 568.3112;
    float y = hasilRumus;

    presentasePakaian = constrain(hasilRumus, 0, 100); 
    presentasePakaian = round(hasilRumus); 
  }

  Serial.print("ADC: ");
  Serial.print(sensorKelembapan);
  Serial.print(" | Persentase: ");
  Serial.print(presentasePakaian);
  Serial.println(" %");

  delay(1000);
}