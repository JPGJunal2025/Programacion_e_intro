import matplotlib.pyplot as plt
import numpy as np
from sympy import primerange
from math import sqrt

# Generar al menos 200 números primos
primos = list(primerange(1, 1250))  # Esto da más de 200 primos

# Calcular las normas de los primeros 100 pares
n_vals = np.arange(1, 101)
normas = [sqrt(primos[2*i-2]**2 + primos[2*i-1]**2) for i in n_vals]

# Graficar
plt.figure(figsize=(8, 5))
plt.plot(n_vals, normas, 'o-', label=r'$\sqrt{p^2 + q^2}$')
plt.xlabel(r'$n$')
plt.ylabel('Norma')
plt.title('Norma de pares de primos consecutivos vs. $n$')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("norma_primos.pdf")  # Guarda el gráfico como PDF
plt.show()
