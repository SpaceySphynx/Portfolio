using System;
using System.Text;
using Lab_7A;

namespace FSPG1
{
    // Declared Circle class with properties x, y, and radius.
    public class Circle
    {
        // Member variables for the Circle class
        public float mX;
        public float mY;
        public float mRadius;

        // Constructor for initializing a Circle
        public Circle(float x, float y, float radius)
        {
            mX = x;
            mY = y;
            mRadius = radius;
        }

        // Return for X
        public float GetX()
        {
            return mX;
        }

        // Return for Y
        public float GetY()
        {
            return mY;
        }

        // Return for Radius
        public float GetRadius()
        {
            return mRadius;
        }

        // Method to calculate the area of a Circle using pi*r^2
        public float GetArea()
        {
            return (float)(Math.PI * Math.Pow(mRadius, 2));
        }

        // Method to determine something lies within the circle True of False
        public bool Contains(float px, float py)
        {
            // Calculates the distance between the center of the circle and the point
            float distance = (float)Math.Sqrt(Math.Pow(px - mX, 2) + Math.Pow(py - mY, 2));

            // If the distance is less than or equal to the radius, the point is inside the circle
            return distance <= mRadius;
        }

        // Method to calculate the circumference of the circle
        public float GetCircumference()
        {
            // Uses the formula 2*pi*r
            return (float)(2 * Math.PI * mRadius);
        }
    }
    public class Submission
    {
        /* The following variable will determine the gamification
         * value for this lab assignment. This will determine speed of animations
         * for this assignment and will change your grade out the expected outcome.
         * 
         * 0 = DISABLED 
         * 1 = ENABLED
         * 2 = ENABLED (FAST MODE)
         */

        public static readonly int GAME_MODE = 1;

        // Test1 creates an acronym from the first letter of each input from the array
        public static StringBuilder Test1(string[] names)
        {
            // Created an empty StringBuilder object called "acronym".
            StringBuilder acronym = new StringBuilder();

            // For loop that goes through every string in the input array.
            for (int i = 0; i < names.Length; i++)
            {
                // Checks if the string is empty
                if (!string.IsNullOrEmpty(names[i]))
                {
                    // If the string is valid, take the first character using StringBuilder.
                    acronym.Append(names[i][0]);
                }
            }

            // Return the StringBuilder containing the first letter of each input now as an acronym
            return new StringBuilder(acronym.ToString());
        }

        // Overload the circle class with a new x, y, radius of this Circle and return the value fro Test 2 through 5
        public static object Test2(float x, float y, float radius)
        {
            Circle circle = new Circle(x, y, radius);
            return circle;
        }

        public static object Test3(float x, float y, float radius)
        {
            Circle circle = new Circle(x, y, radius);
            return circle;
        }

        public static object Test4(float x, float y, float radius)
        {
            Circle circle = new Circle(x, y, radius);
            return circle;
        }

        public static object Test5(float x, float y, float radius)
        {
            Circle circle = new Circle(x, y, radius);
            return circle;
        }


        public static int Test6(string str1, string str2, bool ignoreCase)
        {
            // compares if String is equal = 0, str1 comes before str2 1, str1 comes after str2 -1
            // ignoreCase is takes in if it should be case sensitive or not
            return String.Compare(str1, str2, ignoreCase);
        }

        public class TextCodec
        {
            // Private member variable to store the offset.
            private sbyte mOffset;

            // TextCodec constructor.
            public TextCodec(sbyte offset)
            {
                // The offset is saved in the private member variable
                mOffset = offset;
            }

            // Encode method. Input to be encoded and returns the encoded string.
            public string Encode(string message)
            {
                // Initialize a StringBuilder with the input string
                StringBuilder sb = new StringBuilder(message);

                // Standard for loop
                for (int i = 0; i < message.Length; i++)
                {
                    // Offset each character
                    sb[i] = (char)(sb[i] + mOffset);
                }
                // Return the Encode string
                return sb.ToString();
            }

            // The Decode method to decyper the encoded message
            public string Decode(string message)
            {
                // Initialize a StringBuilder with the input
                StringBuilder sb = new StringBuilder(message);

                // Standard for loop to loop over every character in the message
                for (int i = 0; i < message.Length; i++)
                {
                    // Each character is shifted back from the offset value to decode the message
                    sb[i] = (char)(sb[i] - mOffset);
                }
                // Return the decoded string
                return sb.ToString();
            }
        }

        // Test7 is a method to utilize the Encode function
        public static string Test7(sbyte offset, string message)
        {
            // Overload of TextCodec using the offset
            TextCodec codec = new TextCodec(offset);

            // Returns the codec Encoded
            return codec.Encode(message);
        }

        // Test 8 is a mthod to utilize the Decode function
        public static string Test8(sbyte offset, string message)
        {
            // Overload of TextCodec using the offset
            TextCodec codec = new TextCodec(offset);

            // Returns the codec Dncoded
            return codec.Decode(message);
        }
    }
}