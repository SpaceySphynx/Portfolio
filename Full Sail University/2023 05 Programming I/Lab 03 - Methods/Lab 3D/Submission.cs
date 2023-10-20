using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3D
{
    /*  Instructions
     * ========================
     * Each method below will be called within a separate "Test" class.
     * These methods will be passed several random values as arguments.
     * 
     * Read the instructions for each test and complete
     * the method so that it outputs the expected result.
     * 
     * Tips:
     * - For this lab, do not override the value provided as a parameter
     * - Do not alter any of the given code unless spefically told otherwise.
     * - Make sure to run your application regularly to make sure you're receiving
     *   the exptect output.
     * - Syntax errors (red squiggly lines) indicate an error that will prevent your
     *   code from building and running. Even if it seems as if your application is 
     *   running, Visual Studio is simply showing your the last "working" version 
     *   of your code.
     */


    public class Submission
    {
        /* Test 1
        * ==================
        * Given an integer parameter "years", return the 
        * given value convert into days.
        * 
        * Example input:
        * - 5
        * 
        * Expected output: 
        * - 1,825
        */
        public static int Test1(int years)
        {
            int totalDaysFromYears = years * 365;

            // Set totalDaysFromYears to year * number of days in a year

            return totalDaysFromYears;
        }

        /* Test 2
        * ==================
        * Given two double parameters "number1" and "number2, return the 
        * value of number1 divided by number2.
        * 
        * Example input: 
        * - 5.00
        * - 2.00
        * 
        * Expected output:
        * - 2.50
        */
        public static double Test2(double number1, double number2)
        {
            double answerNumber1DividedNumber2 = number1 / number2;

            // Set answerNumber1DividedNumber2 to number 1 divided by number 2

            return answerNumber1DividedNumber2;
        }

        /* Test 3
        * ==================
        * Given two integer parameters "number1" and "number2, return the 
        * value of the remainder of number1 divided by number2.
        * 
        * Tip:
        * -This does not require use of the Math.DivRem() method.
        * 
        * Example input: 
        * - 7
        * - 2
        * 
        * Expected output: 
        * - 1
        */
        public static int Test3(int number1, int number2)
        {
            int answerRemainder = (number1 % number2);

            // answerRemainder using modulus return just the remainder from number1 divided by number2

            return answerRemainder ;
        }

        /* Test 4
        * ==================
        * Given a double parameter "input", find square root 
        * of the input value using the Math.Sqrt() method, 
        * then return the result converted float by using a cast.
        * 
        * References:
        * - https://learn.microsoft.com/en-us/dotnet/api/system.math.sqrt?view=net-6.0
        * - https://www.geeksforgeeks.org/c-sharp-math-sqrt-method/
        * - https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/types/casting-and-type-conversions
        * 
        * Example input: 
        * - 36
        * 
        * Expected output: 
        * - 6
        */
        public static float Test4(double input)
        {
            double doubleSqaureRoot = Math.Sqrt(input);
            
            //take square root of input using Math.Sqrt() method and put it into doubleSqaureRoot varible

            float answerSquareRoot = (float)doubleSqaureRoot;

            //convert the square root of doubleSquareRoot variable to a float assigning it to answerSquareRoot
            
            return answerSquareRoot;
        }

        /* Test 5
        * ==================
        * Given two integer parameters "number" and "power", 
        * return the value of number raised to power by using the
        * Math.Pow() method.
        * 
        * References:
        * - https://learn.microsoft.com/en-us/dotnet/api/system.math.pow?view=net-6.0
        * - https://www.geeksforgeeks.org/c-sharp-math-pow-method/
        * 
        * Example input: 
        * - 5
        * - 2
        * 
        * Expected output: 
        * - 25
        */
        public static double Test5(int number, int power)
        {
            double answerPower = Math.Pow(number, power);
            
            return answerPower;
        }

        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!   IMPORTANT   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        * ============================================================================================
        * From this point on, you will need to create your own methods.
        * 
        * ALL of the methosd must use the follwing keywords:
        * - public: the access for the method must be set to public
        * - static: the access for the method must also be static
        * 
        * See the above methods for an example.
        * 
        * Once the method has been created, locate and uncomment the 
        * corresponding line at the top of the Test.cs file.
        * 
        * DO NOT alter any other part of the file as this could cause
        * unexpected output and would be considered academic dishonesty.
        * ============================================================================================
        * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!   IMPORTANT   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        */

        /* Test 6
        * ==================
        * Create a method named "Test6" that accepts three string parameters.
        * Return the value of all three paramaters combined to form a question.
        * 
        * Tips:
        * - You may use either concatenation or interpolation to complete this.
        * - Pay attention to the output of the console to make sure your are providing
        *   the expected result.
        *   
        * Example input: 
        * - "Hey,"
        * - "what's up"
        * - "man"
        * 
        * Expected output: 
        * - "Hey, what's up man?" 
        */

        //created a Test6 string method accepting 3 strings
        public static string Test6(string string1, string string2, string string3)
        {
            string answerString = $"{string1} {string2} {string3}?";

            //formated the three strings into an answerString string variable and then returned the variable

            return answerString;
        }

        /* Test 7
        * ==================
        * Create a method named "Test7" that accepts one double parameter.
        * Return the value of the double parameter converted 
        * to a float by using a cast.
        * 
        * References:
        * - https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/types/casting-and-type-conversions
        * 
        * Example input:
        * - 5.25
        * 
        * Expected output:
        * - 5.25f
        */

        // made a Test7 method that's a float that takes a double input
        public static float Test7(double input7)
        {
            float answerNumber7 = (float)input7;
            
            // casting the double to a float varaible answerNumber7

            return answerNumber7;
        }



        /* Test 8
        * ==================
        * Create a method named "Test8" that accepts one string parameter.
        * Return the value of the string parameter converted to all caps
        * by using the ToUpper() method.
        * 
        * References:
        * - https://learn.microsoft.com/en-us/dotnet/api/system.string.toupper?view=net-6.0
        * - https://www.geeksforgeeks.org/c-sharp-toupper-method/
        * 
        * Example input: 
        * - "hey"
        * 
        * Expected output: 
        * - "HEY" 
        */


        // created a method for Test8 taking a string input
        public static string Test8(string input8) 
        {
            string answerCaps = input8.ToUpper();
            
            // convert a lowercase string a upperclase string using ToUpper() method

            return answerCaps;
        }

        /* Test 9
        * ==================
        * Create a method named "Test9" that accepts two double parameters named "base" and "height".
        * Using the given values for base and height, determine the area of a triangle and return the
        * result as a double.
        * 
        * Tips:
        * - The formula for the area of a triangle is 1/2 * base * height.
        * - This solution should not require any type of conversion.
        * 
        * References:
        * - https://www.cuemath.com/measurement/area-of-triangle/
        * 
        * Example input: 
        * - 10, 7
        * 
        * Expected output:
        * - 35
        */

        // created a method for Test9 taking two double inputs for the base and height
        public static double Test9(double triangleBase, double triangleHeight)
        {
            double answerTriangle = (triangleBase * triangleHeight / 2);

            // using the formula for a triangle take base and height and divide by 2 and put that value into a variable 

            return answerTriangle;
        }

        /* Test 10
        * ==================
        * Create an overload for Test2 that accepts 3 double values, instead of 2.
        * Return the value of number1 divided by number2 divided by number3.
        * 
        * Tips: 
        * - Remember that a method overload is a different version of a method
        *   that has the same identifier but accepts different parameters, 
        *   has a different return type, or both. 
        * 
        * References:
        * - https://www.geeksforgeeks.org/c-sharp-method-overloading/
        * - https://learn.microsoft.com/en-us/dotnet/standard/design-guidelines/member-overloading
        * 
        * Example input: 
        * - 5.0
        * - 2.0
        * - 6.0
        * 
        * Expected output: 
        * - 4.167
        */

        // reused the method for Test2 for this test10 but now taking three inputs
        public static double Test2(double number1, double number2, double number3)
        {
            double answerThreeValuesDivided = ((number1 / number2) / number3);

            // took the values and divided number1 by number 2 then all of it by number 3 assigning the answer to answerThreeValuesDivided variable 

            return answerThreeValuesDivided;
        }


    }
}
