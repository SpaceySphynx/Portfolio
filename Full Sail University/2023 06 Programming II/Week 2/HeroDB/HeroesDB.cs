using Newtonsoft.Json;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics.Metrics;
using System.Globalization;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace HeroDB
{
    public enum SortBy
    {
        Intelligence = 1,
        Strength,
        Speed,
        Durability,
        Power,
        Combat
    }


    public static class HeroesDB
    {
        private static List<Hero> _heroes;
        private static Dictionary<string, List<Hero>> _groupedHeroes;
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
            _groupedHeroes = null;//resets the dictionary
        }



        //
        //sort heroes by Name descendingly using the Bubble Sort algorithm
        //
        public static void SortByNameDescending()
        {
            List<Hero> sorted = _heroes.ToList();//clone

            int n = sorted.Count;
            bool swapped;
            do
            {
                swapped = false;
                for (int i = 1; i < n; i++)
                {
                    int compResult = string.Compare(sorted[i - 1].Name, sorted[i].Name, true);//pass true to ignore case
                    if (compResult < 0)
                    {
                        swapped = true;
                        (sorted[i - 1], sorted[i]) = (sorted[i], sorted[i - 1]);
                    }
                }
                --n;
            } while (swapped);


            foreach (var hero in sorted)
            {
                Console.WriteLine($"{hero.Id,3}: {hero.Name}");
            }
        }



        //---------------------------------------------------------------------------------------------------------------------------------------------
        //
        //PART A
        //

        //
        // Part A-1: MergeSort
        //      Implement the MergeSort and Merge methods in the HeroesDB class.
        //      Your code must follow the pseudo-code. You will find the pseudocode for the methods in the lab document (see the Solution Items in the Solution Explorer)
        //
        //      NOTE: you must add a parameter of type SortBy to both methods.
        //      You will get the user’s sort by selection in part A-2 and pass it to MergeSort.
        //
        //      NOTE: to compare heroes, use the Hero.Compare method.
        //      EX: int compResult = Hero.Compare(hero1, hero2, sortBy); //returns -1 is hero1 < hero2, 0 if hero1 = hero2, or 1 is hero1 > hero2
        //

        // Created public static list MergeSort taking in List m and sortBy
        public static List<Hero> MergeSort(List<Hero> m, SortBy sortBy)
        {
            // Base case. A list of zero or one elements is sorted, by definition.
            // A code formatting was given in the instructions so I followed the formatting adjusting 
            // translating the formatting example into working code
            if (m.Count <= 1)
            {
                return m;
            }

            // Recursive case. First, divide the list into equal-sized sublists
            // consisting of the first half and second half of the list.
            // This assumes lists start at index 0.
            // created a empty list for left and right
            var left = new List<Hero>();
            var right = new List<Hero>();
            // made the for loop
            for (int i = 0; i < m.Count; i++)
            {
                // first half
                if (i < m.Count / 2)
                {
                    left.Add(m[i]);
                }
                // else second half
                else
                {
                    right.Add(m[i]);
                }
            }

            // Recursively sort both sublists.
            left = MergeSort(left, sortBy);
            right = MergeSort(right, sortBy);

            // Then merge the now-sorted sublists.
            return Merge(left, right, sortBy);
        }

        // Merge using compare public static List Method taking in left, right and sortBy
        public static List<Hero> Merge(List<Hero> left, List<Hero> right, SortBy sortBy)
        {
            // variable to hold the newly sorted list
            var result = new List<Hero>();
            // while loop to run until the list is fully sorted
            while (left.Count > 0 && right.Count > 0)
            {
                if (Hero.Compare(left[0], right[0], sortBy) <= 0)
                {
                    result.Add(left[0]);
                    left.RemoveAt(0);
                }
                else
                {
                    result.Add(right[0]);
                    right.RemoveAt(0);
                }
            }

            while (left.Count > 0)
            {
                result.Add(left[0]);
                left.RemoveAt(0);
            }

            while (right.Count > 0)
            {
                result.Add(right[0]);
                right.RemoveAt(0);
            }

            return result;
        }



        //
        // Part A-2: SortByAttribute
        //
        //      The method should have a SortBy parameter passed to it.
        //      In the method, call the MergeSort method from part A-1.
        //      Pass to it the _heroes list of the class and the SortBy parameter.
        //      After calling MergeSort, print the items in the sorted list that is returned from MergeSort.
        //          NOTE: print the hero ID, selected attribute, and name(see screenshot).
        //          To get the selected attribute, call the GetSortByAttribute on each hero.
        //

        // Created the public static void Method SortByAttribute
        public static void SortByAttribute(SortBy sortBy)
        {
            // Calling the MergeSort method and assigning it to a list variable to use
            List<Hero> sortedHeroes = MergeSort(_heroes, sortBy);

            // foreach loop to loop through all the sortedHeroes
            foreach (var hero in sortedHeroes)
            {
                // Called method and assigned to variable
                var attribute = hero.GetSortByAttribute(sortBy);
                // Write to the console the hero id, attribute and name.
                // For formatting I added, 3 and ,4 to get the spacing and right alignment from the example
                Console.WriteLine($"{hero.Id, 3}: {attribute, 4} {hero.Name}");
            }
        }




        //---------------------------------------------------------------------------------------------------------------------------------------------
        //
        // PART B
        //
        //



        //
        // Part B-1: BinarySearch
        //      Implement the BinarySearch method in the HeroesDB class.
        //      Your code must follow the pseudo-code. You will find the pseudocode for the methods in the lab document (see the Solution Items in the Solution Explorer)
        //

        public static int BinarySearch(List<Hero> heroes, string searchTerm, int low, int high)
        {
            // If the high index is less than the low index, it means that the value
            // has not been found, so we return -1
            if (high < low)
            {
                return -1;
            }

            // Calculate the mid index
            int mid = (low + high) / 2;

            // If the search term is less than the name of the hero at the mid index,
            // we continue the search in the left half of the list
            if (string.Compare(searchTerm, heroes[mid].Name, StringComparison.OrdinalIgnoreCase) < 0)
            {
                return BinarySearch(heroes, searchTerm, low, mid - 1);
            }
            // If the search term is greater than the name of the hero at the mid index,
            // we continue the search in the right half of the list
            else if (string.Compare(searchTerm, heroes[mid].Name, StringComparison.OrdinalIgnoreCase) > 0)
            {
                return BinarySearch(heroes, searchTerm, mid + 1, high);
            }
            // If the search term is equal to the name of the hero at the mid index,
            // we have found the hero and return its index
            else
            {
                return mid;
            }
        }



        //
        // Part B-2: FindHero
        //      The method should have a string parameter for the name of the hero to find.
        //      Call the BinarySearch method from part A-3.
        //      Print the result.
        //      If the found index is -1,
        //          print "<insert heroName> is not found"
        //      otherwise
        //          print "<insert heroName> was found at index <insert found index>"
        //

        // Method for finding a specific hero using Binary Search
        public static void FindHero(string heroName)
        {
            // Assume that _heroes list is already sorted by name
            int index = BinarySearch(_heroes, heroName, 0, _heroes.Count - 1);

            // if the hero is not found print to console
            if (index == -1)
            {
                Console.WriteLine($"{heroName} was not found.");
            }
            // else print to console hero name and index
            else
            {
                Console.WriteLine($"{heroName} was found at index {index}");
            }
        }


        // Part B-3: GroupHeroes
        //      Add a method called GroupHeroes to the HeroesDB class.
        //      The method should initialize the _groupedHeroes dictionary.
        //      Make sure to make the keys case insensitive (ignore the case). HINT: look at the constructors of the Dictionary class for an overload that you can use.
        //
        //      You want to create a dictionary where the keys are the first letters of the heroes and the value for each key is a list of the heroes whose names start with that letter.
        //      EX: for the key “B”, the value would contain a list of all the heroes whose names start with B.
        //
        //      Loop over the heroes list.
        //      Check if the first letter of each hero name is in the _groupedHeroes dictionary.
        //      If not,
        //          then create a new list,
        //          add the hero to the list,
        //          then add the list to the dictionary as the value for that initial letter.
        //      Else If it is in the dictionary already,
        //          then add the hero to the list that is stored for that key.
        //

        // Created public static Method GroupHeroes for grouping heroes by the first letter of their name
        public static void GroupHeroes()
        {
            // Initialize the dictionary with a case-insensitive string comparer
            _groupedHeroes = new Dictionary<string, List<Hero>>(StringComparer.OrdinalIgnoreCase);

            // foreach loop to loop over all heroes in the _heroes list
            foreach (var hero in _heroes)
            {
                // Get the first letter of the hero's name
                string firstLetter = hero.Name.Substring(0, 1).ToUpper();\

                if (!_groupedHeroes.ContainsKey(firstLetter))
                {
                    // If the first letter of hero name is not in the dictionary, add it with a new list that contains the current hero
                    _groupedHeroes[firstLetter] = new List<Hero> { hero };
                }
                else
                {
                    // If the first letter of hero name is already in the dictionary, add the hero to the corresponding list
                    _groupedHeroes[firstLetter].Add(hero);
                }
            }
        }


        //
        // Part B-4: PrintGroupCounts
        //
        //      Add a method called PrintGroupCounts to the HeroesDB class.
        //      In the method, if _groupedHeroes is null, call the GroupHeroes method from part B-1.
        //      Loop over the dictionary and print each key and the count of the list for each key.

        // Created public static Method PrintGroupCounts for printing the count of heroes for each letter
        public static void PrintGroupCounts()
        {
            // If _groupedHeroes is not initialized, call GroupHeroes to initialize it
            if (_groupedHeroes == null)
            {
                GroupHeroes();
            }

            // foreach loop for looping over all entries in the dictionary and print the count for each letter
            foreach (var entry in _groupedHeroes)
            {
                Console.WriteLine($"{entry.Key}: {entry.Value.Count, 2}");
            }
        }

        //---------------------------------------------------------------------------------------------------------------------------------------------
        //
        // PART C
        //
        //

        //
        // Part C-1: FindHeroesByLetter
        //      The method should take a string parameter for the first letter.
        //      In the method, if _groupedHeroes is null, call the GroupHeroes method from part B-1.
        //      Then, check if the letter parameter is in the dictionary.
        //      If it is not,
        //          then print a message that no heroes were found that start with the letter.
        //      Else,
        //          loop over the list of heroes for the key and print the ID and name.
        //

        // Created a public static Method FindHeroesByLetter for finding all heroes that start with a specific letter
        public static void FindHeroesByLetter(string firstLetter)
        {
            // If _groupedHeroes is not initialized, call GroupHeroes to initialize it
            if (_groupedHeroes == null)
            {
                GroupHeroes();
            }

            // If the dictionary does not contain this letter, print to console the message below basically saying not found
            if (!_groupedHeroes.ContainsKey(firstLetter))
            {
                Console.WriteLine($"No heroes were found that start with the letter {firstLetter}.");
            }
            // If the dictionary contains the letter, print all heroes that start with this letter with formatting that matches the example in a foreach loop
            else
            {
                foreach (var hero in _groupedHeroes[firstLetter])
                {
                    Console.WriteLine($"{hero.Id, 3}: {hero.Name}");
                }
            }
        }


        // Part C-2: RemoveHero
        //
        //      The method should take a string parameter that is the name of the hero to remove.
        //      In the method, if _groupedHeroes is null, call the GroupHeroes method from part B-1.
        //      Then, check if the _groupedHeroes dictionary contains a key with the first letter of the name.
        //      If not,
        //          print a message saying the hero was not found.
        //     If the key is found, then get the list for the key. The list is the value stored in the dictionary for the key.
        //          call the BinarySearch method to get the index of the hero to remove for the list.
        //          If BinarySearch returns the index, then remove the hero from the list AND from the _heroes list. Print that the hero was removed.
        //              NOTE: if removing the hero makes the list empty for the letter, then remove the letter (which is the key) from the dictionary.
        //          If BinarySearch returns -1 (meaning the hero is not in the list), print a message that the hero was notfound.
        //

        // Created a public static Method RemoveHero for removing a specific hero
        public static void RemoveHero(string heroName)
        {
            // Get the first letter of the hero's name
            string firstLetter = Char.ToUpper(heroName[0]).ToString();

            // If _groupedHeroes is not initialized, call GroupHeroes to initialize it
            if (_groupedHeroes == null)
            {
                GroupHeroes();
            }

            // If the dictionary does not contain this letter, print to console was not found
            if (!_groupedHeroes.ContainsKey(firstLetter))
            {
                Console.WriteLine($"{heroName} was not found.");
                return;
            }

            // Get the list of heroes that start with this letter
            List<Hero> heroesList = _groupedHeroes[firstLetter];

            // Find the hero in this list
            int heroIndex = BinarySearch(heroesList, heroName, 0, heroesList.Count - 1);

            // If the hero is not in the list, print to console was not found
            if (heroIndex == -1)
            {
                Console.WriteLine($"{heroName} was not found.");
                return;
            }

            // Remove the hero from the list
            heroesList.RemoveAt(heroIndex);
            _heroes.Remove(_heroes.Find(h => h.Name.Equals(heroName, StringComparison.OrdinalIgnoreCase)));

            // If removing the hero makes the list empty, remove the letter from the dictionary
            if (heroesList.Count == 0)
            {
                _groupedHeroes.Remove(firstLetter);
            }

            // Print that the hero was removed
            Console.WriteLine($"{heroName} was removed.");
        }

    }
}
