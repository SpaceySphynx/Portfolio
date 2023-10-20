using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace WarGame
{
    // Created a HighScore class for all the Methods related to tracking Player Scores and High Scores.
    public class HighScore
    {
        // Varible properties of Name and Score.
        public string Name { get; set; }
        public int Score { get; set; }

        // Constructor for the HighScore class.
        // When a new HighScore object is created, 
        // the player's name and their score are passed in as parameters.
        public HighScore(string name, int score)
        {
            this.Name = name;
            this.Score = score;
        }

        // Method that reads high score data from a file at the given filePath.
        public static List<HighScore> LoadHighScores(string filePath)
        {
            // Read the entire file content as a string at the filePath.
            string jsonData = File.ReadAllText(filePath);
            // The file's contents are deserialized from JSON into a List of HighScore objects.
            List<HighScore> highScores = JsonConvert.DeserializeObject<List<HighScore>>(jsonData);
            // Return the List of HighScore objects.
            return highScores;
        
        }

        // A static method that writes a list of HighScore objects to a file at the given filePath.
        public static void SaveHighScores(string filePath, List<HighScore> highScores)
        {
            // Serialize the List of HighScore objects into JSON format.
            string jsonData = JsonConvert.SerializeObject(highScores, Formatting.Indented);
            // Write the data to the file at the given filePath.
            File.WriteAllText(filePath, jsonData);
        }

        // Method that prints out the high scores in a formatted.
        public static void ShowHighScores(List<HighScore> highScores)
        {
            // Output to console HIGH SCORES header.
            Console.WriteLine("----HIGH SCORES----");

            // Find the max name length amoung all names in the high score.
            int maxNameLength = highScores.Max(hs => hs.Name.Length);

            // Created a foreach loop to loop through each high score in the highScore list.
            foreach (var score in highScores)
            {
                // Add padding to the names using the maxNameLength +1 to match the example.
                string paddedName = score.Name.PadRight(maxNameLength + 1);
                // Write to console the score.Name with the padding.
                Console.Write(paddedName);
                // Change the forgrond color to yellow.
                Console.ForegroundColor = ConsoleColor.Yellow;
                // Print to console the score in yellow ending the line. 
                Console.WriteLine($"{score.Score}");
                // Reset the color on the console before looping again or exiting. 
                Console.ResetColor();
            }
        }
    }
}
