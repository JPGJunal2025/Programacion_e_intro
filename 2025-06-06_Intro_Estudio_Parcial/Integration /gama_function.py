import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
import os

def verify_data_file():
    """Verifica que el archivo de datos existe y tiene contenido"""
    if not os.path.exists('gamma_cdf.dat'):
        raise FileNotFoundError("El archivo gamma_cdf.dat no existe. Ejecuta primero el programa C++.")
    if os.path.getsize('gamma_cdf.dat') == 0:
        raise ValueError("El archivo gamma_cdf.dat está vacío.")

def load_data():
    """Carga los datos del archivo"""
    return np.loadtxt('gamma_cdf.dat', comments='#')

def create_plot(data):
    """Crea el gráfico con los datos"""
    x = data[:, 0]
    simpson_cdf = data[:, 1]
    gauss_cdf = data[:, 2]

    plt.figure(figsize=(10, 6))
    plt.plot(x, simpson_cdf, 'b-', label='Método de Simpson', linewidth=2)
    plt.plot(x, gauss_cdf, 'r--', label='Método Gauss-Legendre', linewidth=2)
    
    plt.title('Función de Distribución Acumulativa Gamma\n(α=7.5, β=1.0)', fontsize=14)
    plt.xlabel('x', fontsize=12)
    plt.ylabel('CDF(x)', fontsize=12)
    plt.legend(fontsize=12, loc='lower right')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.xlim(0, 20)
    plt.ylim(0, 1.05)

def save_to_pdf():
    """Guarda el gráfico en PDF"""
    with PdfPages('gamma_cdf_plot.pdf') as pdf:
        pdf.savefig()
        plt.close()
    print(f"✓ Gráfico guardado correctamente en: {os.path.abspath('gamma_cdf_plot.pdf')}")

def main():
    try:
        # Paso 1: Verificar archivo de datos
        verify_data_file()
        
        # Paso 2: Cargar datos
        data = load_data()
        
        # Paso 3: Crear gráfico
        create_plot(data)
        
        # Paso 4: Guardar PDF
        save_to_pdf()
        
    except Exception as e:
        print(f"Error: {str(e)}")
        print("Posibles soluciones:")
        print("1. Asegúrate de haber ejecutado primero el programa C++")
        print("2. Verifica que gamma_cdf.dat tenga datos válidos")
        print("3. Comprueba que tengas permisos de escritura")

if __name__ == "__main__":
    main()