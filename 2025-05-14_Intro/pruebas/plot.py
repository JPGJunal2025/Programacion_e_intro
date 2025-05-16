import matplotlib.pyplot as plt
import numpy as np

# Leer datos
N, et, es, etr, esr = np.loadtxt("integration.txt", unpack=True)

# Configuración del gráfico
fig, ax = plt.subplots(figsize=(8, 6))

# Curvas de error (agregué markersize para mejor visualización)
ax.plot(N, et, '-o', markersize=5, label='Trapecio (orden 2)')
ax.plot(N, es, '-s', markersize=5, label='Simpson (orden 4)')
ax.plot(N, etr, '-*', markersize=6, label='Trapecio + Richardson')
ax.plot(N, esr, '-D', markersize=5, label='Simpson + Richardson')

# Escalas logarítmicas
ax.set_xscale('log')
ax.set_yscale('log')

# Etiquetas (usando LaTeX para formato matemático)
ax.set_xlabel('$N$ (número de intervalos)', fontsize=12)
ax.set_ylabel('Error relativo', fontsize=12)
ax.set_title('Error en métodos de integración', pad=15)

# Leyenda y grid
ax.legend(fontsize=10, framealpha=0.9)
ax.grid(True, which="both", ls="--", alpha=0.4)

# Ajustar layout y guardar
plt.tight_layout()
fig.savefig('integration.pdf', bbox_inches='tight')