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
fig = plt.figure(figsize=(8, 8))

# Add three subplots, one for each scatter plot
ax1 = fig.add_subplot(311)
ax2 = fig.add_subplot(312)
ax3 = fig.add_subplot(313)

# Set plot titles and axis labels
ax1.set_title('Omega < OLL')
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax2.set_title('OLL <= Omega <= OUL')
ax2.set_xlabel('X')
ax2.set_ylabel('Y')
ax3.set_title('Omega > OUL')
ax3.set_xlabel('X')
ax3.set_ylabel('Y')



# Plot the scatter points with different colors and big markers
ax1.scatter(x[data['Omega'] < OLL], y1, color='red', s=100)
ax2.scatter(x[(data['Omega'] >= OLL) & (data['Omega'] <= OUL)], y2, color='green', s=100)
ax3.scatter(x[data['Omega'] > OUL], y3, color='blue', s=100)

# Display the plot
plt.show()
