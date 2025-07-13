import numpy as np
import matplotlib.pyplot as plt

# Leer los archivos de datos
euler_data = np.loadtxt('output-euler.txt')
heun_data = np.loadtxt('output-heun.txt')

# Extraer las columnas relevantes
x_euler = euler_data[:, 1]  # Segunda columna (posición x)
v_euler = euler_data[:, 2]   # Tercera columna (velocidad v)

x_heun = heun_data[:, 1]     # Segunda columna (posición x)
v_heun = heun_data[:, 2]     # Tercera columna (velocidad v)

# Configuración de la figura
plt.figure(figsize=(10, 6))
plt.rcParams['font.size'] = 12
plt.rcParams['axes.labelsize'] = 14
plt.rcParams['axes.titlesize'] = 16

# Graficar ambos métodos
plt.plot(x_euler, v_euler, label='Método de Euler', color='blue', alpha=0.7, linewidth=2)
plt.plot(x_heun, v_heun, label='Método de Heun', color='red', alpha=0.7, linewidth=2)

# Añadir elementos gráficos
plt.xlabel('Posición (x)')
plt.ylabel('Velocidad (v)')
plt.title('Comparación de Métodos: v vs x (ω = 4.376)')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.6)

# Ajustar márgenes y guardar como PDF
plt.tight_layout()
plt.savefig('comparacion_metodos.pdf', format='pdf', dpi=300, bbox_inches='tight')
plt.close()  # Cerrar la figura para liberar memoria