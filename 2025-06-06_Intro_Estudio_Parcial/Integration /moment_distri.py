import numpy as np
import matplotlib.pyplot as plt
from scipy.special import gamma

alpha = 2.0
beta = 1.0
k_values = np.arange(1, 11)

# Theoretical moments
theoretical = gamma(alpha + k_values) / (beta**k_values * gamma(alpha))

# Read calculated values from C++ output (you'll need to save them to a file first)
# calculated = np.array([...]) 

plt.figure(figsize=(12, 6))

# Use logarithmic scale if moments grow exponentially
plt.semilogy(k_values, theoretical, 'bo-', label='Teórico', markersize=8)
# plt.semilogy(k_values, calculated, 'rx--', label='Calculado')

plt.title(f'Momentos de la Distribución Gamma\n(α={alpha}, β={beta})', fontsize=14)
plt.xlabel('Orden del momento (k)', fontsize=12)
plt.ylabel('Valor del momento (escala log)', fontsize=12)
plt.xticks(k_values)
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend(fontsize=12)

# Add exact values as text
for k, val in zip(k_values, theoretical):
    plt.text(k, val*1.2, f'{val:.2f}', ha='center', va='bottom')

plt.tight_layout()
plt.savefig('gamma_moments_log.pdf')
plt.show()