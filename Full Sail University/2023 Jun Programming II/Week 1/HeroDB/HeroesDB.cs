using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.ExceptionServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace HeroDB
{
    public static class HeroesDB
    {
        private static List<Hero> _heroes;

        static HeroesDB()
        {
            LoadHeroes();
        }
        public static int Count
        {
            get
            {
                return _heroes.Count;
            }
        }
        public static void LoadHeroes()
        {
            string jsonText = File.ReadAllText("heroes.json");
            try
            {
                _heroes = JsonConvert.DeserializeObject<List<Hero>>(jsonText) ?? new List<Hero>();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                _heroes = new List<Hero>();
            }
        }

        public static Hero GetTheBest()
        {
            Hero theBest = _heroes[51];
            return theBest;
        }

        //---------------------------------------------------------------------------------------------------------------------------------------------
        //
        //PART A
        //


        /*
         

        Part A-1: ShowHeroes
             The method should loop over the _heroes list and print the hero ID and the hero Name.

        */


        // Public String Method ShowHeroes
        /* This was the original code before the C change
        public static string ShowHeroes()
        {
            // Intialize an emptry string variable to store hero info
            string heroesNameID = "";

            // foreach loop to iterate through every hero in the _heroes list
            // and append hero Id and Name to the heroesNameID variable
            foreach (var hero in _heroes)
            {   
                heroesNameID += $"{hero.Id, 3}: {hero.Name}\n";
            }
            // return the heroesNameID variable now full of all the Ids and Names
            return heroesNameID;

        }
        */


        /*
         
        Part A-2: PrintHero
             The method should have a Hero parameter passed to it.Print the details of the Hero parameter(ID, Name, Powerstats.Intelligence, etc)
              See the lab document for a screenshot example under part A-3.

            Use the dot operator to gain access to members of a type.
            EX: to get to the Intelligence value on the Powerstats...  heroObject.Powerstats.Intelligence

        */

        // Public static void Method PrintHero
        public static void PrintHero(Hero hero)
        {
            // Change the text color to yellow
            Console.ForegroundColor = ConsoleColor.Yellow;
            // Write the hero Id and Name from hero
            Console.WriteLine($"{hero.Id}: {hero.Name}");
            // Now change the ConsoleColor for the text to Blue
            Console.ForegroundColor = ConsoleColor.Blue;
            // Write the STATS title in blue
            Console.WriteLine("\tSTATS:");
            // Now change the text color to white
            Console.ForegroundColor = ConsoleColor.White;
            // write the Intelligence, Strength, Speed, Durablility, Power, Combat pulling the info from hero.cs Powerstats object
            Console.WriteLine($"\t\tIntelligence: {hero.Powerstats.Intelligence}");
            Console.WriteLine($"\t\tStrength: {hero.Powerstats.Strength}");
            Console.WriteLine($"\t\tSpeed: {hero.Powerstats.Speed}");
            Console.WriteLine($"\t\tDurability: {hero.Powerstats.Durability}");
            Console.WriteLine($"\t\tPower: {hero.Powerstats.Power}");
            Console.WriteLine($"\t\tCombat: {hero.Powerstats.Combat}");
            // Now change the text color back to blue
            Console.ForegroundColor = ConsoleColor.Blue;
            // Write the APPEARANCE title in blue
            Console.WriteLine("\tAPPEARANCE:");
            // Now change the text color to white
            Console.ForegroundColor = ConsoleColor.White;
            // Write the Race, Height, Weight, Eye Color, Hair Color pulling all the info from hero.cs Appearance object
            Console.WriteLine($"\t\tRace: {hero.Appearance.Race}");
            // Height and Weight were special as they we arrays so I had to use string.Join to get the info otherwise it would say System.String[]
            Console.WriteLine($"\t\tHeight: {string.Join(",", hero.Appearance.Height[0])}");
            Console.WriteLine($"\t\tWeight: {string.Join(",", hero.Appearance.Weight[0])}");
            Console.WriteLine($"\t\tEye Color: {hero.Appearance.EyeColor}");
            Console.WriteLine($"\t\tHair Color: {hero.Appearance.HairColor}");
            // Now change the ConsoleColor for the text to Blue
            Console.ForegroundColor = ConsoleColor.Blue;
            // Write the BIO title in blue
            Console.WriteLine("\tBIO:");
            // Now change the text color to white
            Console.ForegroundColor = ConsoleColor.White;
            // Write to console Full Name, Alter Ego, Aliases, Place of Birth, First Appearance, Publisher, Aligenment
            // pulling information from hero.cs Birography property
            Console.WriteLine($"\t\tFull Name: {hero.Biography.FullName}");
            Console.WriteLine($"\t\tAlter Ego: {hero.Biography.AlterEgos}");
            Console.WriteLine($"\t\tAliases: {string.Join(",", hero.Biography.Aliases)}");
            Console.WriteLine($"\t\tPlace of Birth: {hero.Biography.PlaceOfBirth}");
            Console.WriteLine($"\t\tFirst Appearance: {hero.Biography.FirstAppearance}");
            Console.WriteLine($"\t\tPublisher: {hero.Biography.Publisher}");
            Console.WriteLine($"\t\tAlignment: {hero.Biography.Alignment}");
            // Now change the ConsoleColor for the text to Blue
            Console.ForegroundColor = ConsoleColor.Blue;
            // Write the WORK title in blue
            Console.WriteLine("\tWORK:");
            // Now change the text color to white
            Console.ForegroundColor = ConsoleColor.White;
            // Write oocupation pulling from hero.cs Work property
            Console.WriteLine($"\t\tOccupation: {hero.Work.Occupation}");
            // Now change the ConsoleColor for the text to Blue
            Console.ForegroundColor = ConsoleColor.Blue;
            // Write the CONNECTIONS title in blue
            Console.WriteLine("\tCONNECTIONS:");
            // Now change the text color to white
            Console.ForegroundColor = ConsoleColor.White;
            // Write to console Group Affilication and Relatives pulling information from hero.cs Connections property
            Console.WriteLine($"\t\tGroup Affiliation: {hero.Connections.GroupAffiliation}");
            Console.WriteLine($"\t\tRelatives: {hero.Connections.Relatives}");
            // Reset console color
            Console.ResetColor();
        }





        /*
         
        Part A-3: FindHero
             The method should have a string parameter for the name to search.
             The method needs to loop over the heroes list to try to find the hero.

                 Check if the hero name matches the parameter. If so, break out of the loop and return the found hero.

            (see the GetTheBest method on how to return a Hero object)

        */

        // Public static method FindHero taking in a string name
        public static Hero FindHero(string name)
        {
            // Made a result variable so I could have one return statement and break out of loop
            Hero result = null;
            //foreach loop interating through variable hero in _heroes list
            foreach (var hero in _heroes)
            {
                // if hero.Name == name return that hero
                // basically it's looping through the list until it finds a matching hero to what the user typed in
                // then if a match is found it returns that hero if and breaks out of the loop
                if (hero.Name == name)
                {
                    result = hero;
                    break;
                }
            }

            // if no match is found it returns null
            // I wouldn't normally do a null value but it's in the instructions
            // to write an if else based on a null value being returned or not
            return result;

        }


        //---------------------------------------------------------------------------------------------------------------------------------------------
        //
        //PART B
        //




        /*
         
        Part B-1: RemoveHero
             The method should have a string parameter for the name of the hero to remove.
             The method should loop over the heroes list.
             If the hero is found, remove the hero from the heroes list.
             Return true if the hero was found and removed.

             Return false if the hero was not found.

        */

        // Created a public bool method of RemoveHero taking in a string removeHero
        public static bool RemoveHero(string removeHero)
        {

            // Intialize the heroToRemove variable to null value
            Hero heroToRemove = null;
            // Find the hero to remove using a foreach loop
            foreach (var hero in _heroes)
            {
                // if hero.Name matched the removeHero variable that was taken in then assign it to heroToRemove
                if (hero.Name == removeHero)
                {
                    heroToRemove = hero;
                    break;
                }
            }

            // Now if that heroToRemove is no longer null than remove the hero and return true
            if (heroToRemove != null)
            {
                // If the hero is found, remove it from the list and return true
                _heroes.Remove(heroToRemove);
                return true;

            }

            // If the hero is not found and the value is still null, return false
            return false;
        }

        /*
         
        Part B-2: StartsWith
             The method should have a string parameter for the name of the hero to match and a ref parameter for the List of heroes that were found.
             Loop over the heroes list and add every hero whose name starts with the string parameter to the List parameter. 

        */

        // public static Method StartsWith taking in two parameters Name and list of matching heroes
        public static void StartsWith(string heroName, ref List<Hero> matchingHeroes)
        {
            // Loop over each hero in the heroes list using a foreach loop
            foreach (var hero in _heroes)
            {
                // Check if hero's name starts with the passed string variable
                if (hero.Name.StartsWith(heroName))
                {
                    // If so, add that hero to the matchingHeroes list variable
                    matchingHeroes.Add(hero);
                }
            }
        }

        /*
         
        Part B-3: RemoveAllHeroes
             The method should have a string parameter for the name of the hero to match and an out parameter for the List of heroes that were found and removed.
             Initialize the list inside the RemoveAllHeroes method
             Loop over the heroes list and add every hero whose name starts with the string parameter to the List parameter.

             Make sure to remove the hero from the heroes list.

        */

        public static void RemoveAllHeroes(string startsWithName, out List<Hero> removedHeroes)
        {
            // Initialize the removedHeroes list
            removedHeroes = new List<Hero>();

            // For loop to iterate over the list looping for matching names that begin with the user's input
            for (int i = _heroes.Count - 1; i >= 0; i--)
            {
                // if name in the list matches
                if (_heroes[i].Name.StartsWith(startsWithName))
                {
                    // Add the hero to the removed list
                    removedHeroes.Add(_heroes[i]);
                    // Remove the hero from the original list
                    _heroes.RemoveAt(i);
                }
            }
        }



        //---------------------------------------------------------------------------------------------------------------------------------------------
        //
        //PART C   
        //
        //

        /*
         
        Part C-1: Optional Parameter
              Add an optional parameter to the ShowHeroes method(see part A-1). Default it to 0.
              In the method,
              if the parameter has the default value of 0,
                  show all the heroes
              else
                  show the number of heroes that match the parameter.Example, if 10 is passed in, only show the first 10 heroes.

        */

        // 
        public static void ShowHeroes(int numberToShow = 0)
        {
            // Initialize count variable to 0
            int count = 0;

            // Foreach loop to iterate through every hero in the _heroes list
            foreach (var hero in _heroes)
            {
                // If numberToShow does not equal 0 and count is equal to or greater than numberToShow, break
                if (numberToShow != 0 && count >= numberToShow)
                {
                    break;
                }

                // Print the hero ID and the hero Name
                Console.WriteLine($"{hero.Id,3}: {hero.Name}");

                // Increment count by 1
                count++;
            }
        }
    }
}
