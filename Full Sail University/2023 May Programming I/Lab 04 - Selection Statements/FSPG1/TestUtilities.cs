#define MATH_OPERATOR
#define TEST1
#define TEST2

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FSPG1
{
    public class TestUtilities
    {
        public static Random gen = new Random();
        public static int[] t1 = new int[25] { 4, 2, 0, 1, 3, 3, 3, 0, 4, 4, 2, 1, 4, 1, 2, 3, 0, 1, 3, 4, 3, 2, 2, 2, 1 };
        public static int[] t2 = new int[25] { -319, 122, -441, -25, -377, -9, 367, -217, -293, -324, -225, -207, 111, -479,
                                                -369, -231, -432, 260, 53, -86, -67, 320, 102, -142, 409};
        public static double[] t3 = new double[25] {188.934, 95.16, 479.514, 48.287, 272.482, 14.678, 124.024, 8.006, 96.386,
                                                     36.129, 215.996, 133.161, 58.581, 158.265, 228.648, 238.994, 271.459,
                                                     39.788, 185.278, 28.035, 488.663, 116.774, 279.987, 174.485, 181.41};
        public static double[] t4 = new double[25] { 917.868, 789.589, 671.067, 18.392, 697.436, 459.439, 654.322, 103.5, 309.062,
                                                      834.863, 235.972, 1141.762, 265.18, 895.173, 1998.336, 1510.924, 615.196,
                                                      84.972, 204.279, 1959.15, 330.176, 100.712, 132.73, 1089.482, 261.624 };
        public static int[] t5 = new int[25] { 4, 2, 1, 1, 3, 3, 3, 2, 4, 4, 2, 1, 4, 1, 2, 3, 3, 1, 3, 4, 3, 2, 2, 2, 1 };
        public static double[] t8 = new double[25] { 100.1, 100.0, 99.9, 95.0, 192.2, 90.0, 89.9, 87.85, 85.0, 82.2, 80.2, 80.0, 
                                                     79.9, 75.0, 73.25, 73.0, 72.9, -71.5, 70.1, 70.0, 69.9, 55.7, 14.93,
                                                     0, -2.2 };

        public static Triangle[] deltas = new Triangle[10];

        public static Triangle[] deltas2 = InitializeRights();

        public static char T8(double a)
        {
            char b = '?';

            if (a > 100)
            {
                b = '?';
            }
            else if (a >= 90)
            {
                b = 'A';
            }
            else if (a >= 80)
            {
                b = 'B';
            }
            else if (a >= 73)
            {
                b = 'C';
            }
            else if (a >= 70)
            {
                b = 'D';
            }
            else if (a >= 0)
            {
                b = 'F';
            }
            return b;
        }
        public static bool T6(Triangle a, Triangle b)
        {
            return a.Equals(b);
        }

        public static string T5(int a)
        {
            string b = "Termination";

            switch (a)
            {
                case 1:
                    b = "Verbal reprimand";
                    break;
                case 2:
                    b = "Formal reprimand";
                    break;
                case 3:
                    b = "Suspension";
                    break;
                case 4:
                    b = "Termination";
                    break;
            }
            return b;
        }

        public static double T4(double a, bool b)
        {
            double c = 0;
            if (b)
            {
                c = a * 2.20462;
            }
            else
            {
                c = a * 0.453592;
            }
            return Math.Round(c, 3);
        }

        public static string T3(bool a)
        {
            string b = "Denied";
            if (a)
            {
                b = "Proven";
            }
            return b;
        }

# if TEST1
        public static int T2(int a, int b, MathOperator c)
        {
            int d = 0;

            switch (c)
            {
                case MathOperator.Add:
                    d = a + b;
                    break;
                case MathOperator.Subtract:
                    d = a - b;
                    break;
                case MathOperator.Multiply:
                    d = a * b;
                    break;
                case MathOperator.Divide:
                    d = a / b;
                    break;
                case MathOperator.Modulo:
                    d = a % b;
                    break;
            }
            return d;
        }

        public static MathOperator T1(int a)
        {
            MathOperator b = MathOperator.Modulo;
            switch(a)
            {
                case 0:
                    b = MathOperator.Add;
                    break;
                case 1:
                    b = MathOperator.Subtract;
                    break;
                case 2:
                    b = MathOperator.Multiply;
                    break;
                case 3:
                    b = MathOperator.Divide;
                    break;
                default:
                    b = MathOperator.Modulo;
                    break;
            }
            return b;
        }
# endif

        private static Triangle[] InitializeRights()
        {
            Triangle[] answer = new Triangle[25];

            for(int cntr = 0; cntr<answer.Length;cntr+=2)
            {
                answer[cntr] = new Triangle(gen);
                double longest = answer[cntr].GetA();
                if( longest > answer[cntr].C)
                {
                    answer[cntr].SetA(answer[cntr].C);
                    answer[cntr].C = longest;
                }
                longest = answer[cntr].GetB();
                if (longest > answer[cntr].C)
                {
                    answer[cntr].SetB(answer[cntr].C);
                    answer[cntr].C = longest;
                }
            }
            answer[1] = new Triangle(3, 4, 5);
            answer[3] = new Triangle(8 , 6, 10);
            answer[5] = new Triangle(5, 12, 13);
            answer[7] = new Triangle(9, 12, 15);
            answer[9] = new Triangle(15, 8, 17);
            answer[11] = new Triangle(12, 16, 20);
            answer[13] = new Triangle(15, 20, 25);
            answer[15] = new Triangle(24, 7, 25);
            answer[17] = new Triangle(10, 24, 26);
            answer[19] = new Triangle(21, 20, 29);
            answer[21] = new Triangle(18, 24, 30);
            answer[23] = new Triangle(16, 30, 34);
            return answer;
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
