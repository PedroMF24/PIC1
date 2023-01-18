from easydict import EasyDict as ed
import matplotlib.pyplot as plt
import numpy as np

a = np.array([[ 1, 2, 3, 4, 5, 6, 7, 8 ], [ 9, 8, 7, 6, 5, 4, 3, 2 ]])

Pars = ed({})

Pars['M22'] = []
Pars['La2'] = []
Pars['La3'] = []
Pars['La4'] = []
Pars['La5'] = []

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
categories = np.asarray(colorCodes)

plt.scatter(Pars.M22, Pars.La2 , s=50, c=colormap[categories]) # a[0], a[1]
plt.show()

# i = 0
# j = 1

# while i<100:
#     Pars.M22.append(i)
#     Pars.La2.append(j)
#     if i > 50:
#         j-=2
#     if i < 50:
#         j+=2
#     i+=1
# print(Pars.M22)
# print(Pars)

# plt.scatter(Pars.M22,Pars.La2)
# plt.show()