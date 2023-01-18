import random as R
import math as M

i = 0
while i < 3:
    lambdas = [R.random() for j in range(6)]
    lambdas[0] = "It " + str(i+1)
    auxCon1 = lambdas[3]+M.sqrt(lambdas[1]*lambdas[2])
    auxCon2 = lambdas[1]+lambdas[2]+lambdas[3]+M.sqrt(lambdas[1]*lambdas[2])
    valid = 0
    if ( lambdas[1]>0 and lambdas[2]>0 and auxCon1>0 and auxCon2>0 ):
        valid = 1
    if (valid == 1):
        for k in range(len(lambdas)):
            print(str(lambdas[k]) + " ")
        i+=1
        print("\n")

