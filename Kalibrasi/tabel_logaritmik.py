import numpy as np
import matplotlib.pyplot as plt
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
# Regresi Logaritmik
# Bentuk umum: y = a + b * ln(x)
# -------------------------------
ln_x = np.log(x)
coef = np.polyfit(ln_x, y, 1)  # fitting linear terhadap ln(x)
b, a = coef                    # b = koefisien ln(x), a = konstanta

# Prediksi nilai
y_pred = a + b * np.log(x)

# Hitung R²
r2 = r2_score(y, y_pred)

# Buat kurva halus untuk tampilan grafik
x_fit = np.linspace(min(x), max(x), 200)
y_fit = a + b * np.log(x_fit)

# -------------------------------
# Plot hasil regresi logaritmik
# -------------------------------
plt.scatter(x, y, color='blue', label='Data Kalibrasi')
plt.plot(x_fit, y_fit, 'r--', label='Regresi Logaritmik')

plt.title("Grafik Regresi Logaritmik")
plt.xlabel("Nilai Sensor")
plt.ylabel("Kelembaban (%)")
plt.legend()
plt.grid(True)

# -------------------------------
# Tampilkan persamaan dan nilai R² di grafik
# -------------------------------
plt.text(
    min(x) + 200, max(y) - 40,
    f"y = {a:.4f} + {b:.4f}ln(x)\nR² = {r2:.4f}",
    fontsize=10
)

plt.show()

# -------------------------------
# Cetak hasil ke terminal
# -------------------------------
print("=== HASIL REGRESI LOGARITMIK ===")
print(f"Persamaan: y = {a:.4f} + {b:.4f}ln(x)")
print(f"R² = {r2:.4f}")
