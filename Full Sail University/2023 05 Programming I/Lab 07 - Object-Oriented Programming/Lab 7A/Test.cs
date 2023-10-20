using System;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using FSPG1;
using Lab_7A;
using LabUI;

namespace Tester
{
    class Test
    {
        private static Random rng;
        private static bool t4Checked = false;

        public static void Run(int labNumber)
        {
            rng = new Random(labNumber);
            double labScore = 0;
            double testScore = 0;
            double testTotal = 0;
            int tests = 5;


            UI.DisplayHeader("Test 1");
            // Test1
            for (int ndx = 0; ndx < tests; ndx++)
            {
                string targetAcronym = Utility.acronyms[rng.Next(Utility.acronyms.Length)];
                string [] words = targetAcronym.Split(' ');

                testScore = 0;
                string expected = "";
                foreach(string word in words)
                {
                    expected += word[0];
                }
                StringBuilder sb = Submission.Test1(words);
                string submitted = null;
                if (sb != null)
                {
                    submitted = sb.ToString();
                }
                bool success = expected == submitted;
                if (success)
                {
                    testScore = 2.5;
                }

                UI.DisplayTryPass(
                    ndx + 1,
                    PrintArray(words),
                    expected,
                    submitted != null ? submitted : "",
                    45,
                    5
                );

                testTotal += testScore;
                labScore += testScore;
            }

            UI.DisplayPrograssBar(testTotal, 2.5 * 5, 20, Submission.GAME_MODE);
            UI.DisplayScore(testTotal, 2.5);
            UI.DisplayDivider();

            UI.DisplayHeader("Test 2");

            testTotal = 0;
            // Test2
            for (int ndx = 0; ndx < tests; ndx++)
            {
                testScore = 0;
                Pt pt = Utility.points[rng.Next(0,Utility.points.Length)];
                float x = pt.x;
                float y = pt.y;
                float rad = pt.r;
                MyCir expected = new MyCir(x, y, rad);

                object submitted = Submission.Test2(x,y,rad);

                bool success = CompareCircles(expected, submitted);
                if (success)
                {
                    testScore = 2.5;
                }
                if (submitted != null && submitted.GetType() == typeof(Circle))
                {
                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        expected.GetX() + ", " + expected.GetY() + ", " + expected.GetRadius(),
                        ((Circle)submitted).GetX() + ", " + ((Circle)submitted).GetY() + ", " + ((Circle)submitted).GetRadius(),
                        20,
                        20
                    );
                } else if (submitted != null)
                {
                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        expected.GetX() + ", " + expected.GetY() + ", " + expected.GetRadius(),
                        submitted.ToString(),
                        20,
                        20
                    );
                }
                else
                {
                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        expected.GetX() + ", " + expected.GetY() + ", " + expected.GetRadius(),
                        "null",
                        20,
                        20
                    );
                }

                testTotal += testScore;
                labScore += testScore;
            }
            UI.DisplayPrograssBar(testTotal, 2.5 * 5, 20, Submission.GAME_MODE);
            UI.DisplayScore(testTotal, 2.5);
            UI.DisplayDivider();

            UI.DisplayHeader("Test 3");
            testTotal = 0;
            // Test3
            for (int ndx = 0; ndx < tests; ndx++)
            {
                testScore = 0;
                Pt pt = Utility.points[rng.Next(0, Utility.points.Length)];
                float x = pt.x;
                float y = pt.y;
                float rad = pt.r;
                MyCir expected = new MyCir(x, y, rad);

                object submitted = Submission.Test3(x, y, rad);

                bool success = false;
                if(submitted != null && submitted.GetType() == typeof(Circle))
                {
                    float answer = ((Circle)(submitted)).GetArea(); 
                    if (Math.Round(expected.GetArea(),2) == Math.Round(answer,2))
                    {
                        success = true;
                    }
                }
                if (success)
                {
                    testScore = 2.5;
                }
                if (submitted != null && submitted.GetType() == typeof(Circle))
                {

                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        Math.Round(expected.GetArea(), 3).ToString(),
                        Math.Round(((Circle)submitted).GetArea(), 3).ToString(),
                        20,
                        9
                    );
                }
                else
                {
                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        Math.Round(expected.GetArea(), 3).ToString(),
                        "null",
                        20,
                        9
                    );
                }

                testTotal += testScore;
                labScore += testScore;
            }
            UI.DisplayPrograssBar(testTotal, 2.5 * 5, 20, Submission.GAME_MODE);
            UI.DisplayScore(testTotal, 2.5);
            UI.DisplayDivider();

            UI.DisplayHeader("Test 4");
            testTotal = 0;
            // Test4
            for (int ndx = 0; ndx < tests; ndx++)
            {
                testScore = 0;
                Pt pt = Utility.points[rng.Next(0, Utility.points.Length)];
                float x = pt.x;
                float y = pt.y;
                float rad = pt.r;
                Pt pt2 = Utility.points[rng.Next(0, Utility.points.Length)];
                float x2 = pt2.x;
                float y2 = pt2.y;
                if ((rng.Next(4) == ndx) || (ndx == 4 && !t4Checked))
                {
                    x2 = x + (rad*0.99f);
                    y2 = y + (rad*0.99f);
                    t4Checked = true;
                }

                MyCir expected = new MyCir(x, y, rad);

                object submitted = Submission.Test4(x, y, rad);

                bool success = false;
                if (submitted != null && submitted.GetType() == typeof(Circle))
                {
                    if (expected.Contains(x2,y2) == ((Circle)submitted).Contains(x2,y2))
                    {
                        success = true;
                    }
                }
                if (success)
                {
                    testScore = 2.5;
                }
                if (submitted != null && submitted.GetType() == typeof(Circle))
                {
                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        expected.Contains(x2, y2).ToString(),
                        ((Circle)submitted).Contains(x2, y2).ToString(),
                        28,
                        5
                    );
                }
                else
                {

                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        expected.Contains(x2, y2).ToString(),
                        "null",
                        28,
                        5
                    );
                }

                testTotal += testScore;
                labScore += testScore;
            }
            UI.DisplayPrograssBar(testTotal, 2.5 * 5, 20, Submission.GAME_MODE);
            UI.DisplayScore(testTotal, 2.5);
            UI.DisplayDivider();

            UI.DisplayHeader("Test 5");
            testTotal = 0;
            // Test5
            for (int ndx = 0; ndx < tests; ndx++)
            {
                testScore = 0;
                Pt pt = Utility.points[rng.Next(0, Utility.points.Length)];
                float x = pt.x;
                float y = pt.y;
                float rad = pt.r;
                MyCir expected = new MyCir(x, y, rad);

                object submitted = Submission.Test5(x, y, rad);

                bool success = false;
                if (submitted != null && submitted.GetType() == typeof(Circle))
                {
                    float answer = ((Circle)(submitted)).GetCircumference(); 
                    if (Math.Round(expected.GetCircumference(),2) == Math.Round(answer,2))
                    {
                        success = true;
                    }
                }
                if (success)
                {
                    testScore = 2.5;
                }
                if (submitted != null && submitted.GetType() == typeof(Circle))
                {
                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        Math.Round(expected.GetCircumference(), 3).ToString(),
                        Math.Round(((Circle)submitted).GetCircumference(), 3).ToString(),
                        20,
                        20
                    );
                }
                else
                {
                    UI.DisplayTryPass(
                        ndx + 1,
                        x + ", " + y + ", " + rad,
                        Math.Round(expected.GetCircumference(), 3).ToString(),
                        "null",
                        20,
                        20
                    );
                }

                testTotal += testScore;
                labScore += testScore;
            }
            UI.DisplayPrograssBar(testTotal, 2.5 * 5, 20, Submission.GAME_MODE);
            UI.DisplayScore(testTotal, 2.5);
            UI.DisplayDivider();

            UI.DisplayHeader("Test 6");
            testTotal = 0;
            // Test6
            for (int ndx = 0; ndx < tests; ndx++)
            {
                testScore = 0;
                Pairs pair = Utility.pairs[rng.Next(0, Utility.pairs.Length)];
                string s1 = pair.First;
                string s2 = pair.Second;
                bool ignore = pair.IgnoreIt;

                int expected = String.Compare(s1, s2, ignore);

                int submitted = Submission.Test6(s1,s2,ignore);

                bool success = expected == submitted;

                if (success)
                {
                    testScore = 2.5;
                }

                UI.DisplayTryPass(
                    ndx + 1,
                    s1 + ", " + s2 + ", " + ignore,
                    expected.ToString(),
                    submitted.ToString(),
                    29,
                    2
                );

                testTotal += testScore;
                labScore += testScore;
            }
            UI.DisplayPrograssBar(testTotal, 2.5 * 5, 20, Submission.GAME_MODE);
            UI.DisplayScore(testTotal, 2.5);
            UI.DisplayDivider();

            UI.DisplayHeader("Test 7");
            testTotal = 0;
            // Test7
            for (int ndx = 0; ndx < tests; ndx++)
            {
                testScore = 0;
                Secret secret = Utility.secrets[rng.Next(0, Utility.secrets.Length)];
                sbyte off = secret.Shift;
                string msg = secret.Phrase;

                string expected = (new TC(off)).Encode(msg);

                string submitted = Submission.Test7(off,msg);

                bool success = expected == submitted;

                if (success)
                {
                    testScore = 2.5;
                }

                var line = "null";

                if(submitted != null)
                {
                    const string reduceMultiSpace = @"[ ]{2,}";
                    line = Regex.Replace(submitted.Replace("\t", " "), reduceMultiSpace, " ");
                }
                

                UI.DisplayTryPass(
                    ndx + 1,
                    off + ", " + msg,
                    line,
                    submitted != null ? line : "null",
                    29,
                    29
                );

                testTotal += testScore;
                labScore += testScore;
            }
            UI.DisplayPrograssBar(testTotal, 2.5 * 5, 20, Submission.GAME_MODE);
            UI.DisplayScore(testTotal, 2.5);
            UI.DisplayDivider();

            UI.DisplayHeader("Test 8");
            testTotal = 0;
            // Test8
            for (int ndx = 0; ndx < tests; ndx++)
            {
                testScore = 0;
                Secret secret = Utility.secrets[rng.Next(0, Utility.secrets.Length)];
                sbyte off = secret.Shift;
                string msg = (new TC(off)).Encode(secret.Phrase);

                string expected = (new TC(off)).Decode(msg);

                string submitted = Submission.Test8(off, msg);

                bool success = expected == submitted;

                if (success)
                {
                    testScore = 2.5;
                }

                const string reduceMultiSpace = @"[ ]{2,}";
                var line = Regex.Replace(msg.Replace("\t", " "), reduceMultiSpace, " ");

                UI.DisplayTryPass(
                    ndx + 1,
                    off + ", " + line,
                    expected,
                    submitted != null ? submitted : "null",
                    29,
                    29
                );

                testTotal += testScore;
                labScore += testScore;
            }
            UI.DisplayPrograssBar(testTotal, 2.5 * 5, 20, Submission.GAME_MODE);
            UI.DisplayScore(testTotal, 2.5);
            UI.DisplayDivider();

            Utility.File.SO(labScore.ToString());

            UI.DisplayPrograssBar(labScore, 100, 50, Submission.GAME_MODE);
            UI.DisplayScore(labScore, 100, true);
        }

        public static string PrintArray(string[] array)
        {
            string retVal = null;

            if(array != null)
            {
                retVal = "";
                for(int ndx = 0; ndx < array.Length-1;ndx++)
                {
                    retVal += array[ndx] + " ";
                }
                retVal += array[array.Length - 1];
            }
            return retVal;
        }

        private static bool CompareCircles(MyCir c1,object c)
        {
            bool same = true;
            if(c == null)
            {
                same = false;
            }
            else if(c.GetType() != typeof(Circle))
            {
                same = false;
            }
            else
            {
                Circle c2 = (Circle)c;
                float x = c2.GetX();
                float y = c2.GetY();
                float radius = c2.GetRadius();

                if (c1.GetX() != x || c1.GetY() != y || c1.GetRadius() != radius)
                    same = false;
            }
            return same;
        }

    }
}
