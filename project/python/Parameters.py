
# from easydict import EasyDict as ed
# import numpy as np
import random as R
import math as M

class Parameters:
    # Fixed values
    Mh = 125
    v = 246
    la1 = (Mh/v)**2

    # Parameters Generated randomly
    MHX = 70 # CDM
    MH3 = 120 # It is A in IDM paper
    MHC = 120 # Charged Higgs
    la2 = 0.01
    laL = 0.01 # la3 + la4 + la5

    # MHX = R.uniform(0.0, 1000.0)
    # MH3 = R.uniform(0.0, 1000.0)
    # MHC = R.uniform(70.0, 1000.0)
    # la2 = R.uniform(0.0, 4.5)
    # laL = R.uniform(-1.5, 2)

    # Topo de pag 11
    def HardLimits(MHC, MHX):
        if (MHC - MHX >= 0.1):
            return True
        else: 
            return False

    # Coupling Constants
    m22Sqr = (v**2)*laL - 2*(MHX**2)
    la3 = laL + 2*(MHC**2 - MHX**2)/(v**2)
    la4 = (MHX**2 + MH3**2 - 2*(MHC**2))/v**2
    la5 = (MHX**2 - MH3**2)

    # Pars = ed({})
    # Pars['M22'] = []
    # Pars['La2'] = []
    # Pars['La3'] = []
    # Pars['La4'] = []
    # Pars['La5'] = []

    M22 = []
    La2 = []
    La3 = []
    La4 = []
    La5 = []
    # def GenerateParameters()
    
