# PACKAGES
import numpy as np

from Parameters import Parameters as P

# Theoritical Constraints

# Bound from Below
def BFB(par1, par2, par3, par4, par5):
    aux1 = par3 + np.sqrt(par1*par2)
    aux2 = par4 + par5 + aux1
    if (par1 > 0 and par2 > 0 and aux1 > 0 and aux2 > 0):
        return 1
    else:
        print("Potencial is not bound from below")
        quit()
        # return 0

# Two minima coexistence
def TwoMins(SMhiggs, par1, mass22, par2):
    aux1 = (SMhiggs**2)/np.sqrt(par1)
    aux2 = (mass22)/np.sqrt(par2)
    if (aux1 >= aux2):
        return 1
    else:
        print("Inert vacuum is not garanteed to be global")
        quit()
        # return 0

def TheoCons():
    BFB(P.la1, P.la2, P.la3, P.la4, P.la5)
    TwoMins(P.Mh, P.la1, P.m22Sqr, P.la2)