using System;
using System.Data;
using System.Diagnostics.Contracts;
using System.Numerics;
using Tester;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace FSPG1
{
    class Submission
    {
        /* The following variable will determine the gamification
         * value for this lab assignment. This will determine speed of animations
         * for this assignment and will change your grade out the expected outcome.
         * 
         * 0 = DISABLED 
         * 1 = ENABLED
         * 2 = ENABLED (FAST MODE)
         */

        public static readonly int GAME_MODE = 0;

        /*
         * This lab is NOT interactive - that means there should be no 
         * calls to the Console class (no Write/WriteLine/ReadLine/ReadKey)
         * 
         * You cannot use multiple return statements any of these methods. 
         * Additionally the use of var is not permitted
         * 
        */

        // Test 1 – Convert char array to int array
        // Given an array of char, phrase, convert each element to an
        // equivalent int value and place in an int array.
        // Return the int array
        public static int[] Test1(char[] phrase)
        {
            // Made a int Array variable charConvertedToInt and assigned it int based on the phrase length inputed
            int[] charConvertedToInt = new int[phrase.Length];

            // Used a for loop starting at 0 with a condition of looping until it reaches the input length
            for (int inTheLoop = 0; inTheLoop < charConvertedToInt.Length; inTheLoop++)
            {
                // Taking the array variable and converting each char to an int and storing it
                charConvertedToInt[inTheLoop] = (int)phrase[inTheLoop];
            }
            
            // Returning the stored int data
            return charConvertedToInt;
        }

        // Test 2 - Array statistics
        // Given an array of double, data, find the smallest element, 
        // the largest element and the numeric mean (average). Store the 
        // results in an array (in that order: smallest, largest, mean).
        // Return the array
        public static double[] Test2(double[] data)
        { 
            // Initialize smallest and largest to the first element of the array
            double smallest = data[0];
            double largest = data[0];

            // Initialize double sum variable to sum all numbers to find the mean
            double sum = 0;

            // Iterate in the data array until length is reached
            for (int inTheLoop = 0; inTheLoop < data.Length; inTheLoop++)
            {
                // If the current array data is less than smallest, update smallest
                if (data[inTheLoop] < smallest)
                    smallest = data[inTheLoop];

                // If the current array data is greater than largest, update largest
                if (data[inTheLoop] > largest)
                    largest = data[inTheLoop];

                // Sum the arrayj data
                sum += data[inTheLoop];
            }

            // Find the mean by taking the sum and dividing it by the data.Length (number of inputs)
            double mean = sum / data.Length;

            // Create a new array with the smallest, largest, and mean
            double[] answer = new double[] { smallest, largest, mean };

            // Return the new array
            return answer;
        }


        // Test 3 - Normalize an array (of double)
        // Given an array of double, numbers, normalize the array. To 
        // normalize an array:
        // 1) Find the largest element stored in the array
        // 2) Divide each element in the array by the largest value
        //    and replace each array element with the result of the 
        //    division.
        // Since the array's contents are being modified, there is 
        // nothing to return
        //
        // Tips:
        // - Round each result to 3 decimal places
        public static void Test3(double[] numbers)
        {
            // Initialize largest to the first element of the array
            double largest = numbers[0];

            // Iterate in the data array until length is reached
            for (int inTheLoop = 0; inTheLoop < numbers.Length; inTheLoop++)
            {
                // If the current array data is greater than largest, update largest
                if (numbers[inTheLoop] > largest)
                    largest = numbers[inTheLoop];
            }

            // Created a second for loop just like the first but this time replacing the original values of the array
            // with the new value of the value divided by largest rounded to 3 decimal places
            for(int inTheLoop = 0; inTheLoop < numbers.Length; inTheLoop++)
            {
                numbers[inTheLoop] = Math.Round(numbers[inTheLoop] / largest, 3);
            }
        
        }

        // Test 4 - Uniqueness
        // Given an array of string, names, verify that each name is unique
        // mean that none of the names are duplicated within the array.
        // If the array is unique, return true; otherwise, return false
        public static bool Test4(string [] names)
        {
            // Started with a for loop to loop at each name in the array
            for (int inTheLoop = 0; inTheLoop < names.Length; inTheLoop++)
            {
                // Did a second for loop to campare the values from the first loop to the values of the second loop
                for (int inTheLoop2 = inTheLoop + 1; inTheLoop2 < names.Length; inTheLoop2++)
                {
                    // if statement to perform the comparision and if something matches to return false
                    if (names[inTheLoop] == names[inTheLoop2])
                       
                        return false;
                }
    
            }

            // if no matches are found default to return true
            return true;
        }

        // Test 5 - Acronym
        // Given an array of string, words, create a string that is the 
        // acronym (first letter of each word). Return the string
        public static string Test5(string [] words)
        {
            // intialize the an empty string variable to hold the return value
            string theFirstLetter = "";

            // Created a for loop to go through each word from the array
            for (int inTheLoop = 0; inTheLoop < words.Length; inTheLoop++)
            {
                // Used an if statement that if the string is not empty in the words inTheLoop then
                // using the 0 value I am able to assign only the first letter of each word in the loop to theFirstLetter variable
                if (!string.IsNullOrEmpty(words[inTheLoop]))
                {
                    theFirstLetter += words[inTheLoop][0];
                }
            }

            // return the first letter
            return theFirstLetter;

        }

        // Test 6 - Array reverse
        // Given a char array, letters, create another array that has the
        // same elements but in reverse order. Return the array
        // 
        // You are not allowed to use Array.Reverse (or any existing
        // method) to reverse the array
        //
        public static char[] Test6(char[] letters)
        {
            // created a char array varaible and gave it the length of what variable input is received
            char[] reverseTheLetters = new char[letters.Length];

            // Used a for loop again for this
            for (int inTheLoop = 0; inTheLoop < letters.Length; inTheLoop++)
            {
                // Assigning the information to the reverseTheLetters varaible.
                // The letters side takes the input[ looks at the lengeth of the input minus 1 since 
                // the array counts from 0 the end if one less than the count. Used this to find the end of the
                // input and then counted from that ponit down - inTheLoop
                // resulting in assigning each letter to the reverseTheLetters[inTheLoop] back in reverse order
                reverseTheLetters[inTheLoop] = letters[letters.Length - 1 - inTheLoop];
            }

            return reverseTheLetters;
        }

        // Test 7 - Transpose array
        // Given a 2-Dimension array of int, table, create a new array that 
        // 'transposes' the original array. Transposing means that each row 
        // in the original array will be a column in the new array and each
        // column in the original array will be a row in the new array.
        // For example, given
        //   4   3   1   5
        //   2   7   0   8
        //
        // The transposed array would be
        //   4   2
        //   3   7
        //   1   0
        //   5   8
        //
        public static int[,] Test7(int [,] table)
        {
            // made two int varaible for table baed on rows and columns
            int rows = table.GetLength(0);
            int columns = table.GetLength(1);

            // making a 2-dimensional array variable using columes and rows
            int[,] answer = new int[columns, rows];

            // Created a for loop for rows then a nested for loop for columns
            for (int inTheLoop = 0; inTheLoop < rows; inTheLoop++)
            {
                for (int inTheLoop2 = 0; inTheLoop2 < columns; inTheLoop2++)
                {
                    // result of columns, rows variable being feed rows, columns in into it using the nested loops
                    answer[inTheLoop2, inTheLoop] = table[inTheLoop, inTheLoop2];
                }
            }

            return answer;
        }

        // Test 8 – Return a 2D array
        // Given three arrays of the same type (int) and size, combine the 
        // arrays into a single 2D array. Return the 2D array
        // NOTE: This solution requires a single loop (not three)
        // 
        public static int [,] Test8(int [] mins, int [] maxes, int [] seeds)
        {
            // Initialize the array with 3 rows and as many columns as the input arrays have values
            int[,] answer = new int[3, mins.Length];

            // Created a for loop starting at 0 and to loop until no longer less than mins variable length
            for (int inTheLoop = 0; inTheLoop < mins.Length; inTheLoop++)
            {
                // taking in each variable and assigning it to 0, 1, 2 in the table each time it cycles through the loop
                answer[0, inTheLoop] = mins[inTheLoop];
                answer[1, inTheLoop] = maxes[inTheLoop];
                answer[2, inTheLoop] = seeds[inTheLoop];
            }

            // Return the array that was created from the loop
            return answer;
        }

        // Test 9 – Convert int array to char array
        // Given an array of int, ascii, convert each element to an
        // equivalent char value and place in a char array.
        // Return the char array
        public static char[] Test9(int[] ascii)
        {
            // This is just the reverse of Test 1 so I just took Test 1 and reversed and changed the variable name
            // Made a int Array variable intConvertedToChar and assigned it char based on the phrase length inputed
            char[] intConvertedToChar = new char[ascii.Length];

            // Used a for loop starting at 0 with a condition of looping until it reaches the input length
            for (int inTheLoop = 0; inTheLoop < intConvertedToChar.Length; inTheLoop++)
            {
                // Taking the array variable and converting each int to an char and storing it
                intConvertedToChar[inTheLoop] = (char)ascii[inTheLoop];
            }

            // Returning the stored int data
            return intConvertedToChar;

        }

        // Test 10 – Modify an existing array
        // Given an array of char (all uppercase), modify the array so
        // that every other element will be lowercase (even indexes are 
        // upper, odd indexes are lower)
        public static void Test10(char[] word)
        {
            // Created a for loop starting at 0 for the length of word variable and incriments by one each loop
            for (int inTheLoop = 0; inTheLoop < word.Length; inTheLoop++)
            {
                // If the variable is odd, change the character to lowercase
                if (inTheLoop % 2 != 0)
                {
                    word[inTheLoop] = char.ToLower(word[inTheLoop]);
                }
            }
        }
    }
}
