import numpy as np
import matplotlib.pyplot as plt

class Plotter:

    def __init__(self, x_label, y_label):
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlabel(x_label)
        self.ax.set_ylabel(y_label)

    # def __init__(self, title="", xlabel="", ylabel="", xlim=None, ylim=None, xscale="linear", yscale="linear"):
    #     self.title = title
    #     self.xlabel = xlabel
    #     self.ylabel = ylabel
    #     self.xlim = xlim
    #     self.ylim = ylim
    #     self.xscale = xscale
    #     self.yscale = yscale

    def plot(self, x, y):
        plt.title(self.title)
        plt.xlabel(self.xlabel)
        plt.ylabel(self.ylabel)
        plt.xlim(self.xlim)
        plt.ylim(self.ylim)
        plt.xscale(self.xscale)
        plt.yscale(self.yscale)
        plt.plot(x, y)
        plt.show()

    
    def set_title(self, title):
        self.ax.set_title(title)
        
    def set_xlabel(self, x_label):
        self.ax.set_xlabel(x_label)
    
    def set_ylabel(self, y_label):
        self.ax.set_ylabel(y_label)
    
    def add_scatter_plot(self, x, y, label=None):
        self.ax.scatter(x, y, label=label)
    
    def show(self):
        self.ax.legend()
        plt.show()

    def legend(self):
        self.ax.legend(fontsize=self.fontsize)
    
    def savefig(self, filename):
        self.fig.savefig(filename)

    
    def scatter_plot(self, filename, headers):
        data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
        x = data[headers[0]]
        fig, ax = plt.subplots()
        for i in range(1, len(headers), 2):
            y = data[headers[i]]
            ax.scatter(x, y, label=headers[i+1])
        ax.set_xlabel(self.x_label)
        ax.set_ylabel(self.y_label)
        ax.legend()
        plt.show()
    
    def multiple_scatter_plots(self, filename, headers):
        data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
        num_plots = len(headers) // 2
        fig, axs = plt.subplots(num_plots, figsize=(8, 8*num_plots))
        for i in range(num_plots):
            x = data[headers[i*2]]
            for j in range(i*2 + 1, (i+1)*2, 2):
                y = data[headers[j]]
                axs[i].scatter(x, y, label=headers[j+1])
            axs[i].set_xlabel(self.x_label)
            axs[i].set_ylabel(self.y_label)
            axs[i].legend()
        plt.show()
    
    def histogram(self, filename, headers):
        data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
        x = data[headers[0]]
        fig, ax = plt.subplots()
        ax.hist(x, bins=20, edgecolor='black', alpha=0.5)
        ax.set_xlabel(self.x_label)
        ax.set_ylabel(self.y_label)
        plt.show()
    
    def line_plot(self, filename, headers):
        data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
        x = data[headers[0]]
        fig, ax = plt.subplots()
        for i in range(1, len(headers), 2):
            y = data[headers[i]]
            ax.plot(x, y, label=headers[i+1])
        ax.set_xlabel(self.x_label)
        ax.set_ylabel(self.y_label)
        ax.legend()
        plt.show()
    
    def scatter_plot_with_error_bars(self, filename, headers):
        data = np.genfromtxt(filename, names=True, dtype=None, encoding=None)
        x = data[headers[0]]
        fig, ax = plt.subplots()
        for i in range(1, len(headers), 4):
            y = data[headers[i]]
            error_x = data[headers[i+1]]
            error_y = data[headers[i+2]]
            ax.errorbar(x, y, xerr=error_x, yerr=error_y, fmt='o', label=headers[i+3])
        ax.set_xlabel(self.x_label)
        ax.set_ylabel(self.y_label)
        ax.legend()
        plt.show()























