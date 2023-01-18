
# import numpy as np

# # Fixed values
# Mh = 125
# v = 246
# la1 = (Mh/v)**2

# # Parameters
# MHX = 70 # CDM
# MH3 = 120 # It is A in IDM paper
# MHC = 120 # Charged Higgs
# la2 = 0.01
# laL = 0.01 # la3 + la4 + la5

# # Coupling Constants
# m22Sqr = (v**2)*laL - 2*(MHX**2)
# la3 = laL + 2*(MHC**2 - MHX**2)/(v**2)
# la4 = (MHX**2 + MH3**2 - 2*(MHC**2))/v**2
# la5 = (MHX**2 - MH3**2)


# # Theoritical Constraints

# # Bound from Below
# def BFB(par1, par2, par3, par4, par5):
#     aux1 = par3 + np.sqrt(par1*par2)
#     aux2 = par4 + par5 + aux1
#     if (par1 > 0 and par2 > 0 and aux1 > 0 and aux2 > 0):
#         return 1
#     else:
#         print("Potencial is not bound from below")
#         quit()
#         # return 0

# # Two minima coexistence
# def TwoMins(mass22, par2):
#     aux1 = (Mh**2)/np.sqrt(la1)
#     aux2 = (mass22)/np.sqrt(par2)
#     if (aux1 >= aux2):
#         return 1
#     else:
#         print("Inert vacuum is not garanteed to be global")
#         quit()
#         # return 0

# Experimental Constraints

# # Total width of the electroweak gauge bosons 
# def EWBosons():
#     MW = 80.433 # W boson mass
#     MZ = 91.19  # Z boson mass

#     if (MHX + MHC >= MW and MH3 + MHC and MH3 + MHX >= MZ and 2*MHC >= MZ):
#         return 1
#     else:
#         print("Problems with the EW Bosons mass condition")
#         quit()
#         # return 0

# Check if parameters numbers are valid
# def ConstraintCheck():
#     #Theoretical
#     BFB(la1, la2, la3, la4, la5)
#     TwoMins(Mh, la1, m22Sqr, la2)
#     # Experimental
#     EWBosons(MHX, MHC, MH3)


# # MAIN ZONE

# # print(BFB(la1, la2, la3, la4, la5))   # DONE
# # print(TwoMins(m22Sqr, la2))           # DONE
# # print(EWBosons())                     # DONE

# ConstraintCheck()
