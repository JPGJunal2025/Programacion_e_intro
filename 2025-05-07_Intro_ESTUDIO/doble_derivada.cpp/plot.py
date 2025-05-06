import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Leer el archivo como DataFrame
column_names = [
    "x", "h", 
    "forward_result", "central_result", "second_result", 
    "error_forward", "error_central", "error_second"
]

try:
    df = pd.read_csv("derivatives.txt", delim_whitespace=True, names=column_names)
except FileNotFoundError:
    print("Error: El archivo 'derivatives.txt' no se encontró.")
    exit()

# Mostrar los primeros datos como verificación
print("\nDatos cargados:")
print(df.head())

# Graficar los errores
plt.figure(figsize=(8, 6))
plt.loglog(df["h"], df["error_forward"], 'o-', label='Error Forward')
plt.loglog(df["h"], df["error_central"], 's-', label='Error Central')
plt.loglog(df["h"], df["error_second"], '^-', label='Error Segunda Derivada')

plt.xlabel('Paso h')
plt.ylabel('Error relativo')
plt.title('Errores de derivadas numéricas')
plt.legend()
plt.grid(True, which="both", ls="--")
plt.tight_layout()

# Guardar imagen en PDF
output_path = os.path.join(os.path.dirname(__file__), "derivative_errors.pdf")
plt.savefig(output_path, dpi=300, format='pdf')
print(f"\nGráfico guardado como: {output_path}")

plt.show()
