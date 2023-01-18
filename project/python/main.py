'''
#   PIC - COUPLING PARAMETERS FOR IDM, DARK MATTER MODEL
#   Date 16/12/2022
#   
'''
import numpy as np
# from Constraints import ConstraintCheck
from MakePlots import MakePlot
from Parameters import Parameters as Pars

i = 0
while i < 8:
    Pars.M22.append(i+1)
    Pars.La2.append(9-i)
    i+=1
# Red = 0, Green = 1, Blue = 2
colormap = np.array(['r', 'g', 'b'])
colorCodes = [] # 0, 2, 1, 1, 1, 2, 0, 0
x = 0
while x < len(Pars.M22):
    if x%2 == 0:
        colorCodes.append(0)
    elif x == 3:
        colorCodes.append(2)
    else:
        colorCodes.append(1)
    x+=1

MakePlot.MultiColorScatterPlot("Plot", "X axis", Pars.M22, "Y axis", Pars.La2, colormap, colorCodes)
# ConstraintCheck()

