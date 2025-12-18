import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import r2_score

# -------------------------------
# Data contoh (silakan ganti sesuai data kamu)
# -------------------------------
x = np.array([
    2133,
    2260,
    2368,
    2406,
    2482,
    2513,
    2579,
    2673,
    3108,
    4095
])
y = np.array([
    100,
    51,
    45,
    41,
    35,
    32,
    26,
    21,
    11,
    0
])

# -------------------------------
# Regresi Linear (orde 1)
# -------------------------------
coef = np.polyfit(x, y, 1)   # dapatkan koefisien linear
a, b = coef                  # a = slope, b = intercept

# Buat garis regresi linear
x_fit = np.linspace(min(x), max(x), 100)
y_fit = a * x_fit + b

# Hitung R²
y_pred = a * x + b
r2 = r2_score(y, y_pred)

# -------------------------------
# Plot grafik
# -------------------------------
plt.scatter(x, y, color='blue', label='Data Kalibrasi')
plt.plot(x_fit, y_fit, 'r--', label='Regresi Linear')

# Judul dan label sumbu
plt.title("Grafik Regresi Linear")
plt.xlabel("Nilai Sensor")
plt.ylabel("Kelembaban (%)")

# -------------------------------
# Pembulatan angka agar rapi
# -------------------------------
a_rounded = round(a, 5)
b_rounded = round(b, 2)

# -------------------------------
# Tampilkan rumus dan nilai R² di grafik
# -------------------------------
plt.text(
    min(x) + 200, max(y) - 40,
    f"y = {a:.5f}x + {b:.2f}\nR² = {r2:.4f}",
    fontsize=10
)

# -------------------------------
# Tampilkan legenda dan grid
# -------------------------------
plt.legend()
plt.grid(True)
plt.show()

# -------------------------------
# Cetak hasil di terminal
# -------------------------------
print(f"Persamaan regresi linear: y = {a_rounded}x + {b_rounded}")
print(f"R² = {r2:.4f}")
