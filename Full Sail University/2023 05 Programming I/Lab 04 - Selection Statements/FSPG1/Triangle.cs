using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FSPG1
{
    public class Triangle
    {
        // 3 sides (a, b and c)
        double a;
        double b;
        double c;

        // Constructors (default and one overloaded)
        public Triangle()
        {
            a = 1;
            b = 1;
            c = 1;
        }

        public Triangle(Random rng)
        {
            do
            {
                a = rng.Next(3, 7);
                b = rng.Next(3, 7);
                c = rng.Next(3, 7);
            } while (!IsTriangle());
        }

        public Triangle(double x, double y, double z)
        {
            a = x;
            b = y;
            c = z;
            bool really = IsTriangle();
            if(!really)
            {
                a = 1;
                b = 1;
                c = 1;
            }
        }


        // Getters/setter or properties for the sides
        public double GetA()
        {
            return a;
        }

        public double GetB()
        {
            return b;
        }

        public void SetA(double x)
        {
            a = x;
        }

        public void SetB(double y)
        {
            b = y;
        }

        public double C
        { 
            get { return c; }
            set { c = value; }
        }

        //What is the area?
        public double Area()
        {
            // heron's formula is area = Math.Sqrt(s*(s-a)*(s-b)*(s-c))
            double s = Perimeter() / 2;
            double area = Math.Sqrt(s * (s - a) * (s - b) * (s - c));
            return area;
        }


        //What is the perimeter?
        public double Perimeter()
        {
            double peri = a + b + c;
            return peri;
        }

        //Is this really a triangle?
        public bool IsTriangle()
        {
            bool yep = true;

            double longest = a;
            double short1 = b;
            double short2 = c;

            if (short1 > longest)
            {
                // swap
                double temp = longest;
                longest = short1;
                short1 = temp;
            }// now longest is definitely longer than short1
            if (short2 > longest)
            {
                // swap
                double temp = longest;
                longest = short2;
                short2 = temp;
            }// now longest is definitely longer than short2
            if (short1 > short2)
            {
                // swap
                double temp = short2;
                short2 = short1;
                short1 = temp;
            }// now short2 is definitely longer than short1
            a = short1;
            b = short2;
            c = longest;

            if ((short1 + short2) <= longest)
            {
                yep = false;
            }
            return yep;
        }

        //Is this really a triangle?
        public bool IsRightTriangle()
        {
            bool yep = false;

            double longest = a;
            double short1 = b;
            double short2 = c;

            if(short1 > longest)
            {
                // swap
                double temp = longest;
                longest = short1;
                short1 = temp;
            }// now longest is definitely longer than short1
            if (short2 > longest)
            {
                // swap
                double temp = longest;
                longest = short2;
                short2 = temp;
            }// now longest is definitely longer than short2
            if(short1 > short2)
            {
                // swap
                double temp = short2;
                short2 = short1;
                short1 = temp;
            }

            if ((short1* short1) + (short2 * short2) == (longest*longest))
            {
                yep = true;
            }
            return yep;
        }

        public Triangle Duplicate()
        {
            return new Triangle(a, b, c);
        }

        //Is it equal to another triangle (is the perimeter and area the same for both)
        public override bool Equals(object obj)
        {
            bool same = true;
            if ((obj == null) || !this.GetType().Equals(obj.GetType()))
            {
                same = false;
            }
            else
            {
                Triangle t2 = (Triangle)obj;
                if (Perimeter() != t2.Perimeter() || Area() != t2.Area())
                {
                    same = false;
                }
            }
            return same;
        }

        public override string ToString()
        {
            return "("+ a + "," + b + "," + c +")";
        }

        public override int GetHashCode()
        {
            return (int) Perimeter();
        }
    }
}
