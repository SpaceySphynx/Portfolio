using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphicsLibrary
{
    // Created public struct Point2D.
    public struct Point2D
    {
        // A constructor which initializes the X and Y with the provided arguments.
        // https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/builtin-types/struct
        // I followed the microsoft link provided in our PDF and structured it exactly like that yet
        // the number 7 selection self check keeps saying it doesn't see the X and Y variables. 
        // I tried about 10 different ways of formating this, variables first, adding set; adding : this()
        // changing the names of the x and y and adjusting public and many other failed attempts.
        // I decided to put it back to the original microsoft suggested C# format for constructors and await for your feedback.
        public Point2D(int x, int y) { X = x; Y = y; }
        // Integers X and Y coordinates of the point.
        public int X { get; }
        public int Y { get; }
    }
    // Created the Shape class.
    public class Shape
    {
        // StartPoint is a property of type Point2D that represents the starting point of the shape.
        public Point2D StartPt { get; set; }
        public ConsoleColor Color { get; set; }
        // Initializes a new instance of the Shape class with the provided start point and color.
        public Shape(Point2D startPt, ConsoleColor color)
        {
            StartPt = startPt;
            Color = color;
        }
        // An alternative constructor that takes X and Y coordinates directly along with the color.
        public Shape(int x, int y, ConsoleColor color)
        {
            StartPt = new Point2D(x, y);
            Color = color;
        }
        // A virtual method Draw() which draws the shape on the console.
        // It sets the console's color and cursor position and then prints a space character.
        public virtual void Draw()
        {
            Console.BackgroundColor = Color;
            Console.SetCursorPosition(StartPt.X, StartPt.Y);
            Console.Write(" ");
            Console.ResetColor();
        }
    }
    // Created the Line class which derives from Shape.
    public class Line : Shape
    {
        // EndPoint represents the end point of the line.
        public Point2D EndPt { get; set; }
        // The constructor takes in the start point, end point, and color, then initializes a new instance of the Line class.
        public Line(Point2D startPoint, Point2D endPt, ConsoleColor color)
            : base(startPoint, color)
        {
            EndPt = endPt;
        }
        // The Draw() method of Line is overridden here.
        public override void Draw()
        {
            // Save the original console color as originalColor variable.
            ConsoleColor originalColor = Console.BackgroundColor;
            // Set the console color to this shape's color.
            Console.BackgroundColor = Color;
            // This is a placeholder code for PlotLine.
            PlotLine(StartPt, EndPt);
            // Reset the console color.
            Console.BackgroundColor = originalColor;
        }
        // The following is copy and pasted from the week 3 instruction PDF but
        // then was editted into functioning C# code as that was sudo code used as a blueprint.
        private void PlotLine(Point2D startPt, Point2D endPt)
        {
            int x0 = startPt.X;
            int y0 = startPt.Y;
            int x1 = endPt.X;
            int y1 = endPt.Y;

            int dx = Math.Abs(x1 - x0);
            int sx = x0 < x1 ? 1 : -1;
            int dy = -Math.Abs(y1 - y0);
            int sy = y0 < y1 ? 1 : -1;
            int error = dx + dy;

            while (true)
            {
                Plot(x0, y0);
                if (x0 == x1 && y0 == y1)
                    break;
                int e2 = 2 * error;
                if (e2 >= dy)
                {
                    if (x0 == x1)
                        break;
                    error += dy;
                    x0 += sx;
                }
                if (e2 <= dx)
                {
                    if (y0 == y1)
                        break;
                    error += dx;
                    y0 += sy;
                }
            }
        }
        // Plot() is another helper method that writes a space character at the given (x, y) position in the console        
        // provided it is within the window bounds.
        private void Plot(int x, int y)
        {
            if (x >= 0 && y >= 0 && x < Console.WindowWidth && y < Console.WindowHeight)
            {
                Console.SetCursorPosition(x, y);
                Console.Write(" ");
            }
        }
    }
    // Created the Rectangle class which derives from Shape.
    public class Rectangle : Shape
    {
        // Varible Width and Height with get and set to represent the width and height of the Rectangle.
        public int Width { get; set; }
        public int Height { get; set; }
        // _lines is a private list that contains all the lines that make up the rectangle's outline.
        private List<Line> _lines;
        // The constructor initializes a new instance of the Rectangle class.
        public Rectangle(int width, int height, Point2D startPt, ConsoleColor color)
            : base(startPt, color)
        {
            Width = width;
            Height = height;
            _lines = new List<Line>();
            // Calculates the corner points of the rectangle
            Point2D topRight = new Point2D(startPt.X + width, startPt.Y);
            Point2D bottomLeft = new Point2D(startPt.X, startPt.Y + height);
            Point2D bottomRight = new Point2D(startPt.X + width, startPt.Y + height);
            // Line objects representing the sides of the rectangle, and adds them to the _lines list.
            _lines.Add(new Line(startPt, topRight, color));      // Top line
            _lines.Add(new Line(topRight, bottomRight, color));  // Right line
            _lines.Add(new Line(bottomLeft, bottomRight, color)); // Bottom line
            _lines.Add(new Line(startPt, bottomLeft, color));    // Left line
        }
        // The Draw() method of Rectangle is overridden here. It draws each line in the _lines list to draw the rectangle on the console.
        public override void Draw()
        {
            foreach (var line in _lines)
            {
                line.Draw();
            }
        }
    }
    // Created the Triangle class which derives from Shape.
    public class Triangle : Shape
    {
        // Varible P2 and P3 with get and set.
        public Point2D P2 { get; set; }
        public Point2D P3 { get; set; }
        // _lines is a private list that contains all the lines that make up the triangle's outline.
        private List<Line> _lines;
        // The constructor initializes a new instance of the Triangle class. 
        public Triangle(Point2D p1, Point2D p2, Point2D p3, ConsoleColor color)
            : base(p1, color)
        {
            P2 = p2;
            P3 = p3;
            _lines = new List<Line>();
            // Line objects representing the sides of the triangle, and adds them to the _lines list.
            _lines.Add(new Line(p1, P2, color));
            _lines.Add(new Line(P2, P3, color));
            _lines.Add(new Line(P3, p1, color));
        }
        // The Draw() method of Triangle is overridden here. It draws each line in the _lines list to draw the triangle on the console.
        public override void Draw()
        {
            foreach (var line in _lines)
            {
                line.Draw();
            }
        }
    }
    // Created the Circle class which derives from Shape.
    public class Circle : Shape
    {
        // Get and set the the Radius variable
        public int Radius { get; set; }
        // The constructor initializes a new instance of the Circle class. 
        public Circle(int radius, Point2D centerPt, ConsoleColor color)
            : base(centerPt, color)
        {
            Radius = radius;
        }
        // Here is the pseudecode area which I edited until I got it working. I thought it was confusing though in a way because it shows DrawCirclePoints
        // taking in four variables but Point2D center is brining in 2 variables but as one pass so it does seem a bit odd but it passes everything.
        private void DrawCirclePoints(Point2D center, int x, int y)
        {
            Plot(center.X + x, center.Y + y);
            Plot(center.X - x, center.Y + y);
            Plot(center.X + x, center.Y - y);
            Plot(center.X - x, center.Y - y);
            Plot(center.X + y, center.Y + x);
            Plot(center.X - y, center.Y + x);
            Plot(center.X + y, center.Y - x);
            Plot(center.X - y, center.Y - x);
        }
        private void DrawCircle(Point2D center, int radius)
        {
            int x = 0;
            int y = radius;
            int d = 3 - 2 * radius;

            DrawCirclePoints(center, x, y);

            while (y >= x)
            {
                x++;
                if (d > 0)
                {
                    y--;
                    d = d + 4 * (x - y) + 10;
                }
                else
                {
                    d = d + 4 * x + 6;
                }
                DrawCirclePoints(center, x, y);
            }
        }

        private void Plot(int x, int y)
        {
            if (x >= 0 && y >= 0 && x < Console.WindowWidth && y < Console.WindowHeight)
            {
                Console.SetCursorPosition(x, y);
                Console.Write(" ");
            }
        }
        // The Draw() method of Circle is overridden here. It draws each line in the _lines list to draw the Circle on the console.
        public override void Draw()
        {
            ConsoleColor originalColor = Console.BackgroundColor;
            Console.BackgroundColor = Color;
            DrawCircle(StartPt, Radius);
            Console.BackgroundColor = originalColor;
        }
    }


    public class SampleClass
    {
        /*
                Fields
        */
        private int _sampleField = 0;



        /*
                Properties
        */
        public string SampleAutoProperty { get; set; }


        private double _sampleBackingField;
        public double SampleFullProperty
        {
            get { return _sampleBackingField; }
            set { _sampleBackingField = value; }
        }


        /*
                Constructors
        */
        // sample default constructor (no parameters)
        public SampleClass()
        {

        }

        //sample constructor with parameters
        public SampleClass(int intParam, double doubleParam, string stringParam)
        {
            SampleAutoProperty = stringParam;
            SampleFullProperty = doubleParam;
            _sampleField = intParam;
        }



        /*
                Methods
        */
        //instance (non-static) method
        public void SampleMethod()
        {
            Console.WriteLine($"{SampleAutoProperty} {SampleFullProperty} {_sampleField}");
        }



    }
}
