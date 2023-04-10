import numpy as np
from plotter import Plotter

# Load data from file and specify column names
filename = '../data/micrOMEGAs/output-mO.dat'
data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)

# Create plotter instance
plotter = Plotter('laL', 'MH')

# Set plot title for first scatter plot
plotter.set_title('Scatter plot 1')

# Add first scatter plot
plotter.add_scatter_plot(data['laL'], data['MH'], label='scatter plot 1')

# Set axis labels for second scatter plot
#plotter.set_xlabel('laL')
#plotter.set_ylabel('MC')

# Add second scatter plot
plotter.add_scatter_plot(data['laL'], data['MC'], label='scatter plot 2')

# Show plot
plotter.show()