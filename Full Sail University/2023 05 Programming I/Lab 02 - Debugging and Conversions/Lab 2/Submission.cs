using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FSPG1
{
    class Submission
    {
        /*
         * 
         * For this lab you are required to use the Parse() method 
         * for each conversion.
         * 
         * Additional notes/information:
         * When the instructions say ‘given’ it means that the test method is receiving the 
         * specified data as a parameter (the data inside the parentheses). You can use the 
         * variables directly in your solution. For example, Test3 has the ‘header’ line:
         * 
         * public static int Test3(string input)
         * -	public and static are ‘optional’ modifiers for the header
         * -	int is the return data (the ‘type’ of answer the method will provide)
         * -	Test3 is the name of the method
         * -	(string input) is the parameter list. In this case there is a single parameter 
         *      – it is a string and its name is input – it is the ‘information’ that is given 
         *      (passed) to the method when it is called
         *      
        */

        /* The following variable will determine the gamification
         * value for this lab assignment. This will determine speed of animations
         * for this assignment and will change your grade out the expected outcome.
         * 
         * 0 = DISABLED 
         * 1 = ENABLED
         * 2 = ENABLED (FAST MODE)
         */

        public const int GAME_MODE = 1;

        // Given a string, using the Int32 class, convert the string 
        // to an integer. Return the integer
        public static int Test3(string input)
        {
            return Int32.Parse(input);
        }

        // Given a string, using the SByte class, convert the string 
        // to a signed byte. Return the signed byte
        public static sbyte Test4(string input)
        {
            return SByte.Parse(input); ;
        }

        // Given a string, using the Double class, convert the string 
        // to a double Return the double
        public static double Test5(string input)
        {
            return Double.Parse(input); ;
        }

        // Given a string, using the UInt16 class, convert the string
        // to a unsigned short. Return the unsigned short
        public static ushort Test6(string input)
        {
            return UInt16.Parse(input); ;
        }

        // Given a string, using the Single class, convert the string 
        // to a float. Return the float
        public static float Test7(string input)
        {
            return Single.Parse(input); ;
        }

        // Given a string, using the UInt32 class, convert the string 
        // to an unsigned integer. Return the unsigned integer
        public static uint Test8(string input)
        {
            return UInt32.Parse(input); ;
        }

        // Given a string, using the Int16 class, convert the string 
        // to a short. Return the short
        public static short Test9(string input)
        {
            return Int16.Parse(input); ;
        }

        // Given a string, using the UInt64 class, convert the string 
        // to an unsigned long. Return the unsigned long
        public static ulong Test10(string input)
        {
            return UInt64.Parse(input); ;
        }
    }
}
