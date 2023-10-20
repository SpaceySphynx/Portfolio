using Microsoft.SqlServer.Server;
using System;
using System.IO;
using System.Security.Cryptography;
using Tester;

namespace FSPG1
{
    class Submission
    {
        /*
         * This lab is NOT interactive - that means there should be no 
         * calls to the Console class (no Write/WriteLine/ReadLine/ReadKey)
         * 
         * You cannot use multiple return statements any of these methods. 
         * Additionally the use of var is not permitted
         * 
        */

        // Test 1 – How many multiples
        // Given three int's, start, end and factor, using a loop, count how 
        // multiples of factor occur between start and end(inclusive)
        public static int Test1(int start, int end, int factor)
        {
            // Created a count variable to count how many multiples of factor occur and to store that value
            int count = 0;

            /* Went with a for loop first taking in the start variable and assigning it to a duringTheLoop varaible for the initializer
             * Then saying the duringTheLoop should continue as long as it's less or equal to the end variable provided for the condition
             * and duringTheLoop++ for the iterator
            */
            for (int duringTheLoop = start; duringTheLoop <= end; duringTheLoop++)
            {
                // this is where the factoring and counting occurs
                // each time the for loop runs if the duringTheLoop variable is equalivant to the duringTheLoop divided by factor and
                // then muliplied by factor then count will increase by 1 saying this is a one multiple of factor
                if (duringTheLoop == (duringTheLoop / factor) * factor)
                {
                    count++;
                }
            }
            // one the loop has come to completion return the final count
            return count;
        }

        // Test 2 - Factorial
        // Given an int, number, calculate the factorial for number. A factorial 
        // is the result of multiplying all integers between 1 and the target 
        // (number) (so 3 factorial, 3!, is 3 X 2 X 1 = 6)
        public static int Test2(int number)
        {
            // Assigning the input number to a second variable factorial
            int factorial = number;
            
            // Using a for loop I put number-- decremental for initializer, as long as number is greater than or equal to 1 for the condition
            // the last thing is that we want to loop to continue but in a counting down decremental manner and so we have -- instead of ++
            for (number--; number >=1; number--)
            {
                // I didn't think a if statement was needed this time.
                // This is where I use factorial and store the factor multipled by number
                factorial = factorial * number;
            }
            // Once the loop has finished the final value of factorial is returned
            return factorial;
        }

        // Test 3 - Raise to a power
        // Given two int's, root and exponent, use a loop to raise root to 
        // exponent. You are not allowed to use Math.Pow to compute the answer – 
        // you must use a loop. Additionally, exponent will be greater than or 
        // equal to 0 (no negative exponents)
        public static int Test3(int root, int exponent)
        {
            // created a variable to store the answer for each loop and finally return
            int answer = root;

            // I used a for loop that decremental by and counts down on each loop until the last time through is equal to 1
            for (exponent--; exponent >= 1; exponent--)
                {
                // Since an exponent is the number * the number I used answer to multiply the root     
                answer = answer * root;
                }
             // one the loop has come to completion return the final count
             return answer;
        }

        // Test 4 - Consumable
        // Given two doubles (onHand and consume) that represent the amount of 
        // an on-hand resource (onHand) and the amount of the resource that is 
        // consumed per cycles (think a time period). You are to determine how 
        // many cycles (time periods), before the on-hand amount is used up. 
        // For example, if you have 1 gallon of milk (onHand)and use 1 quart 
        // (1/4 gallon) per day (consume), determine when you expect to run out 
        // of milk (4 days).  Return the number representing when the on-hand 
        // amount reaches 0 (or becomes negative)
        // You may find it necessary to use the Round method from the Math class 
        // to avoid floating-point errors. I'd suggest rounding the results of 
        // each computation to 3 decimal places.
        public static int Test4(double onHand, double consume)
        {
            // Created a count variable to count the number of times the loop runs
            int count = 0;
            // Created a whatIsLeft variable to hold the amount as it's consumed
            double whatIsLeft = onHand;

            // Created a while loop that runs into the condition of whatIsLeft long as it's greater than or equal to consume
            // and had to add Math.Round to deal with the floating-point errors.
            while (Math.Round(whatIsLeft, 3) >= consume)
            { 
                // whatIsLeft is equal to whatIsLeft subtract consume then count the loops with count ++
                whatIsLeft -= consume;
                count++;
            }
           
            return count;

        }

        // Test 5 - Prime number
        // Given an int, number, determine if number is a prime number. Recall 
        // prime numbers are numbers that are divisible only by 1 and themselves. 
        // By definition negative values, 0 and 1 are not prime numbers (2 is 
        // the smallest prime number). If number is prime, return true, 
        // otherwise return false.
        public static bool Test5(int number)
        {
            // Created a int variable to hold the primeCheck counter defaulted to 0 value
            int primeCheck = 0;

            //probably not needed but just there to make sure no numbers are submitted that are 1 or less
            if (number <= 1)
            {
                return false;
            }

            // Created a for loop that runs until the int number is reached
            for (int theLoop = 1; theLoop < number; theLoop++)
            {
                // This if statement checks if there is a remainder when the number is divided by the loop
                // If there is a remainder primeCheck variable will increment by 1
                if (number % theLoop == 0)
                {
                    primeCheck++;
                }
            }
            // This if statement checks if the primeCheck variable was incremented
            // if so it returns true
            if (primeCheck == 1)
            {
                return true;
            }
            // If nothing returns true it defaults to false
            return false;

        }

        // Test 6 - Build a string
        // Given a char, starter, and an int, number, create a string the is made
        // up of starter the next number of characters (in order). For example, 
        // if starter is 'A' and number is 5, the string should be ABCDE (the
        // starting value of A followed by the next 4 letters, in order) 
        public static string Test6(char starter, int number)
        {
            // Created a string answer value to hold the answer
            string answer = "";

            // Used a for loop to run through the number of characters that is asked for. 
            for (number--; number >= 0; number--)
            {
                // The answer stores the starter string character then starter++ increments one character
                answer += starter.ToString();
                starter++;
            }
            
            return answer;
        }

        // Test 7 - Making change
        // Given a double, amount, that represents an amount of US money, 
        // determine the minimum number of coins required to equal that 
        // amount. Use on quarters, dimes, nickels and pennies. There are 
        // two approaches to this problem. The first uses modulo division 
        // and the second uses loops. You are not allowed to solve using
        // modulo division. For example, given 2.63, you would need 10 
        // quarters, 1 dime and 3 pennies, for a total of 14 coins.
        // You will probably find it necessary to use the Round method 
        // from the Math class to avoid floating-point errors. Since you 
        // are dealing with US currency/coins, I'd suggest rounding the 
        // results of each computation to 2 decimal places.
        public static int Test7(double amount)
        {
            // I created a double variable for each coin
            double quarter = 0.25;
            double dime = 0.10;
            double nickle = 0.05;
            double penny = 0.01;
            // I created a remainingAmount variable to store what is left after each if, else if, else statement
            double remainingAmount = amount;
            // Counts the amount of coins
            int countCoins = 0;

            // Used a while loop and added Math.Round to deal with floating point percision errors
            // set to two decimal places    
            while (Math.Round(remainingAmount, 2) > 0)
            {
                // First if loop condition runs until all quarters are subtracted from the original amount counting each loop
                if (remainingAmount >= quarter)
                {
                    countCoins++;
                    remainingAmount -= quarter;
                }
                // Second else if loop condition kicks in once no quarters are left
                // it also adds 1 to the count each time it triggers
                else if (remainingAmount >= dime)
                {
                    countCoins++;
                    remainingAmount -= dime;
                }
                // Third else if loop condition kicks in once there are no dimes left to count the nickles
                // each iteration adds to the countCoins variable
                else if (remainingAmount >= nickle)
                {
                    countCoins++;
                    remainingAmount -= nickle;
                }
                // The final loop checks for pennies and adds to the final count
                else
                {
                    countCoins++;
                    remainingAmount -= penny;
                }
                               
            }
            // Returns the total count of all coins needed
            return countCoins;

        }

        // Test 8 – Return the multiples
        // Given two int's factor and qty, find the first qty multiples of 
        // factor (including factor as the first multiple) and add each to 
        // a string (separate each multiple with a single space). For 
        // example, given 5 (factor) and 7 (qty), the resulting string 
        // would be 5 10 15 20 25 30 35
        public static string Test8(int factor, int qty)
        {
            // Made a string variable to hold the answer
            string answer = "";
            // Used a for loop that addes factor * duringTheLoop that starts at 1 making it put the original number then
            // the next factor and so on to the string.
            for (int duringTheLoop = 1; duringTheLoop <= qty; duringTheLoop++)
            {
                answer += (factor * duringTheLoop).ToString() + " ";
            }

            return answer;
        }

        // Test 9 – Sum of values
        // Given two int's start and end, find the sum of all values between 
        // start and end (inclusive). For example, given 11 (start) and 19 
        // (end), the result is 135
        public static int Test9(int start, int end)
        {
            // Created an int answer variable to hold the answer
            int answer = 0;
            // Used a for loop to run starting at start given and ending with end inclusive
            // this takes the answer and adds the begnningNumber variable to the answer until all loops are complete
            for (int beginningNumber = start; beginningNumber <= end; beginningNumber++)
            {
                answer += beginningNumber;
            }

            return answer;
        }

        // Test 10 – Sum of values
        // Given an instance of the Random class, gener, use it to generate 
        // qty random integers in the range min (inclusive) to max (exclusive).
        // Find the and return the sum of the random numbers you generate. For 
        // example, given gener, 3, 7, 5, you will generate 5 random numbers 
        // between 3 and 7 (actually 3 and 6 because 7 is excluded) and find 
        // the sum of those 5 numbers. Return the sum
        // NOTE: You are given the Random object (gener) so you should not 
        // declare/instantiate another Random object
        public static int Test10(Random gener, int min, int max, int qty)
        {
            // Created a int answer variable and a randomNumber variable
            int answer = 0;
            int randomNumber = 0;

1           // Used a for loop to run the qty in a howManyNumbers variable
            for (int howManyNumbers = qty; howManyNumbers > 0; howManyNumbers--)
            {
                // took the random number and set it equal to the gener.Next with the min, max inputs for the range
                randomNumber = gener.Next(min, max);
                // Took the answer and added the randomNumber to it for each loop to get Sum
                answer += randomNumber;
            }

            return answer;

        }
    }
}
