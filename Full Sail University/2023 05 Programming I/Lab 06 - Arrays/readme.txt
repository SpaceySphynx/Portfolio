Test 1 – Convert a char array to an int array
public static int[] Test1(char [] phrase)
Given an array of char, phrase, copy each element to an int array. If appropriate, cast/convert each element from char to int. Return the int array.

Example Input	Example Output
{ 'A', 'B', 'C' }	
{ 66, 67, 68 }



 

Test 2 – Compute statistics for elements of an array
public static double [] Test2(double [] data)
Given an array of double, data, find the smallest element, the largest element and the numeric mean (average). Store the results in an array (in that order: smallest, largest, mean). Return the array. 

You are not allowed to use any methods in the Array class to accomplish these tasks.

Example Input	Example Output
{ 9.0,  11.0, 4.0 }
{ 4.0, 11.0, 6.0 }



Test 3 – Normalize an array
public static void Test3(double [] numbers)
Given an array of double, numbers, normalize the array. To normalize an array:

Find the largest element stored in the array
Divide each element in the array by the largest value
and replace each array element with the result of the division. Since array's are reference types and the array's contents are being modified, there is nothing to return

Example Input	Example Output
{ 7.0, 3.5, 1.75 }
{ 1.0, 0.5, 0.25 }

Test 4 – Uniqueness (No duplicates)
public static bool Test4(string [] names)
Given an array of string, names, verify that each name is unique mean that none of the names are duplicated within the array. If the array is unique, return true; otherwise, return false


Example Input	Example Output
{ 7.0, 3.5, 1.75 }
{ 1.0, 0.5, 0.25 }

Tip: Use 2 for loops (nested) to accomplish this task.
Test 5 – Acronym
public static string Test5(string [] words)
Given an array of string, words, create a string that is the acronym (first letter of each word) using the concatenation operator (+). Return the string.

Example Input	Example Output
{ "World", "of", "Wonder" }
"WoW"

Test 6 – Array reversal
public static char [] Test6(char [] letters)
Given a char array, letters, create another array that has the same elements but in reverse order. Return the array.

You are not allowed to use Array.Reverse (or any existing method) to reverse the array.

Example Input	Example Output
{ 'a', 'b', 'c' }
{ 'c', 'b', 'a' }

Test 7 – Transpose array
public static int[,] Test7(int [,] table)
Given a 2-Dimension array of int, table, create a new array that the original array. Transposing means that each row in the original array will be a column in the new array and each column in the original array will be a row in the new array.
Example Input	Example Output
4 3 1 5
2 7 0 8

4 2

3 7

1 0

5 8



Test 8 – Combine multiple 1D array into a 2D array
public static int [,] Test8(int [] mins, int [] maxes, int [] seeds)
Given three arrays of the same type (int) and size, mins, maxes and seeds, combine the arrays into a single 2D array. Return the 2D array.

Example Input	Example Output
{ 1, 2, 3 } / { 7, 8, 9 } / { 5, 10, 15 }
{ { 1, 2, 3 }, { 7,8,9 }, { 5,10,15 } }

Tip: This task only requires a single loop (not 3)
Test 9 – Convert an int array to a char array
public static char [] Test9(int [] ascii)
Given an array of int, ascii, copy each element to a char array. If appropriate, cast/convert each element from int to char. Return the char array.

Example Input	Example Output
{ 65, 67, 79 }
{ 'A', 'C', 'E' }

Test 10 – Modify elements in an existing array
public static void Test10(char [] word)
Given an array of char (all uppercase), word, modify the array so that every other element will be lowercase (even indexes are upper, odd indexes are lower). You can either use the ToLower method of the Char class or you can add 32 to the char and then cast the resulting value back to a char.

Example Input	Example Output
GENER
GeNeR
