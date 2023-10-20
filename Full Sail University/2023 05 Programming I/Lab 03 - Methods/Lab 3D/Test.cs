// Uncomment the following lines, one by one, when you are working on these tests

#define TEST6
#define TEST7
#define TEST8
#define TEST9
#define TEST10

/* ================================================================================
 * 
 * DO NOT ALTER ANYTHING BENEATH THIS LINE.
 * 
 * DOING SO MAY CAUSE ISSUES WITHIN YOUR CODE.
 * 
 * IF YOU ARE EXPERIENCING ERRORS IN THIS CLASS, 
 * AND YOU HAVE NOT ALTERED THIS CLASS, THE ISSUES
 * EXIST WITHIN YOUR CODE. NOT HERE.
 * 
 *                             ▒▒████                              
 *                             ████████                            
 *                           ██████████                            
 *                           ████▒▒██████                          
 *                         ██████    ████▒▒                        
 *                         ████      ▒▒████                        
 *                       ██████        ██████                      
 *                     ▒▒████    ████    ████                      
 *                     ████▒▒  ████████  ██████                    
 *                   ██████    ████████    ████                    
 *                   ████░░    ████████    ██████                  
 *                 ██████      ████████      ████▒▒                
 *               ░░████        ████████      ▒▒████                
 *               ██████        ████████        ██████              
 *             ▒▒████          ████████          ████              
 *             ████▒▒          ██████▒▒          ██████            
 *           ██████              ████              ████            
 *           ████                ████              ██████          
 *         ██████                ████                ████▒▒        
 *       ░░████                                      ▒▒████        
 *       ████▓▓                                        ██████      
 *     ▒▒████                    ████                    ████      
 *     ████▒▒                  ████████                  ██████    
 *   ██████                      ▒▒▒▒                      ████░░  
 *   ████                                                  ▒▒████  
 * ██████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒██████
 * ████████████████████████████████████████████████████████████████
 * ▓▓████████████████████████████████████████████████████████████▓▓
 * 
 * 
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LabUI;
using Test3Utils;

namespace Lab_3D
{
    internal class Test
    {
        public static int Check1()
        {
            // Display header
            UI.DisplayHeader("Test 1");

            // Randomize data
            int[] numbers = RandomInts();

            
            int xk = 0;

            // Run tests
            for (int i = 0; i < numbers.Length; i++)
            {
                int ex = Test3Utils.Test.AgeToDays(numbers[i]);
                int rc = Submission.Test1(numbers[i]);

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                              // Test #
                    numbers[i].ToString(),              // Input
                    ex.ToString(),                      // ex result
                    rc.ToString(),                      // rc result
                    2,                                  // Input pad
                    4                                   // Output pad
                );

                
                if (ex == rc)
                {
                    xk += T_P;
                }
            }

            UI.DisplayPrograssBar(xk, T_P * 5);
            UI.DisplayScore(xk, T_P);
            UI.DisplayDivider();

            return xk;
        }

        public static int Check2()
        {
            // Display header
            UI.DisplayHeader("Test 2");

            // Randomize data
            double[] numbers1 = RandomDoubles();
            double[] numbers2 = RandomDoubles();

            
            int fr = 0;

            // Run tests
            for (int i = 0; i < numbers1.Length; i++)
            {
                double ex = Math.Round(
                    Test3Utils.Test.DivideNumbers(numbers1[i], numbers2[i]),
                    2
                );

                double rc = Math.Round(
                    Submission.Test2(numbers1[i], numbers2[i]),
                    2
                );

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                              // Pass #
                    $"{numbers1[i]}, {numbers2[i]}",    // Input
                    ex.ToString(),                // ex result
                    rc.ToString(),                // rc result
                    12,                                 // Input pad
                    5                                   // Output pad
                );

                
                if (ex == rc)
                {
                    fr += T_P;
                }
            }

            UI.DisplayPrograssBar(fr, T_P * 5);
            UI.DisplayScore(fr, T_P);
            UI.DisplayDivider();

            return fr;
        }

        public static int Check3()
        {
            // Display header
            UI.DisplayHeader("Test 3");

            // Randomize data
            int[] numbers1 = RandomInts();
            int[] numbers2 = RandomInts();

            
            int hj = 0;

            // Run tests
            for (int i = 0; i < numbers1.Length; i++)
            {
                float ex = Test3Utils.Test.Remainder(numbers1[i], numbers2[i]);
                float rc = Submission.Test3(numbers1[i], numbers2[i]);

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                              // Pass #
                    $"{numbers1[i]}, {numbers2[i]}",    // Input
                    ex.ToString(),                // ex result
                    rc.ToString(),                // rc result
                    6,                                  // Input pad
                    0                                   // Output pad
                );

                
                if (ex == rc)
                {
                    hj += T_P;
                }
            }

            UI.DisplayPrograssBar(hj, T_P * 5);
            UI.DisplayScore(hj, T_P);
            UI.DisplayDivider();

            return hj;
        }

        public static int Check4()
        {
            // Display header
            UI.DisplayHeader("Test 4");

            // Randomize data
            double[] numbers = RandomDoubles();

            
            int kw = 0;

            // Run tests
            for (int i = 0; i < numbers.Length; i++)
            {
                float ex = Test3Utils.Test.SquareRoot(numbers[i]);
                float rc = Submission.Test4(numbers[i]);

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                              // Pass #
                    $"{numbers[i]}",                    // Input
                    ex.ToString(),                // ex result
                    rc.ToString(),                // rc result
                    6,                                  // Input pad
                    10                                  // Output pad
                );

                
                if (ex == rc)
                {
                    kw += T_P;
                }
            }

            UI.DisplayPrograssBar(kw, T_P * 5);
            UI.DisplayScore(kw, T_P);
            UI.DisplayDivider();

            return kw;
        }

        public static int Check5()
        {
            // Display header
            UI.DisplayHeader("Test 5");

            // Randomize data
            int[] numbers = RandomInts();
            int[] powers = RandomInts();

            
            int ni = 0;

            // Run tests
            for (int i = 0; i < numbers.Length; i++)
            {
                double ex = Test3Utils.Test.NumberToPower(numbers[i], powers[i]);
                double rc = Submission.Test5(numbers[i], powers[i]);

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                              // Pass #
                    $"{numbers[i]}, {powers[i]}",       // Input
                    ex.ToString(),                // ex result
                    rc.ToString(),                // rc result
                    6,                                  // Input pad
                    12                                  // Output pad
                );

                
                if (ex == rc)
                {
                    ni += T_P;
                }
            }

            UI.DisplayPrograssBar(ni, T_P * 5);
            UI.DisplayScore(ni, T_P);
            UI.DisplayDivider();

            return ni;
        }

#if TEST6
        public static int Check6()
        {
            // Display header
            UI.DisplayHeader("Test 6");

            // Randomize data
            string[][] phrases = RandomWords();

            
            int sd = 0;

            // Run tests
            for (int i = 0; i < phrases.Length; i++)
            {
                string ex = Test3Utils.Test.WordsToSentence(phrases[i][0], phrases[i][1], phrases[i][2]);
                string rc = Submission.Test6(phrases[i][0], phrases[i][1], phrases[i][2]);

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                                                      // Pass #
                    $"{phrases[i][0]} {phrases[i][1]} {phrases[i][2]}",         // Input
                    ex.ToString(),                                        // ex result
                    rc.ToString(),                                        // rc result
                    33,                                                         // Input pad
                    33                                                          // Output pad
                );

                
                if (ex == rc)
                {
                    sd += T_P;
                }
            }

            UI.DisplayPrograssBar(sd, T_P * 5);

            UI.DisplayScore(sd, T_P);

            UI.DisplayDivider();

            return sd;
        }
#endif

#if TEST7
        public static int Check7()
        {
            // Display header
            UI.DisplayHeader("Test 7");

            // Randomize data
            double[] numbers1 = RandomDoubles();

            
            int ki = 0;

            // Run tests
            for (int i = 0; i < numbers1.Length; i++)
            {
                float ex = Test3Utils.Test.DoubleToFloat(numbers1[i]);
                float rc = Submission.Test7(numbers1[i]);

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                              // Pass #
                    $"{numbers1[i]}",                  // Input
                    ex.ToString(),                // ex result
                    rc.ToString(),                // rc result
                    5,                                  // Input pad
                    5                                   // Output pad
                );

                
                if (ex == rc)
                {
                    ki += T_P;
                }
            }

            UI.DisplayPrograssBar(ki, T_P * 5);

            UI.DisplayScore(ki, T_P);

            UI.DisplayDivider();

            return ki;
        }
#endif

#if TEST8
        public static int Check8()
        {
            // Display header
            UI.DisplayHeader("Test 8");

            // Randomize data
            string[] words = RandomWord();

            
            int oo = 0;

            // Run tests
            for (int i = 0; i < words.Length; i++)
            {
                string ex = Test3Utils.Test.StringToUppercase(words[i]);
                string rc = Submission.Test8(words[i]);

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                              // Pass #
                    $"{words[i]}",                      // Input
                    ex.ToString(),                // ex result
                    rc.ToString(),                // rc result
                    9,                                  // Input pad
                    9                                   // Output pad
                );

                
                if (ex == rc)
                {
                    oo += T_P;
                }
            }

            UI.DisplayPrograssBar(oo, T_P * 5);
            UI.DisplayScore(oo, T_P);
            UI.DisplayDivider();

            return oo;
        }
#endif

#if TEST9
        public static int Check9()
        {
            // Display header
            UI.DisplayHeader("Test 9");

            // Randomize data
            int[] numbers1 = RandomInts();
            int[] numbers2 = RandomInts();


            
            int oi = 0;

            // Run tests
            for (int i = 0; i < numbers1.Length; i++)
            {
                double ex = Math.Round(
                    Test3Utils.Test.AreaOfTriangle(numbers1[i], numbers2[i]),
                    2
                );

                double rc = Math.Round(
                    Submission.Test9(numbers1[i], numbers2[i]),
                    2
                );

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                                              // Pass #
                    $"{numbers1[i]}, {numbers2[i]}",     // Input
                    ex.ToString(),                                // ex result
                    rc.ToString(),                                // rc result
                    6,                                                 // Input pad
                    5                                                   // Output pad
                );

                
                if (ex == rc)
                {
                    oi += T_P;
                }
            }

            UI.DisplayPrograssBar(oi, T_P * 5);
            UI.DisplayScore(oi, T_P);
            UI.DisplayDivider();

            return oi;
        }
#endif

#if TEST10
        public static int Check10()
        {
            // Display header
            UI.DisplayHeader("Test 10", true);

            // Randomize data
            double[] numbers1 = RandomDoubles();
            double[] numbers2 = RandomDoubles();
            double[] numbers3 = RandomDoubles();

            
            int iugh = 0;

            // Run tests
            for (int i = 0; i < numbers1.Length; i++)
            {
                double ex = Math.Round(
                    Test3Utils.Test.DivideNumbers(numbers1[i], numbers2[i], numbers3[i]),
                    2
                );

                double rc = Math.Round(
                    Submission.Test2(numbers1[i], numbers2[i], numbers3[i]),
                    2
                );

                // Display test results
                UI.DisplayTryPass(
                    i + 1,                                              // Pass #
                    $"{numbers1[i]}, {numbers2[i]}, {numbers3[i]}",     // Input
                    ex.ToString(),                                // ex result
                    rc.ToString(),                                // rc result
                    18,                                                 // Input pad
                    5                                                   // Output pad
                );

                
                if (ex == rc)
                {
                    iugh += T_P;
                }
            }

            UI.DisplayPrograssBar(iugh, T_P * 5);
            UI.DisplayScore(iugh, T_P);
            UI.DisplayDivider();

            return iugh;
        }
#endif

        private const int T_P = 2;

        public static void Run()
        {
            int tp = 0;

            tp += Check1();
            tp += Check2();
            tp += Check3();
            tp += Check4();
            tp += Check5();

#if TEST6
            tp += Check6();
#endif

#if TEST7
            tp += Check7();
#endif

#if TEST8
            tp += Check8();
#endif

#if TEST9
            tp += Check9();
#endif

#if TEST10
            tp += Check10();
#endif
            File.SO(tp.ToString());
            UI.DisplayScore(tp, T_P, true);
        }


        private static int[] RandomInts()
        {
            int[] numbers = new int[5];

            Random rnd = new Random();

            for (int i = 0; i < numbers.Length; i++)
            {
                numbers[i] = rnd.Next(1, 11);
            }

            return numbers;
        }

        private static double[] RandomDoubles()
        {
            double[] numbers = new double[5];

            Random rnd = new Random();

            for (int i = 0; i < numbers.Length; i++)
            {
                int number = rnd.Next(1, 11);
                double floatValue = rnd.NextDouble();

                numbers[i] = Math.Round(number + floatValue, 2);
            }

            return numbers;
        }

        private static string[][] RandomWords()
        {
            string[][] phrases = new string[5][];

            string[] starters = new string[] { "Welcome,", "Greetings,", "Hello,", "Hey,", "Hiya," };
            string[] bodies = new string[] { "how are you,", "how ya' doin'", "how's it goin',", "how's is hangin',", "sup," };
            string[] ends = new string[] { "bud", "mac", "man", "buddy", "bruh", "dude", "gamer", "gamerz", "ya'll", "yinz" };

            for (int i = 0; i < phrases.Length; i++)
            {
                Random generator = new Random();

                int starter = generator.Next(starters.Length);
                int body = generator.Next(bodies.Length);
                int end = generator.Next(ends.Length);

                phrases[i] = new string[3];

                phrases[i][0] = starters[starter];
                phrases[i][1] = bodies[body];
                phrases[i][2] = ends[end];

            }

            return phrases;
        }

        private static string[] RandomWord()
        {
            string[] randomWords = new string[5];

            string[] words = { "hello", "hey", "listen", "look", "watch out", "ha", "yah", "wahhhhhh" };
            Random rnd = new Random();

            for (int i = 0; i < randomWords.Length; i++)
            {
                int randomNum = rnd.Next(words.Length);
                randomWords[i] = words[randomNum];
            }


            return randomWords;
        }

        public static class File
        {
            private static readonly string P = "hdkvkt.txt";

            public static void SO(string s)
            {
                if (!System.IO.File.Exists(P))
                {
                    using (StreamWriter sw = System.IO.File.CreateText(P))
                    {
                        sw.WriteLine(s);
                    }
                }
                else
                {
                    System.IO.File.WriteAllText(P, string.Empty);
                    using (StreamWriter sw = System.IO.File.AppendText(P))
                    {
                        sw.WriteLine(s);
                    }
                }
            }
        }
    }
}
