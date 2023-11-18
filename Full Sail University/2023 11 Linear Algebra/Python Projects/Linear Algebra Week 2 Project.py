# -*- coding: utf-8 -*-
"""
Created on Thu Nov  2 15:41:52 2023

@author: Johna
"""

import sympy as sy

exampleMatrix = sy.Matrix([[3,2,11], [5,-7,8]]) #Example provided matrix
sy.pprint(exampleMatrix) #Print the matrix
sy.pprint("\n") #Print a new line
exampleRref = exampleMatrix.rref(pivots = False) #Perform Reduced Row-Echelon Form to the matrix
sy.pprint(exampleRref) #Print the RREF
sy.pprint("\n") #Print a new line
exampleLastColumn = exampleRref.col(2) #Extract the last column for solution
sy.pprint(exampleLastColumn) #Print the solution
sy.pprint("\n") #Print a new line

#Solve the provided equations using RREF
equationSolve = sy.Matrix([[1,3,-1,2,1,19],[1,1,2,1,1,18],[3,-2,-1,2,-3,5],[2,1,-5,-7,-1,-16],[5,1,3,-2,2,36]])
sy.pprint(equationSolve) #Print the matrix
sy.pprint("\n") #Print a new line
equationRref = equationSolve.rref(pivots= False) #Perform Reduced Row-Echelon Form to the matrix
sy.pprint(equationRref) #Print the RREF
sy.pprint("\n") #Print a new line
equationLastColumn = equationRref.col(5) #Extract the last column for solution
sy.pprint(equationLastColumn) #Print the solution
sy.pprint("\n") #Print a new line

#Solve the word problem using RREF
wordProblemSolve = sy.Matrix([[100, 20, 50, 60, 200, 1200],[5,6,7,4,3,200],[10,2,5,5,6,500],[12,4,10,1,13,600],[7,9,3,5,10,300]])
sy.pprint(wordProblemSolve) #Print the matrix
sy.pprint("\n") #Print a new line
wordProblemRref = wordProblemSolve.rref(pivots= False) #Perform Reduced Row-Echelon Form to the matrix
sy.pprint(wordProblemRref) #Print the RREF
sy.pprint("\n") #Print a new line
wordProblemColumn = wordProblemRref.col(5) #Extract the last column for solution
sy.pprint(wordProblemColumn) #Print the solution