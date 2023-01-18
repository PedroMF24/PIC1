import random as R
import matplotlib.pyplot as plt
import numpy as np
import itertools as index 

def AddPoint(plot, x, y, color):
    plot.scatter(x, y, c=color)
    plot.clf()
    plot.show()

f = open('randomData.par', 'w')
pars = ['Mh','MH','MX3']
x=[]
y=[]
i=0
it = index.count(1,1)
while i<3:
    n = R.random()
    if (n<0.12):
        f.write(pars[i] + '\t' + str(n) + '\n')
        i+=1
        x.append(next(it))
        y.append(n)

f.write(str('Mh') + '\t' + str(125))
f.close
plt.scatter(x,y)
plt.title('My first graph!')
plt.xlabel('x - axis')
plt.ylabel('y - axis')
plt.savefig("../bin/first")
plt.show()
