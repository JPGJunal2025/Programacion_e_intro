import matplotlib.pyplot as plt
import numpy as np

# 1. Leer datos del archivo generado por tu C++
data = np.loadtxt("integration.txt")
N = data[:, 0]
error_trap = data[:, 1]
error_simp = data[:, 2]
error_trap_r = data[:, 3]
error_simp_r = data[:, 4]

# 2. Configurar el gráfico log-log
plt.figure(figsize=(8, 6))
plt.loglog(N, error_trap, 'bo-', label='error trap', markersize=4, linewidth=1)
plt.loglog(N, error_simp, 'rs-', label='error simp', markersize=4, linewidth=1)
plt.loglog(N, error_trap_r, 'g*-', label='error richardson trap', markersize=6, linewidth=1)
plt.loglog(N, error_simp_r, 'm*-', label='error richardson simp', markersize=6, linewidth=1)

# 3. Ajustes de ejes y estilo
plt.xlabel('N', fontsize=11)
plt.ylabel('Error', fontsize=11)
plt.legend(fontsize=10, frameon=True)
plt.grid(True, which="both", linestyle=':', alpha=0.7)

# 4. Guardar como PDF vectorial (sin pérdida de calidad)
plt.savefig('errores_integracion.pdf', format='pdf', bbox_inches='tight')

print("Gráfico guardado como 'errores_integracion.pdf'")