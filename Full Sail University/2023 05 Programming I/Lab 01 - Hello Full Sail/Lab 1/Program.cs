namespace Lab_1;
class Program
{
    static void Main(string[] args)
    {
        // Declaring a string variable type "nameOfUser" 
        string nameOfUser;

        // Declaring a int variable type "age"
        int age;

        // Displays Welcome Message
        Console.WriteLine("Hello Full Sail!");

        // Clarifies what we're asking the user for
        Console.WriteLine("\nWhat's your name?");

        // Prompts user for their name
        Console.Write("\nName: ");

        // Define the value of "nameOfUser" using ReadLine Method
        nameOfUser = Console.ReadLine();

        // Displays hello message to user with defined "nameOfUser" value
        Console.Write($"\nHello, {nameOfUser}!");

        // Clarifies what we're asking for the user's age
        Console.WriteLine("\n\nWhat is your age?");

        // Prompts user to input their age
        Console.Write("\nAge: ");

        // Defines the value of "age" using ReadLine Method with wrapper class Int32 to convert to int
        age = Int32.Parse(Console.ReadLine());

        // Displays contents of variable "nameOfUser" is contents of variable "age" 
        Console.WriteLine($"\n{nameOfUser} is {age}!");

        // Pause console before exiting which requires user input to exit
        Console.WriteLine("\n\n\nPress any key to exit . . .");
        Console.ReadKey();
    }
}