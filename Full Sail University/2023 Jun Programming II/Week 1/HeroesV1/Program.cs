using HeroDB;
using HeroesV1.Tests;
using Newtonsoft.Json;
using PG2Input;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Diagnostics;

namespace HeroesV1
{
    /*  Lab Video   
      
        Here's a video showing what the lab could look like when completed:
        https://web.microsoftstream.com/video/3ed0e560-a731-4e00-bb94-21abb6551b0b

    */
    internal class Program
    {
        static void Main(string[] args)
        {
            /*
            
                Here's an example of calling a method on the HeroesDB and getting a Hero object returned.
                Also in this example is how to access something inside the hero object (Name in this example).

            */
            Hero theBest = HeroesDB.GetTheBest();
            Console.WriteLine($"Welcome to Heroes DB (v1)");

            /*
            
                Here's an example of how to access something inside the hero object (Name in this example).
                
                To go another level deep, you continue to use the dot operator. 
                EX: to get to the Intelligence value on the Powerstats...  theBest.Powerstats.Intelligence

            */
            Console.WriteLine($"We all know the best hero is {theBest.Name}!\n");

            string userName = string.Empty;
            Input.GetString("What is your name? ", ref userName);
            Console.Clear();

            List<string> menu = new List<string>()
            { "1. Show Heroes", "2. Find Hero", "3. Remove Hero", "4. Starts With", "5. Remove All Heroes", "6. Show Top x", "7. Run Lab tests", "8. Exit" };

            int selection;
            do
            {
                Console.Clear();
                Console.WriteLine($"Hello {userName}. Welcome to Heroes DB (v1)");
                Input.GetMenuChoice("Choice? ", menu, out selection);
                Console.Clear();
                switch (selection)
                {
                    case 1:
                        //
                        // Part A-1: ShowHeroes
                        //
                        // In the HeroesDB.cs file in the HeroDB project...
                        //      Add a method called ShowHeroes to the HeroesDB class.
                        //      The method should loop over the _heroes list and print the hero ID and the hero Name.
                        //
                        // In Main (here), add code to case 1 of the switch to call the method. 
                        
                        // When option 1 is selected
                        // Call the Showheroes Method
                        HeroesDB.ShowHeroes();
                        break;

                    case 2:
                        //
                        // Part A-3: FindHero
                        //
                        //
                        // In the HeroesDB.cs file in the HeroDB project...
                        //      Add a method called FindHero to the HeroesDB class.
                        //      The method should have a string parameter for the name to search.
                        //      The method needs to loop over the heroes list to try to find the hero.
                        //          Check if each hero name matches the parameter. If so, break out of the loop and return the found hero.
                        //
                        // In Main (here), add code to case 2 of the switch.
                        //      Using Input.GetString (see example above), ask the user to enter the name of the hero to find.
                        //      Call FindHero passing the string that the user enters.
                        //      if the returned value is not null,
                        //          then call PrintHero
                        //      else
                        //          print out a message that the name was not found.

                        // When option 2 is selected
                        // Intialized a whichHero string variable
                        string whichHero = "";
                        // asked the user to enter the name of a hero to located in the list which will be assigned to the whichHero variable
                        Input.GetString("Please enter the name of the hero to find: ", ref whichHero);
                        // Intialized a foundHero variable pushing whichHero to the FindHero method
                        Hero foundHero = HeroesDB.FindHero(whichHero);
                        // if a hero is found aka null is not returned
                        if (foundHero != null)
                        {
                            // Call the PrintHero method
                            HeroesDB.PrintHero(foundHero);
                        }
                        // Otherwise write to console that hero was not found
                        else
                            Console.WriteLine($"{whichHero} was not found");
                        // break out of if else 
                        break;

                    case 3:
                        //
                        // Part B-1: RemoveHero
                        //
                        //
                        // In the HeroesDB.cs file in the HeroDB project...
                        //      Add a method called RemoveHero to the HeroesDB class.
                        //      The method should have a string parameter for the name of the hero to remove.
                        //      The method should loop over the heroes list.
                        //      If the hero is found, remove the hero from the heroes list.
                        //      Return true if the hero was found and removed.
                        //      Return false if the hero was not found.
                        //
                        // In Main (here), add code to case 3 of the switch.
                        //      Using Input.GetString (see example above), ask the user to enter the name of the hero to remove.
                        //      Call RemoveHero passing the string that the user enters.
                        //      if the returned value is true,
                        //          print that the hero was removed
                        //      else
                        //          print that the hero was not found.
                        //

                        // When option 3 is selected
                        // Intialized a heroName string variable
                        string heroName = "";
                        // Asked the user to enter the name of a hero to remove in the list which will be assigned to the heroName variable
                        Input.GetString("Please enter the name of the hero to remove: ", ref heroName);
                        // Call the RemoveHero method while passing the heroName and return the value into the bool isRemoved variable
                        bool isRemoved = HeroesDB.RemoveHero(heroName);
                        // if a hero is removed
                        if (isRemoved)
                        {
                            // Write to console that the hero was removed successfully
                            Console.WriteLine($"{heroName} was removed.");
                        }
                        // Otherwise write to console that hero was not found
                        else
                            Console.WriteLine($"{heroName} was not found");
                        // break out of the if else 
                        break;
                    case 4:
                        //
                        // Part B-2: StartsWith
                        //
                        //
                        // In the HeroesDB.cs file in the HeroDB project...
                        //      Add a method called StartsWith to the HeroesDB class.
                        //      The method should have a string parameter for the name of the hero to match and a ref parameter for the List of heroes that were found.
                        //      Loop over the heroes list and add every hero whose name starts with the string parameter to the List parameter. 
                        //
                        // In Main (here), add code to case 4 of the switch.
                        //      Using Input.GetString (see example above), ask the user to enter the name of the hero to find.
                        //      Call StartsWith passing the string that the user enters and a ref parameter for the list. Make sure to create an empty list.
                        //      print out the number of heroes found AND loop over the list and call PrintHero for each hero found.
                        //

                        // When option 4 is selected
                        // Intialized a heroToFind string variable
                        string heroToFind = "";
                        // Asked the user to enter the name of a hero to find in the list which will be assigned to the heroToFind ref variable
                        Input.GetString("Please enter the start of the name of the heroes to find: ", ref heroToFind);
                        // List variable foundHeroes
                        List<Hero> foundHeroes = new List<Hero>();
                        // Call the StartsWith Method passing the heroToFind and foundHeroes variables
                        HeroesDB.StartsWith(heroToFind, ref foundHeroes);
                        // Print the number of heroes found and formatted like the example
                        Console.WriteLine($"Found {foundHeroes.Count} heroes that start with {heroToFind}\n\n\n");
                        // Loop over each hero in the foundHeroes list using a foreach loop
                        foreach (var hero in foundHeroes)
                        {
                            // And call PrintHero with that hero
                            HeroesDB.PrintHero(hero);
                        }
                        // break out of this case
                        break;
                    case 5:
                        //
                        // Part B-3: RemoveAllHeroes
                        //
                        //
                        // In the HeroesDB.cs file in the HeroDB project...
                        //      Add a method called RemoveAllHeroes to the HeroesDB class.
                        //      The method should have a string parameter for the name of the hero to match and an out parameter for the List of heroes that were found and removed.
                        //      Initialize the list inside the RemoveAllHeroes method
                        //      Loop over the heroes list and add every hero whose name starts with the string parameter to the List parameter.
                        //      Make sure to remove the hero from the heroes list.
                        //
                        // In Main (here), add code to case 5 of the switch.
                        //      Using Input.GetString (see example above), ask the user to enter the name of the hero to remove.
                        //      Call RemoveAllHeroes passing the string that the user enters and an out parameter for the list.
                        //      After calling the method, if the list is empty, print that "No heroes found that start with <the startsWith string the user entered>"
                        //      else print "The following heroes were removed: " and loop over the list calling PrintHero for each hero in the list.
                        //

                        // When option 5 is selected
                        // Intialized a heroesToRemove string variable
                        string heroesToRemove = "";
                        // Asked the user to enter the name of a heroes to find and remove in the list which will be assigned to the heroesToRemove ref variable
                        Input.GetString("Please enter the start of the name of the heroes to remove: ", ref heroesToRemove);
 
                        // Initialize an empty list to hold removed heroes
                        List<Hero> removedHeroes;

                        // Call RemoveAllHeroes with the user's input and the out parameter
                        HeroesDB.RemoveAllHeroes(heroesToRemove, out removedHeroes);

                        // if removedHeroes count is not zero than give a confirmation of heroes removed
                        if (removedHeroes.Count != 0)
                        {
                            // Write to console that the hero was removed successfully
                            Console.WriteLine($"The following heroes were removed: \n\n\n");
                            foreach(var hero in removedHeroes)
                            {
                                HeroesDB.PrintHero(hero);
                            }
                        }
                        // Otherwise write to console that hero was not found
                        else
                            Console.WriteLine($"{heroesToRemove} was not found");
                        // break out of the if else 
                        break;
                    case 6:
                        //
                        // Part C-1: Optional Parameter
                        //
                        //
                        // In the HeroesDB.cs file in the HeroDB project...
                        //      Add an optional parameter to the ShowHeroes method. Default it to 0.
                        //      In the method,
                        //      if the parameter has the default value of 0,
                        //          show all the heroes
                        //      else
                        //          show the number of heroes that match the parameter. Example, if 10 is passed in, only show the first 10 heroes.
                        //
                        //
                        // In Main (here), add code to case 6 of the switch.
                        //      Using Input.GetInteger (see Input.GetMenuChoice for an example of calling GetInteger), ask the user to enter the number of heroes to show.
                        //      Use the HeroesDB.Count property to get the max value to pass to Input.GetInteger.
                        //      Call ShowHeroes and pass in the number that Input.GetInteger returns.
                        //

                        // When option 6 is selected
                        // Intialized a heroesToShow string variable
                        // Asked the user to enter the number of heroes to show to be assigned to the heroesToShow variable
                        int heroesToShow = Input.GetInteger("How many heroes to show? ", 0, HeroesDB.Count);

                        // Call ShowHeroes with the user's input
                        HeroesDB.ShowHeroes(heroesToShow);
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