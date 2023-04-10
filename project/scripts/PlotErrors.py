import numpy as np
from plotter import Plotter

# Load data from file and specify column names
filename = '../data/micrOMEGAs/output-mO.dat'
data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)

# Create plotter instance
plotter = Plotter()

# Set plot title and axis labels
plotter.set_title('Scatter plot with error bars')
plotter.set_xlabel('X')
plotter.set_ylabel('Y')

# Add scatter plot with error bars
plotter.add_scatter_error_plot(data['x'], data['y'], data['error_x'], data['error_y'])

# Show plot
plotter.show()
