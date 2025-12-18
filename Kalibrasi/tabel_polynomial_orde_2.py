import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import r2_score

# Data contoh (silakan ganti sesuai data kamu)
x = np.array([
    2133
    ,2260
    ,2368
    ,2406
    ,2482
    ,2513
    ,2579
    ,2673
    ,3108
    ,4095
])
y = np.array([
    100
    ,51
    ,45
    ,41
    ,35
    ,32
    ,26
    ,21
    ,11
    ,0
])

# -------------------------------
# Regresi Polynomial orde 2
# -------------------------------
coef = np.polyfit(x, y, 2)   # dapatkan koefisien
a, b, c = coef               # a = x², b = x, c = konstanta

# Buat garis kurva hasil regresi
x_fit = np.linspace(min(x), max(x), 100)
y_fit = a * x_fit**2 + b * x_fit + c

# Hitung R²
y_pred = a*x**2 + b*x + c
r2 = r2_score(y, y_pred)

# -------------------------------
# Plot grafik
# -------------------------------
plt.scatter(x, y, color='blue', label='Data Kalibrasi')
plt.plot(x_fit, y_fit, 'b--', label='Regresi Polynomial (Orde 2)')

# Judul dan label sumbu
plt.title("Grafik Regresi Polinomial Orde-2")
plt.xlabel("Nilai Sensor")
plt.ylabel("Kelembaban (%)")

# -------------------------------
# Pembulatan angka agar rapi
# -------------------------------
a_rounded = round(a, 5)
b_rounded = round(b, 4)
c_rounded = round(c, 4)

# Tampilkan rumus dan nilai R² di grafik
plt.text(
    min(x) + 200, max(y) - 40,
    f"y = {a:.2e}x² + {b:.4f}x + {c:.4f}\nR² = {r2:.4f}",
    fontsize=10
)

# Tampilkan legenda dan grid
plt.legend()
plt.grid(True)
plt.show()
