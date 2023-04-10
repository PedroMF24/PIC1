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
x = data['laL']

# Define y data for each scatter plot based on Omega values
y1 = data['Omega'][data['Omega'] < OLL]
y2 = data['Omega'][(data['Omega'] >= OLL) & (data['Omega'] <= OUL)]
y3 = data['Omega'][data['Omega'] > OUL]

# Create a new figure and set the size
fig, ax = plt.subplots(figsize=(8, 8))

# Set plot titles and axis labels
ax.set_title('Omega vs. X')
ax.set_xlabel('X')
ax.set_ylabel('Omega')

# Plot the scatter points with different colors and big markers
ax.scatter(x[data['Omega'] < OLL], y1, color='red', s=50, label='Omega < OLL')
ax.scatter(x[(data['Omega'] >= OLL) & (data['Omega'] <= OUL)], y2, color='green', s=50, label='OLL <= Omega <= OUL')
ax.scatter(x[data['Omega'] > OUL], y3, color='blue', s=50, label='Omega > OUL')

# Add a legend
ax.legend()

# Set logarithmic scale for y-axis
ax.set_yscale('log')

# Display the plot
plt.show()
