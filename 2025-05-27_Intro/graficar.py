import numpy as np
import matplotlib.pyplot as plt

# Cargar datos
data = np.loadtxt("millikan.txt")
x, y = data[:, 0], data[:, 1]

# Calcular m (pendiente) y b (intercepto)
m = (np.mean(x * y) - (np.mean(x) * np.mean(y))) / (np.mean(x**2) - np.mean(x)**2)
b = np.mean(y) - m * np.mean(x)

# Constantes físicas
e = 1.602176634e-19  # Carga fundamental (C)
h_calculado = m * e   # h = m * e (de V = (h/e)ν - φ)
phi = -b              # φ = -b

# Crear texto para la leyenda
leyenda_ajuste = (
    f"Ajuste lineal:\n"
    f"$V = (h/e)\\nu - \\phi$\n"
    f"$h = {h_calculado:.4e}$ J·s\n"
    f"$\\phi = {phi:.4e}$ V"
)

# Configurar gráfica
plt.figure(figsize=(10, 6))
plt.scatter(x, y, color="blue", label="Datos experimentales")
plt.plot(x, m * x + b, color="red", label=leyenda_ajuste)

# Añadir título y etiquetas
plt.xlabel("Frecuencia ($\\nu$) [Hz]", fontsize=12)
plt.ylabel("Voltaje (V) [V]", fontsize=12)
plt.title("Experimento de Millikan: Efecto fotoeléctrico", fontsize=14)
plt.legend(fontsize=10, loc="best", framealpha=1)
plt.grid(True)

# Guardar en PDF
plt.savefig("millikan_ajuste.pdf", bbox_inches="tight", format="pdf")
print("Gráfica guardada como 'millikan_ajuste.pdf'")
plt.show()