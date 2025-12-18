import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import r2_score

# Data kalibrasi
x = np.array([2133, 2260, 2368, 2406, 2482, 2513, 2579, 2673, 3108, 4095])
y = np.array([100, 51, 45, 41, 35, 32, 26, 21, 11, 0])

# Regresi polinomial orde 2
coef = np.polyfit(x, y, 2)
a, b, c = coef

# Rentang x
x_fit = np.linspace(min(x), max(x), 300)
y_fit = a * x_fit**2 + b * x_fit + c

# Rectifikasi: nilai negatif = 0, dan nilai setelah nol pertama = 0 juga
y_fit_rectified = np.copy(y_fit)
zero_idx = np.where(y_fit_rectified <= 0)[0]
if len(zero_idx) > 0:
    y_fit_rectified[zero_idx[0]:] = 0  # setelah y <= 0, tetap 0

# Hitung R² (tanpa rectifikasi)
y_pred = a*x**2 + b*x + c
r2 = r2_score(y, y_pred)

# Plot
plt.scatter(x, y, color='blue', label='Data Kalibrasi')
plt.plot(x_fit, y_fit, 'b--', label='Regresi Polynomial Orde-2')
plt.plot(x_fit, y_fit_rectified, 'r-', linewidth=2, label='Regresi Polynomial Orde-2 (Rektifikasi)')

plt.title("Grafik Regresi Polinomial Orde-2 (Rektifikasi)")
plt.xlabel("Nilai Sensor")
plt.ylabel("Kelembapan (%)")

plt.text(min(x)+200, max(y)-40,
         f"y = {a:.2e}x² + {b:.4f}x + {c:.4f}\nR² = {r2:.4f}",
         fontsize=10)

plt.legend()
plt.grid(True)
plt.show()
