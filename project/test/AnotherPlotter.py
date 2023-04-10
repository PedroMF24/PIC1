
# import numpy as np
# import matplotlib.pyplot as plt

# class Plotter:

#     def __init__(self, x_label, y_label):
#         self.x_label = x_label
#         self.y_label = y_label
    
#     def scatter_plot(self, filename, headers):
#         data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
#         x = data[headers[0]]
#         fig, ax = plt.subplots()
#         for i in range(1, len(headers), 2):
#             y = data[headers[i]]
#             ax.scatter(x, y, label=headers[i+1])
#         ax.set_xlabel(self.x_label)
#         ax.set_ylabel(self.y_label)
#         ax.legend()
#         plt.show()
    
#     def multiple_scatter_plots(self, filename, headers):
#         data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
#         num_plots = len(headers) // 2
#         fig, axs = plt.subplots(num_plots, figsize=(8, 8*num_plots))
#         for i in range(num_plots):
#             x = data[headers[i*2]]
#             for j in range(i*2 + 1, (i+1)*2, 2):
#                 y = data[headers[j]]
#                 axs[i].scatter(x, y, label=headers[j+1])
#             axs[i].set_xlabel(self.x_label)
#             axs[i].set_ylabel(self.y_label)
#             axs[i].legend()
#         plt.show()
    
#     def histogram(self, filename, headers):
#         data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
#         x = data[headers[0]]
#         fig, ax = plt.subplots()
#         ax.hist(x, bins=20, edgecolor='black', alpha=0.5)
#         ax.set_xlabel(self.x_label)
#         ax.set_ylabel(self.y_label)
#         plt.show()
    
#     def line_plot(self, filename, headers):
#         data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
#         x = data[headers[0]]
#         fig, ax = plt.subplots()
#         for i in range(1, len(headers), 2):
#             y = data[headers[i]]
#             ax.plot(x, y, label=headers[i+1])
#         ax.set_xlabel(self.x_label)
#         ax.set_ylabel(self.y_label)
#         ax.legend()
#         plt.show()
    
#     def scatter_plot_with_error_bars(self, filename, headers):
#         data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
#         x = data[headers[0]]
#         fig, ax = plt.subplots()
#         for i in range(1, len(headers), 4):
#             y = data[headers[i]]
#             error_x = data[headers[i+1]]
#             error_y = data[headers[i+2]]
#             ax.errorbar(x, y, xerr=error_x, yerr=error_y, fmt='o', label=headers[i+3])
#         ax.set_xlabel(self.x_label)
#         ax.set_ylabel(self.y_label)
#         ax.legend()
#         plt.show()


import numpy as np
import matplotlib.pyplot as plt

from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib.backends.backend_pdf import PdfPages

class Plotter:
    def __init__(self, figsize=(8, 8), fontsize=12, linewidth=2):
        self.fig = Figure(figsize=figsize)
        self.canvas = FigureCanvas(self.fig)
        self.ax = self.fig.add_subplot(111)
        self.fontsize = fontsize
        self.linewidth = linewidth
    
    def set_title(self, title):
        self.ax.set_title(title, fontsize=self.fontsize)
    
    def set_xlabel(self, xlabel):
        self.ax.set_xlabel(xlabel, fontsize=self.fontsize)
    
    def set_ylabel(self, ylabel):
        self.ax.set_ylabel(ylabel, fontsize=self.fontsize)
    
    def set_yscale(self, scale):
        self.ax.set_yscale(scale)
    
    def scatter(self, x, y, color, s, label):
        self.ax.scatter(x, y, color=color, s=s, label=label)
    
    def legend(self):
        self.ax.legend(fontsize=self.fontsize)
    
    def savefig(self, filename):
        self.fig.savefig(filename)
        
OPL = 0.1197;
OUL = OPL + 0.0022;
OLL = OPL - 0.0022;

OmegaLimit = 0.1241;

# Load data from file and specify column names
filename = 'output-mO.dat'
data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)

# Define x data
x = data['laL']

# Define y data for each scatter plot based on Omega values
y1 = data['Omega'][data['Omega'] < OLL]
y2 = data['Omega'][(data['Omega'] >= OLL) & (data['Omega'] <= OUL)]
y3 = data['Omega'][data['Omega'] > OUL]

# Create a new figure and set the size
plotter = Plotter(figsize=(8, 8))

# Set plot titles and axis labels
plotter.set_title('Omega vs. X')
plotter.set_xlabel('X')
plotter.set_ylabel('Omega')

# Plot the scatter points with different colors and big markers
plotter.scatter(x[data['Omega'] < OLL], y1, color='red', s=100, label='Omega < OLL')
plotter.scatter(x[(data['Omega'] >= OLL) & (data['Omega'] <= OUL)], y2, color='green', s=100, label='OLL <= Omega <= OUL')
plotter.scatter(x[data['Omega'] > OUL], y3, color='blue', s=100, label='Omega > OUL')

# Add a legend
plotter.legend()

# Set logarithmic scale for y-axis
plotter.set_yscale('log')

# Save the plot to a PDF file
plotter.savefig('plot.pdf')



# import numpy as np
# import matplotlib.pyplot as plt

# class Plotter:
#     def __init__(self, filename=None, x_label=None, y_label=None, title=None, x_logscale=False):
#         self.fig, self.ax = plt.subplots(figsize=(8, 8))
#         self.filename = filename
#         self.x_label = x_label
#         self.y_label = y_label
#         self.title = title
#         self.x_logscale = x_logscale
#         self.colors = ['red', 'green', 'blue', 'orange', 'purple', 'brown', 'gray', 'pink', 'olive', 'cyan']
#         self.marker_sizes = [100, 150, 200, 250, 300]
    
#     def load_data(self, names=True, dtype=None, encoding=None):
#         self.data = np.genfromtxt(self.filename, names=names, dtype=dtype, encoding=encoding)
    
#     def scatter(self, x_data, y_data, label=None, color=None, marker_size=None):
#         if color is None:
#             color = self.colors.pop(0)
#         if marker_size is None:
#             marker_size = self.marker_sizes.pop(0)
#         self.ax.scatter(x_data, y_data, color=color, s=marker_size, label=label)
    
#     def set_titles_and_labels(self):
#         self.ax.set_title(self.title)
#         self.ax.set_xlabel(self.x_label)
#         self.ax.set_ylabel(self.y_label)
    
#     def add_legend(self):
#         self.ax.legend()
    
#     def set_logscale(self):
#         if self.x_logscale:
#             self.ax.set_xscale('log')
    
#     def set_xlim(self, left=None, right=None):
#         self.ax.set_xlim(left=left, right=right)
    
#     def set_ylim(self, bottom=None, top=None):
#         self.ax.set_ylim(bottom=bottom, top=top)
    
#     def show(self):
#         self.set_titles_and_labels()
#         self.add_legend()
#         self.set_logscale()
#         plt.show()




# class Plotter:
#     def __init__(self, filename=None, x_label=None, y_label=None, title=None, xlim=None, ylim=None, xscale="linear", yscale="linear", x_logscale=False):
#         self.fig, self.ax = plt.subplots(figsize=(8, 8))
#         self.filename = filename
#         self.x_label = x_label
#         self.y_label = y_label
#         self.title = title
#         self.xlim = xlim
#         self.ylim = ylim
#         self.xscale = xscale
#         self.yscale = yscale
#         self.x_logscale = x_logscale
#         self.colors = ['red', 'green', 'blue', 'orange', 'purple', 'brown', 'gray', 'pink', 'olive', 'cyan']
#         self.marker_sizes = [100, 150, 200, 250, 300]
    
#     def load_data(self, names=True, dtype=None, encoding=None):
#         self.data = np.genfromtxt(self.filename, names=names, dtype=dtype, encoding=encoding)
    
#     def plot(self, x_data, y_data, label=None, color=None, marker_size=None, y_err=None, x_err=None):
#         self.ax.set_xlabel(self.x_label)
#         self.ax.set_ylabel(self.y_label)
#         self.ax.set_title(self.title)
#         self.ax.set_xlim(self.xlim)
#         self.ax.set_ylim(self.ylim)
#         self.ax.set_xscale(self.xscale)
#         self.ax.set_yscale(self.yscale)
#         if self.x_logscale:
#             self.ax.set_xscale('log')
#         if y_err is None and x_err is None:
#             self.ax.plot(x_data, y_data, color=color, label=label)
#         elif y_err is None and x_err is not None:
#             self.ax.errorbar(x_data, y_data, xerr=x_err, color=color, label=label)
#         elif y_err is not None and x_err is None:
#             self.ax.errorbar(x_data, y_data, yerr=y_err, color=color, label=label)
#         else:
#             self.ax.errorbar(x_data, y_data, xerr=x_err, yerr=y_err, color=color, label=label)
    
#     def set_title(self, title):
#         self.ax.set_title(title)
        
#     def set_xlabel(self, x_label):
#         self.ax.set_xlabel(x_label)
    
#     def set_ylabel(self, y_label):
#         self.ax.set_ylabel(y_label)
    
#     def add_scatter_plot(self, x_data, y_data, label=None, color=None, marker_size=None):
#         if color is None:
#             color = self.colors[len(self.ax.collections) % len(self.colors)]
#         if marker_size is None:
#             marker_size = self.marker_sizes[len(self.ax.collections) % len(self.marker_sizes)]
#         self.ax.scatter(x_data, y_data, label=label, color=color, s=marker_size)
    
#     def show(self):
#         self.ax.legend()
#         plt.show()

#     def legend(self, fontsize=None):
#         if fontsize is not None:
#             self.ax.legend(fontsize=fontsize)
#         else:
#             self.ax.legend()
    
#     def savefig(self, filename):
#         self.fig.savefig(filename)

    
#     def scatter_plot(self, headers):
#         self.load_data()
#         x_data = self.data[headers[0]]
#         for i in range(1, len(headers), 

