import matplotlib.pyplot as plt
import numpy as np
# import seaborn as sns
# sns.set_context("poster")

# read data
r, error_r = np.loadtxt("prueba.txt", unpack=True)

# plot 
fig, ax = plt.subplots()
ax.plot(r, error_r, '-o', label='error_r')
ax.set_xscale('log')
ax.set_yscale('log')
ax.set_xlabel('$h$')
ax.set_ylabel('error')
ax.legend()
fig.savefig('deriv.pdf')