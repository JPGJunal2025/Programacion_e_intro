import numpy as np
import matplotlib.pyplot as plt
import subprocess
import os
from matplotlib.backends.backend_pdf import PdfPages

# Matrix sizes to test
sizes = [4, 8, 16, 32, 64, 128, 256, 512, 1024]
seed = 10  # Fixed seed for reproducibility
times = []

# Run the C++ program for each matrix size and measure time
for N in sizes:
    # Compile the program if not already compiled
    if not os.path.exists('matrix_mult'):
        subprocess.run(['g++', '-O3', '-o', 'matrix_mult', 'matrix_mult.cpp'])
    
    # Run the program and capture output
    result = subprocess.run(['./matrix_mult', str(N), str(seed)], 
                           capture_output=True, text=True)
    
    # Parse the output to get the time
    output_lines = result.stdout.split('\n')
    time = float(output_lines[-2])  # The time is the second to last line
    times.append(time)

# Normalize times by the time at N=4
base_time = times[0]
normalized_times = [t / base_time for t in times]

# Create PDF with the plot
with PdfPages('matrix_multiplication_performance.pdf') as pdf:
    plt.figure(figsize=(10, 6))
    plt.loglog(sizes, normalized_times, 'bo-', label='Tiempos medidos')
    plt.loglog(sizes, [ (n/4)**3 for n in sizes ], 'r--', label='Referencia O(N³)')

    # Add labels and title in Spanish
    plt.xlabel('Tamaño de matriz N (escala logarítmica)')
    plt.ylabel('Tiempo normalizado (escala logarítmica)')
    plt.title('Rendimiento de Multiplicación de Matrices (Normalizado a N=4)')
    plt.legend()
    plt.grid(True, which="both", ls="-")
    
    # Save to PDF
    pdf.savefig()
    plt.close()

    # Optionally add a second page with raw data
    plt.figure(figsize=(10, 6))
    plt.axis('off')
    plt.text(0.1, 0.9, "Datos Crudos:", fontsize=12, weight='bold')
    plt.text(0.1, 0.7, f"Tamaños de matriz: {sizes}", fontsize=10)
    plt.text(0.1, 0.6, f"Tiempos medidos: {[f'{t:.6f}' for t in times]}", fontsize=10)
    plt.text(0.1, 0.5, f"Tiempos normalizados: {[f'{t:.6f}' for t in normalized_times]}", fontsize=10)
    pdf.savefig()
    plt.close()

print("Gráfica guardada en 'matrix_multiplication_performance.pdf'")
print("Este archivo PDF contiene:")
print("1. Gráfica log-log de rendimiento")
print("2. Página con datos numéricos crudos")