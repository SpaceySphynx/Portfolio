using GraphicsLibrary;
using PG2Input;
using HeroesV2.Tests;

namespace Graphics
{
    /*  Lab Video   
      
        Here's a video showing what the lab could look like when completed:
        https://web.microsoftstream.com/video/0781f701-2425-434f-bfe0-cb9ecb484fe7

    */
    internal class Program
    {
        static Random _rando = new Random();
        static void Main(string[] args)
        {
            string userName = string.Empty;
            Input.GetString("What is your name? ", ref userName);
            Console.Clear();

            List<string> menu = new List<string>()
            { "1. Draw Shape", "2. Draw Line", "3. Draw Rectangle", "4. Draw Triangle", "5. Draw Circle", "6. Draw Random Shapes", "7. Run Lab tests", "8. Exit"};


            /*
                        SAMPLES
            */
            // creating instances
            SampleClass sampleInstance = new SampleClass(); //call the default constructor
            SampleClass sampleInstance2 = new SampleClass(5, 13.7, "Sample"); //call the constructor with parameters

            // accessing members
            string sample = sampleInstance.SampleAutoProperty; //use the . operator on the instance variable

            // calling methods
            sampleInstance2.SampleMethod(); //use the . operator when calling instance methods on instance variables

            //
            //
            // Part A-1: Point2D struct
            //
            //  Add a Point2D struct to the GraphicsLibrary project.
            //  An easy way to create a struct is to add a new class then change it from a class to a struct.
            //
            //  Add 2 fields: X and Y.The type of these fields is int.
            //  Add a constructor that takes 2 int parameters. Use these to initialize X and Y.



            //
            //
            // Part A-2: Shape class
            //
            //  Add a Shape class to the GraphicsLibrary project.
            //
            //  Add 2 properties: a Point2D property called StartPt and a ConsoleColor property called Color.
            //
            //  Add 2 constructors:
            //      •	First constructor takes 2 parameters: a Point2D and a ConsoleColor.Set the properties with these parameters.
            //      •	Second constructor takes 3 parameters: 2 ints for the x and y and a ConsoleColor.Use the x and y parameters to initialize the StartPt property.Use the ConsoleColor parameter to set the Color property.
            //
            //  Add a Draw method.
            //      •	Set the background color.
            //      •	Move the cursor to the Point2D position.
            //      •	Print a space.
            //      •	Reset the color in the console.


            int selection;
            do
            {
                Console.Clear();
                Console.WriteLine($"Hello {userName}. Welcome to The Graphics Lab");
                Input.GetMenuChoice("Choice? ", menu, out selection);
                Console.Clear();

                switch (selection)
                {
                    case 1:
                        //
                        // Part A-3: Draw Shape menu
                        //      Clear the screen.
                        //      Generate a random Point2D with an x,y anywhere in the console.
                        //      Use that point to create a Shape instance with any color you want.
                        //      Call Draw on the shape instance.
                        //

                        // First cleared the console screen.
                        Console.Clear();
                        // Created variable maxY0 that generates a random int between 0 and the console window width.
                        // Created variable maxX0 that generates a random int between 0 and the console window height.
                        int maxX_0 = Program._rando.Next(Console.WindowWidth);
                        int maxY_0 = Program._rando.Next(Console.WindowHeight);
                        // Point2D creates a new object with random X and Y coordinates that could be anywhere within the Console Window.
                        Point2D point_0 = new Point2D(maxX_0, maxY_0);
                        // Next we create a Shape constructor instance and passes the Point2D as point variable and ConsoleColor and I picked Cyan.
                        Shape shape = new Shape(point_0, ConsoleColor.Cyan);
                        // Calls Draw() method on the shape instance.
                        shape.Draw();
                        break;

                    case 2:
                        //
                        // Part B-1: Line Class
                        //
                        //  Add a Line class to the GraphicsLibrary project. The Line class should derive from Shape.
                        //
                        //  Add 1 property: a Point2D property called EndPt.
                        //
                        //  Implement the pseudocode for the PlotLine and Plot methods.
                        //  (see the pseudo - code for plotLine in the lab document in the Solution Items in Solution Explorer).
                        //  NOTE: Plot is a method that moves the cursor to the x,y position and prints a space.
                        //
                        //  Override the Draw method of the Shape class (that means you need to mark the base as virtual and Line’s Draw method as override).
                        //  Do not call the base. Instead, set the background color, call PlotLine, then reset the color.

                        //
                        // In Main (here), add code to case 2 of the switch.
                        //      Clear the screen.
                        //      Generate 2 random Point2D points with an x,y anywhere in the console.
                        //      Use those points to create a Line instance with any color you want.
                        //      Call Draw on the Line instance.

                        // First cleared the console screen.
                        Console.Clear();
                        // Create variable maxX1 to generate random WindowWidth and maxY1 to generate random WindowHeight and assign them to point1 and point2.
                        int maxX_1 = Program._rando.Next(Console.WindowWidth);
                        int maxY_1 = Program._rando.Next(Console.WindowHeight);
                        int maxX_2 = Program._rando.Next(Console.WindowWidth);
                        int maxY_2 = Program._rando.Next(Console.WindowHeight);
                        Point2D point_1 = new Point2D(maxX_1, maxY_1);
                        Point2D point_2 = new Point2D(maxX_2, maxY_2);
                        // Line instance passing in point1, point2 and ConsoleColor which I selected Red.
                        Line line = new Line(point_1, point_2, ConsoleColor.Red);
                        // Call Draw() method on the Line instance.
                        line.Draw();
                        break;
                    case 3:
                        //
                        // Part B-2: Rectangle Class
                        //
                        //  Add a Rectangle class to the GraphicsLibrary project. The Rectangle class should derive from Shape.
                        //
                        //  Add 2 int properties: Width and Height.
                        //  Add 1 List<Line> field: _lines.
                        //  Add 1 constructor with the following parameters: width, height, startPt, color.Pass the startPt and color to the base constructor.Use width and height to set the properties. The constructor should create 4 lines and add them to the _lines field.
                        //  The 4 lines:
                        //      •	top left to top right
                        //      •	top right to bottom right
                        //      •	bottom left to bottom right
                        //      •	top left to bottom left
                        //
                        //   Override the Draw method of the Shape class (that means you need to mark the base as virtual and Rectangle’s Draw method as override).
                        //   Do not call the base. Instead, call the Draw method of each line in the _lines list.


                        //
                        // In Main (here), add code to case 3 of the switch.
                        //      •	Clear the screen.
                        //      •	Generate a random Point2D point with an x, y anywhere in the console. This point will be the top-left position of the rectangle.
                        //      •	Calculate a random width and height – ensure that it will NOT extend the rectangle beyond the bounds of the console.
                        //      •	Use the point, width, and height to create a Rectangle instance with any color you want.
                        //      •	Call Draw on the Rectangle instance.

                        // First cleared the console screen.
                        Console.Clear();
                        // Create variable maxX3 to generate a random WindowWidth and maxY3 to generate a random WindowHeight.                  
                        int maxX_3 = Program._rando.Next(Console.WindowWidth);
                        int maxY_3 = Program._rando.Next(Console.WindowHeight);
                        // This is going to be used to define the topLeft corner of the rectangle passing maxX3 and maxY3.
                        Point2D topLeft = new Point2D(maxX_3, maxY_3);
                        // Creating variables to store the random size and height of the rectangle.
                        int width = Program._rando.Next(1, Console.WindowWidth - maxX_3);
                        int height = Program._rando.Next(1, Console.WindowHeight - maxY_3);
                        // Rectangle instance passing in width, height, topLeft and ConsoleColor which I selected Blue.
                        Rectangle rectangle = new Rectangle(width, height, topLeft, ConsoleColor.Blue);
                        // Call Draw() method on the rectangle instance.
                        rectangle.Draw();
                        break;
                    case 4:
                        //
                        // Part B-3: Triangle Class
                        //
                        // Add a Triangle class to the GraphicsLibrary project. The Triangle class should derive from Shape.
                        // Add 2 Point2D properties: P2 and P3.
                        // Add 1 List<Line> field: _lines.
                        // Add 1 constructor with the following parameters: p1, p2, p3, color.Pass the p1 and color to the base constructor.Use p2 and p3 to
                        // set the properties. The constructor should create 3 lines connecting the points and add them to the _lines field.
                        //
                        // The 3 lines:
                        //      • P1 to p2
                        //      • P2 to p3
                        //      • P3 to p1
                        //
                        // Override the Draw method of the Shape class (that means you need to mark the base as virtual and Triangle’s Draw method as
                        // override). Do not call the base. Instead, call the Draw method of each line in the _lines list.

                        //
                        // In Main (here), add code to case 4 of the menu switch.
                        //      • Clear the screen.                        
                        //      • Generate 3 random Point2D points with an x, y anywhere in the console.
                        //      • Use the points to create a Triangle instance with any color you want.
                        //      • Call Draw on the Triangle instance.

                        // First cleared the console screen.
                        Console.Clear();
                        // Created the random variables to be used for the X and Y points
                        int maxX_4 = Program._rando.Next(Console.WindowWidth);
                        int maxY_4 = Program._rando.Next(Console.WindowHeight);
                        int maxX_5 = Program._rando.Next(Console.WindowWidth);
                        int maxY_5 = Program._rando.Next(Console.WindowHeight);
                        int maxX_6 = Program._rando.Next(Console.WindowWidth);
                        int maxY_6 = Program._rando.Next(Console.WindowHeight);
                        // Create three variables to Generate 3 random points for the corners of the triangle.
                        Point2D p1 = new Point2D(maxX_4, maxY_4);
                        Point2D p2 = new Point2D(maxX_5, maxY_5);
                        Point2D p3 = new Point2D(maxX_6, maxY_6);

                        // I realize I can do the code like the following below but I feel it's really long on the line and feels a bit confusing
                        // So I decided to create variables to store the values and pass instead. Not sure which would be preferred.
                        //      Point2D p1 = new Point2D(_rando.Next(Console.WindowWidth), _rando.Next(Console.WindowHeight));
                        //      Point2D p2 = new Point2D(_rando.Next(Console.WindowWidth), _rando.Next(Console.WindowHeight));
                        //      Point2D p3 = new Point2D(_rando.Next(Console.WindowWidth), _rando.Next(Console.WindowHeight));

                        // Create a triangle instance with the random points p1, p2, p3 and the console color I picked of Yellow.
                        Triangle triangle = new Triangle(p1, p2, p3, ConsoleColor.Yellow);

                        // Call Draw() method on the triangle instance.
                        triangle.Draw();
                        break;
                    case 5:
                        //
                        // Part B-4: Circle Class
                        //
                        //  Add a Circle class to the GraphicsLibrary project. The Circle class should derive from Shape.
                        //
                        //  Add 1 int property: Radius.
                        //  Add 1 constructor with the following parameters: radius, startPt, color.
                        //      Pass the startPt and color to the base constructor. Use radius parameter to set the Radius property.
                        //
                        //  Implement the pseudocode for the DrawCircle, DrawCirclePoints, and Plot methods.
                        //  (see the pseudo - code in the lab document in the Solution Items in Solution Explorer).
                        //  NOTE: Plot is a method that moves the cursor to the x, y position and prints a space.
                        //
                        //  Override the Draw method of the Shape class (that means you need to mark the base as virtual and Circle’s Draw method as override).
                        //  Do not call the base. Instead, set the background color, call DrawCircle, then reset the color.

                        //
                        // In Main (here), add code to case 5 of the switch.
                        //      •	Clear the screen.
                        //      •	Generate a random Point2D point with an x, y anywhere in the console. This point will be the center position of the circle.
                        //      •	Calculate a random radius – ensure that it will NOT extend the circle beyond the bounds of the console.
                        //      •	Use the point and radius to create a Circle instance with any color you want.
                        //      •	Call Draw on the Circle instance.

                        // First cleared the console screen.
                        Console.Clear();
                        // Created the random variables to be used for the X and Y points.
                        int maxX_7 = Program._rando.Next(Console.WindowWidth);
                        int maxY_7 = Program._rando.Next(Console.WindowHeight);
                        // Generate a random center point.
                        Point2D center = new Point2D(maxX_7, maxY_7);
                        // Calculate a random radius ensuring that it will NOT extend the circle beyond the bounds of the console.
                        // int radius = Math.Min(Math.Min(center.X, center.Y), Math.Min(Console.WindowWidth - center.X, Console.WindowHeight - center.Y));
                        // tried this but was still going out of bounds so added -1 which seems to correct this issue.
                        int radius = Math.Min(Math.Min(center.X, center.Y), Math.Min(Console.WindowWidth - center.X - 1, Console.WindowHeight - center.Y - 1));
                        // Create a circle instance with the random center and radius by passing radius, center and the Green ConsoleColor.
                        Circle circle = new Circle(radius, center, ConsoleColor.Green);
                        // Call Draw() method on the circle instance.
                        circle.Draw();
                        break;
                    case 6:
                        //
                        // Part C-1: Random Shapes
                        //
                        //
                        // In Main (here), add code to case 6 of the switch.
                        // •	Clear the screen.
                        // •	Create a List variable that holds Shapes.
                        // •	Create 100 random shapes and add them to the list.
                        //          o Randomly pick which type of shape to create(Shape, Line, Rectangle, Triangle, Circle).
                        //          o Create the instance according to its shape. (see the case statements before to create the different shapes)
                        // •	After this loop, loop over the shapes list and call Draw on each shape.

                        // First cleared the console screen.
                        Console.Clear();
                        // Created the List variable to hold the Shapes.
                        List<Shape> shapes = new List<Shape>();
                        // variables that take in the Console Width and Height.
                        int maxWidth = Console.WindowWidth;
                        int maxHeight = Console.WindowHeight;
                        // Created a standard for loop that will run until 100 shapes have been added to the list and drawn to console.
                        for (int i = 0; i < 100; i++)
                        {
                            // random start point within the console size.
                            Point2D startPt_0 = new Point2D(_rando.Next(maxWidth), _rando.Next(maxHeight));
                            int shapeType = _rando.Next(5);
                            // switch that can make any of the shapes in a random color.
                            switch (shapeType)
                            {
                                case 0:
                                    shapes.Add(new Shape(startPt_0, (ConsoleColor)_rando.Next(16)));
                                    break;

                                case 1:
                                    Point2D endPt_0 = new Point2D(_rando.Next(maxWidth), _rando.Next(maxHeight));
                                    shapes.Add(new Line(startPt_0, endPt_0, (ConsoleColor)_rando.Next(16)));
                                    break;

                                case 2:
                                    int rectWidth = _rando.Next(1, maxWidth - startPt_0.X);
                                    int rectHeight = _rando.Next(1, maxHeight - startPt_0.Y);
                                    shapes.Add(new Rectangle(rectWidth, rectHeight, startPt_0, (ConsoleColor)_rando.Next(16)));
                                    break;

                                case 3:
                                    Point2D p2_0 = new Point2D(_rando.Next(maxWidth), _rando.Next(maxHeight));
                                    Point2D p3_0 = new Point2D(_rando.Next(maxWidth), _rando.Next(maxHeight));
                                    shapes.Add(new Triangle(startPt_0, p2_0, p3_0, (ConsoleColor)_rando.Next(16)));
                                    break;

                                case 4:
                                    int radius_0 = Math.Min(Math.Min(startPt_0.X, startPt_0.Y), Math.Min(maxWidth - startPt_0.X - 1, maxHeight - startPt_0.Y - 1));
                                    shapes.Add(new Circle(radius_0, startPt_0, (ConsoleColor)_rando.Next(16)));
                                    break;
                            }
                        }
                        // foreach loop to override the Draw() method.
                        foreach (var _shape in shapes)
                        {
                            _shape.Draw();
                        }

                        break;
                    case 7:
                        LabTests.RunTests();
                        break;
                    case 8:
                        return;
                    default:
                        break;
                }
                Console.ReadKey();

            } while (selection != menu.Count);
        }
    }
}