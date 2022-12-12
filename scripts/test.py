import random as R

f = open('randomData.par', 'w')
pars = ['Mh','MH','MX3']
i = 0
while i < 3:
    n = R.random()
    if (n<0.12):
        f.write(str(pars[i]) + ' = ' + str(n) + '\n')
        i+=1

f.write(str('Mh') + ' = ' + str(125))
f.close()
