import matplotlib.pyplot as plt
import numpy as np

# Lee datos del archivo (¡incluyendo el error del método de 5 puntos!)
x, h, fr, cr, fp, fe, ce, fpe = np.loadtxt("derivatives.txt", unpack=True)

# Crea la figura
fig, ax = plt.subplots()

# Traza los errores ya existentes
ax.plot(h, fe, '-o', label='error forward')
ax.plot(h, ce, '-s', label='error central')

# Nuevo: error del método de cinco puntos
ax.plot(h, fpe, '-^', label='error cinco puntos')

# Escalas logarítmicas
ax.set_xscale('log')
ax.set_yscale('log')

# Etiquetas
ax.set_xlabel('$h$')
ax.set_ylabel('error')
ax.legend()

# Guarda el gráfico
fig.savefig('deriv.pdf')
