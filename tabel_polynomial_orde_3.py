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
# Regresi Polynomial orde 3
# Bentuk umum: y = a*x^3 + b*x^2 + c*x + d
# -------------------------------
coef = np.polyfit(x, y, 3)
a, b, c, d = coef

# Prediksi nilai y berdasarkan model
y_pred = a*x**3 + b*x**2 + c*x + d

# Hitung R²
r2 = r2_score(y, y_pred)

# Buat data halus untuk kurva
x_fit = np.linspace(min(x), max(x), 200)
y_fit = a*x_fit**3 + b*x_fit**2 + c*x_fit + d

# -------------------------------
# Plot hasil regresi polynomial orde 3
# -------------------------------
plt.scatter(x, y, color='blue', label='Data Kalibrasi')
plt.plot(x_fit, y_fit, 'r--', label='Regresi Polynomial (Orde 3)')

plt.title("Regresi Polynomial Orde 3 (Kalibrasi Sensor)")
plt.xlabel("Nilai Sensor")
plt.ylabel("Kelembaban (%)")
plt.legend()
plt.grid(True)

# -------------------------------
# Tampilkan persamaan dan nilai R² di grafik
# -------------------------------
plt.text(
    min(x) + 200, max(y) - 40,
    f"y = {a:.2e}x³ + {b:.2e}x² + {c:.4f}x + {d:.4f}\nR² = {r2:.4f}",
    fontsize=10
)

plt.show()

# -------------------------------
# Cetak hasil ke terminal
# -------------------------------
print("=== HASIL REGRESI POLYNOMIAL ORDE 3 ===")
print(f"Persamaan: y = {a:.2e}x³ + {b:.2e}x² + {c:.4f}x + {d:.4f}")
print(f"R² = {r2:.4f}")
