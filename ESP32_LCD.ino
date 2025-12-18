#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// Inisialisasi LCD dengan alamat I2C
LiquidCrystal_PCF8574 lcd(0x27);

void setup() {
  lcd.begin(16, 2);  // Ukuran LCD: 16 kolom, 2 baris
  lcd.setBacklight(255); // Aktifkan lampu latar (0-255)

  // Teks 1
  lcd.setCursor(0, 0);   // Baris pertama
  lcd.print("Kelembapan: 100%");

  // Teks 2
  lcd.setCursor(0, 0);   // Baris pertama
  lcd.print("Status: Hujan");

  // Teks 3
  lcd.setCursor(0, 0);   // Baris pertama
  lcd.print("Pakaian Kering");
}

void loop() {
  // Tidak ada operasi tambahan
}
