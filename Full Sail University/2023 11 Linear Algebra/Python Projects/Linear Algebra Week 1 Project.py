# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np #Import of number python library
import sympy as sy #Import of symbols python library
import scipy as sp #Import of science python library
from sympy import symbols #Import the symbols library out of sympy
x,y,z,t,u = sy.symbols("x,y,z,t,u") #Identify that we'll be using x and y as math variables

#Step 3 Solve 2x-37=17 and 4x+7y=-5
exampleAns = sy.solve([2*x-3*y-17, 4*x+7*y+5])
sy.pprint(exampleAns) #Print the example answer to console
sy.pprint("\n") #Print skip a line
#Step 4 A) Solve the linear equation system provided
linearSystemAns = sy.solve([x+3*y-z+t+u-26, 2*x+4*y+z+t+u-35, 5*x-2*y-z+t-4*u+11, 3*x+y-5*z-7*t-u+28, 4*x+5*y-3*z+2*t+7*u-80])
sy.pprint(linearSystemAns) #Print the linear system answer
sy.pprint("\n")
#Step 4 B) Solve the word problem
wordProblemAns = sy.solve([15*x+10*y+6*z+5*t-273, 20*x+5*y+3*z+4*t-266, 10*x+2*y+5*z+5*t-167, 12*x+4*y+10*z+t-227])
sy.pprint(wordProblemAns) #Print the word problem answer