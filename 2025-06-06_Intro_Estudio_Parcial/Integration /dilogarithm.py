import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

def load_data():
    """Carga los datos del archivo generado por C++"""
    try:
        data = np.loadtxt('dilog.dat', comments='#')
        return data
    except FileNotFoundError:
        print("Error: No se encontró el archivo 'dilog.dat'")
        print("Ejecuta primero el programa C++ para generar los datos")
        exit(1)

def configure_plot_style():
    """Configura un estilo limpio sin dependencias externas"""
    plt.rcParams.update({
        'font.size': 12,
        'figure.titlesize': 14,
        'axes.labelsize': 12,
        'xtick.labelsize': 10,
        'ytick.labelsize': 10,
        'axes.grid': True,
        'grid.alpha': 0.3,
        'grid.linestyle': '--'
    })

def create_plot(data):
    """Crea y configura el gráfico"""
    fig, ax = plt.subplots(figsize=(10, 6))
    
    x = data[:, 0]
    li2 = data[:, 1]
    
    ax.plot(x, li2, 'b-', linewidth=2, label='Li₂(x)')
    
    # Configuraciones del gráfico
    ax.set_title('Función Di-Logaritmo (Dilogarithm)')
    ax.set_xlabel('x')
    ax.set_ylabel('Li₂(x)')
    ax.legend()
    
    # Marcadores especiales
    pi_squared_over_6 = np.pi**2/6
    ax.axhline(y=pi_squared_over_6, color='r', linestyle='--', alpha=0.5)
    ax.text(0.1, pi_squared_over_6+0.05, 'π²/6', color='r')
    
    # Ajustar límites del eje y
    ax.set_ylim(0, pi_squared_over_6 + 0.1)
    
    return fig

def save_to_pdf(fig):
    """Guarda la figura en PDF"""
    try:
        with PdfPages('dilog_plot.pdf') as pdf:
            pdf.savefig(fig)
            plt.close()
        print("✓ Gráfico guardado exitosamente en 'dilog_plot.pdf'")
    except Exception as e:
        print(f"Error al guardar el PDF: {str(e)}")

def main():
    # Configurar estilo
    configure_plot_style()
    
    # Cargar datos
    data = load_data()
    
    # Crear gráfico
    fig = create_plot(data)
    
    # Guardar PDF
    save_to_pdf(fig)

if __name__ == "__main__":
    main()