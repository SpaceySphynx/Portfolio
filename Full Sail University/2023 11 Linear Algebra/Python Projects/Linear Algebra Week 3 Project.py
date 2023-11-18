# -*- coding: utf-8 -*-
"""
Created on Sat Nov 18 00:02:48 2023

@author: Johna
"""

import sympy as sy #Import of symbols python library

#Example
#The following matrix is a provided example
M = sy.Matrix([
    [1,2,4],
    [1,3,9],
    [1,4,16],
    [1,5,25]
])
sy.pprint(M)            #Print the matrix
u=sy.Matrix([3,5,3,6])  #The Y vector construct

# Calculate the vector of coefficients using the least-squares method
v=(M.T*M).inv()*M.T*u   
sy.pprint(v)

# Define the polyomial function
def f2(x):
    return v[0]+v[1]*x+v[2]*x**2

#Print the value passed through the polynomial with the provided Prediction 
print("Prediction at x = 6")
print(f2(6))
sy.pprint("\n") #Print skip a line

# Problem #1
# Defined my own matrix based on the first problem. I used **2 **3 for exponents
M2 = sy.Matrix([
    [1,1,1**2,1**3], 
    [1,2,2**2,2**3], 
    [1,3,3**2,3**3], 
    [1,4,4**2,4**3], 
    [1,5,5**2,5**3], 
    [1,6,6**2,6**3], 
    [1,7,7**2,7**3]
])
sy.pprint(M2)                       #Print the matrix
u2 = sy.Matrix([1,3,5,3,6,4,9])     #The Y vector construct

# Calculate the vector of coefficients using the least-squares method
v2 = (M2.T*M2).inv()*M2.T*u2
sy.pprint(v2)

# Define the polyomial function
def f3(x):
    return v2[0] + v2[1]*x + v2[2]*x**2 + v2[3]*x**3

#Print the value passed through the polynomial with the provided Prediction 
print("Prediction at x = 8")
print(f3(8))
sy.pprint("\n") #Print skip a line

# Problem #2
# Provided temperature data (T) and viscosity data (v)
T_values = [20, 40, 60, 80, 100, 120, 140]
u3 = sy.Matrix([135, 145, 155, 163, 172, 180, 185])

# Construct the matrix M3 using the temperature values
M3 = sy.Matrix([[1, T, T**2, T**3] for T in T_values])

# Calculate the vector of coefficients using the least-squares method
v3 = (M3.T * M3).inv() * M3.T * u3
sy.pprint(v3)

# Define the cubic model function
def f4(T):
    return v3[0] + v3[1]*T + v3[2]*T**2 + v3[3]*T**3

# Predict the oil’s viscosity at a temperature of 150 degrees Celsius
print("Prediction of oil’s viscosity at 150°C:")
print(f4(150))