import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Cargar datos
gravity_data = np.loadtxt('trajectory_gravity.dat')
damped_data = np.loadtxt('trajectory_damped.dat')
ground_data = np.loadtxt('trajectory_ground.dat')

# Crear figura 3D
fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# Graficar trayectorias
ax.plot(gravity_data[:,0], gravity_data[:,1], gravity_data[:,2], 
        label='Solo gravedad', linewidth=2)
ax.plot(damped_data[:,0], damped_data[:,1], damped_data[:,2], 
        label='Con amortiguamiento', linestyle='--')
ax.plot(ground_data[:,0], ground_data[:,1], ground_data[:,2], 
        label='Con suelo', linestyle=':')

# Configurar gráfico
ax.set_xlabel('X position')
ax.set_ylabel('Y position')
ax.set_zlabel('Z position')
ax.set_title('Trayectoria de Partícula bajo Diferentes Fuerzas')
ax.legend()
plt.tight_layout()

# Guardar y mostrar
plt.savefig('particle_trajectories.pdf')
plt.show()