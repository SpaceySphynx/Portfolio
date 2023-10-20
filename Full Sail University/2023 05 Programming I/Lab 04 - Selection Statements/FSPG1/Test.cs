// Uncomment the following line once you have created your enumerator.

#define MATH_OPERATOR


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

namespace FSPG1
{
    public class Test
    {
        public static void Run()
        {
            for(int cntr = 0; cntr < TestUtilities.deltas.Length;cntr++)
            {
                TestUtilities.deltas[cntr] = new Triangle(TestUtilities.gen);
            }

            int[] set1 = new int[5];
            int[] set2a = new int[5];
            int[] set2b = new int[5];
            int[] set2c = new int[5];
            bool[] set3 = new bool[5];
            double[] set4a = new double[5];
            bool[] set4b = new bool[5];
            int[] set5 = new int[5];
            Triangle [] set6a = new Triangle[5];
            Triangle [] set6b = new Triangle[5];
            Triangle[] set7 = new Triangle[5];
            double[] set8 = new double[5];


            for (int cntr = 0; cntr < 5;cntr++)
            {
                set1[cntr] = TestUtilities.t1[TestUtilities.gen.Next(TestUtilities.t1.Length)];
                set2a[cntr] = TestUtilities.t2[TestUtilities.gen.Next(TestUtilities.t2.Length)];
                set2b[cntr] = TestUtilities.t2[TestUtilities.gen.Next(TestUtilities.t2.Length)];
                set2c[cntr] = TestUtilities.t1[TestUtilities.gen.Next(TestUtilities.t1.Length)];
                set3[cntr] = (TestUtilities.gen.Next() % 2) == 0;
                set4a[cntr] = TestUtilities.t4[TestUtilities.gen.Next(TestUtilities.t4.Length)];
                set4b[cntr] = (TestUtilities.gen.Next() % 2) == 0;
                set5[cntr] = TestUtilities.t5[TestUtilities.gen.Next(TestUtilities.t5.Length)];
                set6a[cntr] = TestUtilities.deltas[TestUtilities.gen.Next(TestUtilities.deltas.Length)];
                set6b[cntr] = TestUtilities.gen.Next() % 2 == 0 ? set6a[cntr].Duplicate() : 
                                       TestUtilities.deltas[TestUtilities.gen.Next(TestUtilities.deltas.Length)];
                set7[cntr] = TestUtilities.deltas2[TestUtilities.gen.Next(TestUtilities.deltas2.Length)];
                set8[cntr] = TestUtilities.t8[TestUtilities.gen.Next(TestUtilities.t8.Length)];
            }


            double passScore = 0;
            double testScore = 0;
            double labScore = 0;
            string indicator = "Fail";

#if MATH_OPERATOR
            UI.DisplayHeader("Test 1");

            for(int cntr = 0;cntr < set1.Length;cntr++)
            {
                MathOperator exp = TestUtilities.T1(set1[cntr]);
                MathOperator sub = Submissions.Test1(set1[cntr]);

                UI.DisplayTryPass(
                    cntr + 1,
                    set1[cntr].ToString(),
                    exp.ToString(),
                    sub.ToString(),
                    0,
                    8
                );


                if (exp == sub)
                {
                    passScore = 2.5;
                }
                testScore += passScore;
                passScore = 0;
            }

            UI.DisplayPrograssBar(testScore, 12.5, 20, Submissions.GAME_MODE);
            UI.DisplayScore(testScore, 2.5);
            UI.DisplayDivider();

            labScore += testScore;
            testScore = 0;

            /////////////////////////////////////////////////////////////////////////////////////////

            UI.DisplayHeader("Test 2");
            for (int cntr = 0; cntr < set2a.Length; cntr++)
            {
                int exp = TestUtilities.T2(set2a[cntr], set2b[cntr], TestUtilities.T1(set2c[cntr]));
                int sub = Submissions.Test2(set2a[cntr],set2b[cntr], TestUtilities.T1(set2c[cntr]));

                UI.DisplayTryPass(
                    cntr + 1,
                    set2a[cntr]+ ", " + set2b[cntr] + ", " + TestUtilities.T1(set2c[cntr]),
                    exp.ToString(),
                    sub.ToString(),
                    20,
                    7
                );

                if (exp == sub)
                {
                    passScore = 2.5;
                }
                testScore += passScore;
                passScore = 0;
            }
            UI.DisplayPrograssBar(testScore, 12.5, 20, Submissions.GAME_MODE);
            UI.DisplayScore(testScore, 2.5);
            UI.DisplayDivider();

            labScore += testScore;
            testScore = 0;
#endif

            /////////////////////////////////////////////////////////////////////////////////////////

            UI.DisplayHeader("Test 3");
            for (int cntr = 0; cntr < set3.Length; cntr++)
            {
                string exp = TestUtilities.T3(set3[cntr]);
                string sub = (Submissions.Test3(set3[cntr]) != null) ? Submissions.Test3(set3[cntr]) : "null";

                if (string.Compare(exp, sub, true) == 0)
                {
                    passScore = 2.5;
                }
                testScore += passScore;

                UI.DisplayTryPass(
                    cntr + 1,
                    set3[cntr].ToString(),
                    exp.ToString(),
                    sub.ToString(),
                    5,
                    7
                );

                passScore = 0;
            }
            UI.DisplayPrograssBar(testScore, 12.5, 20, Submissions.GAME_MODE);
            UI.DisplayScore(testScore, 2.5);
            UI.DisplayDivider();

            labScore += testScore;
            testScore = 0;

            /////////////////////////////////////////////////////////////////////////////////////////

            UI.DisplayHeader("Test 4");
            for (int cntr = 0; cntr < set4a.Length; cntr++)
            {
                double exp = TestUtilities.T4(set4a[cntr],set4b[cntr]);
                double sub = Submissions.Test4(set4a[cntr], set4b[cntr]);
                if (exp == sub)
                {

                    passScore = 2.5;
                }


                testScore += passScore;

                UI.DisplayTryPass(
                    cntr + 1,
                    set4a[cntr] + ", " + set4b[cntr],
                    exp.ToString(),
                    sub.ToString(),
                    15,
                    8
                );

                passScore = 0;

            }
            UI.DisplayPrograssBar(testScore, 12.5, 20, Submissions.GAME_MODE);
            UI.DisplayScore(testScore, 2.5);
            UI.DisplayDivider();

            labScore += testScore;
            testScore = 0;

            /////////////////////////////////////////////////////////////////////////////////////////

            UI.DisplayHeader("Test 5");
            for (int cntr = 0; cntr < set5.Length; cntr++)
            {
                string exp = TestUtilities.T5(set5[cntr]);
                string sub = (Submissions.Test5(set5[cntr]) != null) ? Submissions.Test5(set5[cntr]) : "null";
                if (string.Compare(exp, sub, true) == 0)
                {
                    passScore = 2.5;
                }
                testScore += passScore;

                UI.DisplayTryPass(
                    cntr + 1,
                    set5[cntr].ToString(),
                    exp.ToString().ToLower(),
                    sub.ToString().ToLower(),
                    0,
                    16
                );
                passScore = 0;
            }
            UI.DisplayPrograssBar(testScore, 12.5, 20, Submissions.GAME_MODE);
            UI.DisplayScore(testScore, 2.5);
            UI.DisplayDivider();

            labScore += testScore;
            testScore = 0;

            /////////////////////////////////////////////////////////////////////////////////////////

            UI.DisplayHeader("Test 6");
            for (int cntr = 0; cntr < set6a.Length; cntr++)
            {
                bool exp = TestUtilities.T6(set6a[cntr], set6b[cntr]);
                bool sub = Submissions.Test6(set6a[cntr], set6b[cntr]);
                if (exp == sub)
                {
                    passScore = 2.5;
                }
                testScore += passScore;

                UI.DisplayTryPass(
                    cntr + 1,
                    "T1 " + set6a[cntr] + ", T2 " + set6b[cntr],
                    exp.ToString(),
                    sub.ToString(),
                    0,
                    5
                );

                passScore = 0;
            }
            UI.DisplayPrograssBar(testScore, 12.5, 20, Submissions.GAME_MODE);
            UI.DisplayScore(testScore, 2.5);
            UI.DisplayDivider();

            labScore += testScore;
            testScore = 0;

            /////////////////////////////////////////////////////////////////////////////////////////

            UI.DisplayHeader("Test 7");
            for (int cntr = 0; cntr < set7.Length; cntr++)
            {
                int a = (int)set7[cntr].GetA();
                int b = (int)set7[cntr].GetB();
                int c = (int)set7[cntr].C;
                bool exp = new Triangle(a,b,c).IsRightTriangle();
                bool sub = Submissions.Test7(a,b,c);
                if (exp == sub)
                {
                    passScore = 2.5;
                }
                testScore += passScore;

                UI.DisplayTryPass(
                    cntr + 1,
                    a + ", " + b + ", " + c,
                    exp.ToString(),
                    sub.ToString(),
                    10,
                    5
                );

                passScore = 0;
            }
            UI.DisplayPrograssBar(testScore, 12.5, 20, Submissions.GAME_MODE);
            UI.DisplayScore(testScore, 2.5);
            UI.DisplayDivider();

            labScore += testScore;
            testScore = 0;

            /////////////////////////////////////////////////////////////////////////////////////////

            UI.DisplayHeader("Test 8");
            for (int cntr = 0; cntr < set8.Length; cntr++)
            {
                //char exp = new Triangle(a, b, c).IsRightTriangle();
                char exp = Char.ToUpper(TestUtilities.T8(set8[cntr]));
                char sub = Char.ToUpper(Submissions.Test8(set8[cntr]));
                if (exp == sub)
                {
                    indicator = "Pass";
                    passScore = 2.5;
                }
                testScore += passScore;

                UI.DisplayTryPass(
                    cntr + 1,
                    set8[cntr].ToString(),
                    exp.ToString(),
                    sub.ToString(),
                    4,
                    0
                );

                passScore = 0;
            }
            UI.DisplayPrograssBar(testScore, 12.5, 20, Submissions.GAME_MODE);
            UI.DisplayScore(testScore, 2.5);
            UI.DisplayDivider();

            labScore += testScore;
            testScore = 0;

            /////////////////////////////////////////////////////////////////////////////////////////
            TestUtilities.File.SO(labScore.ToString());

            UI.DisplayPrograssBar(labScore, 100, 50, Submissions.GAME_MODE);
            UI.DisplayScore(labScore, 0, true);
        }
    }
}
