# Experimental Constraints

from Parameters import Parameters as P

# Total width of the electroweak gauge bosons 
def EWBosons(MHX, MHC, MH3):
    MW = 80.433 # W boson mass
    MZ = 91.19  # Z boson mass

    if (MHX + MHC >= MW and MH3 + MHC and MH3 + MHX >= MZ and 2*MHC >= MZ):
        return True
    else:
        print("Problems with the EW Bosons mass condition")
        quit()
        # return 0

def LEPAnalysis(MH, MA):
    if (MA <= 100 and MH <= 80 and abs(MA - MH) >= 8):
        print("Region ruled out by LEP Analysis")
        return False
    else:
        return True

def ExpCons():
    EWBosons(P.MHX, P.MHC, P.MH3)
    LEPAnalysis(P.MHX, P.MH3)