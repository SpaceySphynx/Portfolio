using System;
using System.IO;

namespace Tester
{
    public class Utility
    {
        public static string BuildFileName(int testNumber)
        {
            return "Lab" + testNumber + "Data.txt";
        }
        public static string BuildFileName(int testNumber, char version)
        {
            return "Lab" + testNumber + version +"Data.txt";
        }
        public static string BuildFileName(string path, int testNumber)
        {
            string retPath = path + "Lab" + testNumber + "Data-Evaluation.txt";
            return retPath;
        }

        public static StreamReader OpenFile(string fName) // throws FileNotFoundException { }
        {
            StreamReader retFile = null;
            try
            {
                retFile = new StreamReader(fName);
            }
            catch(FileNotFoundException nfe)
            {
                Console.WriteLine(nfe.Message);
                throw nfe;
            }
            return retFile;
        }

        public static string AlignOutput(int width, string str)
        {
            string result = str;
            for (int cntr = str.Length; cntr < width; cntr++)
            {
                result += " ";
            }
            return result;
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
