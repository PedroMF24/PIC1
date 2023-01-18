# to make the plots

from easydict import EasyDict as ed
import matplotlib.pyplot as plt
import numpy as np

class MakePlot:

    colormap = np.array(['r', 'g', 'b'])

    def ScatterPlot(name, xAxis, x , yAxis, y, col = "cornflowerblue"):
        plt.scatter(x,y, marker = 'o', color = col)
        plt.title(name)
        plt.xlabel(xAxis)
        plt.ylabel(yAxis)
        plt.savefig("../bin/" + name)
        plt.show()

    def LinePlot(name, xAxis, x , yAxis, y, col = "cornflowerblue"):
        plt.plot(x,y, marker = 'o', color = col)
        plt.title(name)
        plt.xlabel(xAxis)
        plt.ylabel(yAxis)
        plt.savefig("../bin/" + name)
        plt.show()

    def MultiColorScatterPlot(name, xAxis, x, yAxis, y, colormap, colorCodes):
        categories = np.asarray(colorCodes)
        plt.scatter(x, y, s=50, c=colormap[categories]) # a[0], a[1]
        plt.title(name)
        plt.xlabel(xAxis)
        plt.ylabel(yAxis)
        plt.savefig("../bin/" + name)
        plt.show()
