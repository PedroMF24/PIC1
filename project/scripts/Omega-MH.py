import numpy as np
import matplotlib.pyplot as plt

OPL = 0.1197;
OUL = OPL + 0.0022;
OLL = OPL - 0.0022;

OmegaLimit = 0.1241;

# Load data from file and specify column names
filename = '../data/micrOMEGAs/output-mO.dat'
data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)

# Define x data
x = data['MH']

# Define y data for each scatter plot based on Omega values
y1 = data['Omega'][data['Omega'] < OLL]
y2 = data['Omega'][(data['Omega'] >= OLL) & (data['Omega'] <= OUL)]
y3 = data['Omega'][data['Omega'] > OUL]

# Create a new figure and set the size
fig, ax = plt.subplots(figsize=(8, 8))

# Set plot titles and axis labels
ax.set_title(r'$\Omega$ vs $M_{H}$') # r'$\Omega$ vs $\lambda_{345}$'
ax.set_xlabel(r'$M_{H}$') # r'$\lambda_{345}$'
ax.set_ylabel(r'$\Omega$') # r'$\Omega$'

# Plot the scatter points with different colors and big markers
ax.scatter(x[data['Omega'] < OLL], y1, color='red', s=50, label='Below Planck') # $\Omega < LL$
ax.scatter(x[(data['Omega'] >= OLL) & (data['Omega'] <= OUL)], y2, color='gold', s=50, label='In Planck') # $LL \leq \Omega \leq UL$
ax.scatter(x[data['Omega'] > OUL], y3, color='black', s=50, label='Above Planck') # $\Omega > UL$

# Add a legend
ax.legend()

# Set logarithmic scale for y-axis
ax.set_yscale('log')

# Display the plot
plt.show()
