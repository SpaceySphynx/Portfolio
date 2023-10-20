#define MATH_OPERATOR

using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Security;
using System.Runtime.Intrinsics.X86;
using System.Text;
using System.Threading.Tasks;

namespace FSPG1
{
    //defined the enum
    public enum MathOperator
    {
        Add = 0,
        Subtract = 1,
        Multiply = 2,
        Divide = 3,
        Modulo = 4,
    }
    public class Submissions
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
         * 
         * This is Lab 4 - it is intended for you to demonstrate your 
         * understanding of selection statements (if and switch). This means
         * you are required to use either a switch or if statement for all
         * Test solutions (Test6 is an exception to this rule). For Test6, you
         * are permitted to simply 'pass through' the value returned by the 
         * Equals method.
         * 
         *
         * Additional reminders. In PG1:
         *      1. Methods are not permitted to use more than 1 return statement
         *      2. You are not allowed to use the Convert class
         *      3. You are not allowed to use var in place of a known data type
         */

        /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!   IMPORTANT   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        * ============================================================================================
        * Before beginning Tests 1 and 2, you need to define an enum named
        * MathOperator with five values: Add, Subtract, Multiply, Divide and
        * Modulo.The enum should not be 'nested' within a class (it should
        * be defined in the namespace, but outside all classes). Once you have
        * created it, uncomment the corresponding line in the Test.cs file.
        * 
        * For Test1, After creating the enum, you are to return a MathOperator
        * value based on the value of the parameter provided:
        * 
        * 0 = MathOperator.Add
        * 1 = MathOperator.Subtract
        * 2 = MathOperator.Multiply
        * 3 = MathOperator.Divide
        * 4 = MathOperator.Modulo

        * You do not need to worry about/handle any other possible input values(the
        * only values passed to the method will be 0, 1, 2, 3 or 4)
        * ============================================================================================
        * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!   IMPORTANT   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        */
#if MATH_OPERATOR

        public static MathOperator Test1(int input)
        {
            // Assigning a MathOperator variable for return values
            MathOperator result1 = 0;

            // Decided to use a switch to compare the inputs and return the matching MathOperator
            switch(input)
            {
                // if the input is 0 then MathOperator.Add is assigned to the variable and returned as result1
                case 0:
                    result1 = MathOperator.Add;
                    break;
                // if the input is 1 then MathOperator.Subtract is assigned to the variable and returned as result1
                case 1:
                    result1 = MathOperator.Subtract;
                    break;
                // if the input is 2 then MathOperator.Multiply is assigned to the variable and returned as result1
                case 2:
                    result1 = MathOperator.Multiply;
                    break;
                // if the input is 3 then MathOperator.Divide is assigned to the variable and returned as result1
                case 3:
                    result1 = MathOperator.Divide;
                    break;
                // if the input is 4 then MathOperator.Modulo is assigned to the variable and returned as result1
                case 4:
                    result1 = MathOperator.Modulo;
                    break;

            }

            return result1;

        }


        /* Test 2
        * ===========
        * Use the MathOperator enum you developed for Test1 to decide what
        * operation to perform on the two int values provided. Return the 
        * result of performing the indicated operation on the int values.
        */
        public static int Test2(int number1, int number2, MathOperator operation)
        {
            // Assigning a int variable for return values
            int result2 = 0;
            switch (operation)
            {
                // if the input is MathOperator.Add then variable number1 and variable number2 get added together and the result assigned to result2 variable
                case MathOperator.Add:
                    result2 = (number1 + number2);
                    break;
                // if the input is MathOperator.Subtract then variable number2 gets subtracted from variable number1 and the result assigned to result2 variable
                case MathOperator.Subtract:
                    result2 = (number1 - number2);
                    break;
                // if the input is MathOperator.Multiply then variable number1 gets multiplied by variable number2 and the result assigned to result2 variable
                case MathOperator.Multiply:
                    result2 = (number1 * number2);
                    break;
                // if the input is MathOperator.Divide then variable number1 gets divided by variable number2 and the result assigned to result2 variable
                case MathOperator.Divide:
                    result2 = (number1 / number2);
                    break;
                // if the input is MathOperator.Modulo then variable number1 gets divided by variable number2 and the resulting remainder gets assigned to result2 variable
                case MathOperator.Modulo:
                    result2 = (number1 % number2);
                    break;

            }

            return result2;

        }
#endif

        /* Test3
        * ===========
        * Given a bool parameter, return a string indicating 
        * the related term. When the bool is true return "Proven", 
        * when the bool is false return "Denied". Again remember all
        * identifiers are case sensitive. For this Test, the string's 
        * case does not matter.
        */
        public static string Test3(bool input)
        {
            string result3 = "";

            // if input equals true return "Proven"
            if (input == true)
            {
                result3 = "Proven";
            }

            // if it's not equal to true then return "Denied"
            else
            {
                result3 = "Denied";
            }
            // If input is true then set result to "Proven"
            // Otherwise set result to "Denied"

            return result3;
        }

        /* Test4 
        * ===========
        * Given a weight in either kilograms or pounds and a
        * bool, you will either convert kilograms to pounds(when the
        * bool is true) or pounds to kilograms(when the bool is
        * false). Return the result rounded to 3 decimal places
        * (use Math.Round)
        * 
        * The conversions are:
        * 1 kg = 2.20462 lb
        * 1 lb = 0.453592 kg
        *
        * References:
        * - https://learn.microsoft.com/en-us/dotnet/api/system.math.round?view=net-7.0
        * - https://www.geeksforgeeks.org/c-sharp-math-round-method-set-1/
        */
        public static double Test4(double input, bool kiloToLb)
        {
            double result4 = 0;

            // if kiloToLb is true then multiply the input by kilograms to pounds conversion and assign the value to varaible result4
            if (kiloToLb == true)
            {
                result4 = input * 2.20462;
            }

            // if kiloToLb is false then multiply the input by pounds to kilograms conversion and assign the value to varaible result4
            else
            {
                result4 = input * 0.453592;
            }

            // using Math.Round with 3, MidpointRounding.AwayFromZero to get three places to the right of the decimal point to show
            return Math.Round(result4, 3, MidpointRounding.AwayFromZero);

        }

        /* Test5
        * ===========
        * Given an int that represents the severity of an employee infraction,
        * return the associated action required as a string.
        * Infraction Severity            Required Action
        *       Level 1                   Verbal Reprimand
        *       Level 2                   Formal Reprimand
        *       Level 3                   Suspension
        *       Level 4                   Termination
        * Keep in mind, action required must be spelled correctly
        * (exactly as above) but are not case sensitive.
        */
        public static string Test5(int input)
        {
            // Assigning a empty string variable result5 for return values
            string result5 = " ";
            switch (input)
            {
                // if the input is 1 then assign string Verbal Reprimand to result5 variable
                case 1:
                    result5 = "Verbal Reprimand";
                    break;
                // if the input is 2 then assign string Formal Reprimand to result5 variable
                case 2:
                    result5 = "Formal Reprimand";
                    break;
                // if the input is 3 then assign string Suspension to result5 variable
                case 3:
                    result5 = "Suspension";
                    break;
                // if the input is 4 then assign string Termination to result5 variable
                case 4:
                    result5 = "Termination";
                    break;
                
            }

            return result5;

        }

        /* Test6
        * ===========
        * Use an object's Equal method. Given two Triangle objects,
        * use their Equals method to determine if the two objects are equal.
        * 
        * Keep in mind, the Equals method is not the same as the equality
        * operator (==). The Equals method evaluates the value of the
        * contents of each object while the equality operator (==) will
        * evaluate if both references are the same(the same object).
        * Additionally, for this lab you are required to use the Equals
        * method that accepts a single parameter. 
        */
        public static bool Test6(Triangle t1, Triangle t2)
        {
            
            // I created a bool result6 variable to store a bool value in which I defaulted to false
            bool result6 = false;

            // I created an if statement for my bool using triangle 1 Equals triangle 2 if equal they'll return True in result6
            if (t1.Equals(t2))
            {
                result6 = true;
            }

            // else statement for when not true to assign false to result6 
            else
            {
                result6 = false;
            }

            // 
            return result6;

        }

        /* Test 7
        * ===========
        * Given the three sides of a Triangle, determine if the triangle
        * is a Right Triangle.A triangle where the sum of the squares
        *  of the two shortest sides(a and b) is equal to the square of
        *  longest side(c) is a 'Right' triangle.The third parameter
        *  (c) will always be the longest side given.
        */
        public static bool Test7(int a, int b, int c)
        {
            // default result of false assigned to bool result7 variable
            bool result7 = false;
            // made a varible for the squares of a, b and c sides of a triangle
            double squareOfA = MathF.Pow(a, 2);
            double squareOfB = MathF.Pow(b, 2);
            double squareOfC = MathF.Pow(c, 2);
            // made another variable for sum of squareOfA and squareOfB
            double sumSquaresOfAB = squareOfA + squareOfB;


            // now checked to see if the sumSquaresOfAB is equal to squareOfC
            if (sumSquaresOfAB.Equals(squareOfC))
            {
                result7 = true;
            }

            // else statement for when not true to assign false to result7 
            else
            {
                result7 = false;
            }

            // 
            return result7;

        }

        /* Test 8
        * ===========
        * Given the grade variable, which indicates a student's numeric grade, 
        * determine which letter grade they should receive.Return the proper
        * letter(char) as the result of this test.Do not worry about rounding
        * the grade. Use the following table to indicate which letter corresponds
        * to provided grades.
        * 
        * Use if and else-if for Test8
        * Remember only one return statement is allowed
        *  >= 90 and <= 100 	'A'
        *  >= 80 and< 90 	    'B'
        *  >= 73 and< 80    	'C'
        *  >= 70 and< 73 	    'D'
        *  >= 0 and< 70 	    'F'
        *  < 0 or> 100 	    '?'
        */
        public static char Test8(double grade)
        {
            // since it's a single character being put into the variable I went with char type using result10 for my variable
            char result10 = ' ';
            
            // decided to work my way from out of bounds to 100 using if and then else if statements
            // in this first one I did the or statement for values out of bounds giving a ? for error
            if (grade < 0 || grade > 100)
            {
                result10 = '?';
            }

            // all the rest of these the item had to be true for both with an and statement
            else if (grade >= 0 && grade < 70 )
            {
                result10 = 'F';
            }

            else if (grade >= 70 && grade < 73)
            {
                result10 = 'D';
            }

            else if (grade >= 73 && grade < 80)
            {
                result10 = 'C';
            }

            else if (grade >= 80 && grade < 90)
            {
                result10 = 'B';
            }
            
            else if (grade >= 90 && grade <= 100)
            {
                result10 = 'A';
            }
            
            return result10;
        }
    }
}
